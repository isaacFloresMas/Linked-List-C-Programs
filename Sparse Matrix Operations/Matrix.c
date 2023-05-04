/****************************************************************************** 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA4
* Matrix.c
* Sparse Matrix ADT meaning the number of non-zero entries is small compared
* to the total number of entries
******************************************************************************/ 

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "List.h"
#include "Matrix.h"

double vectorDot(List A, List B);

// struct creation ------------------------------------------------------------

// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj {
    int col;
    double val;
} EntryObj; 

// private MatrixObj type
typedef struct MatrixObj {
    int rows;
    int nonZero;
    List *matrix;
} MatrixObj;

typedef struct MatrixObj* Matrix;

// Constructors-Destructors ---------------------------------------------------

Entry newEntry(int column, double value) {
    Entry E = malloc(sizeof(EntryObj));
    assert(E != NULL);
    E->col = column;
    E->val = value;
    return E;
}

void freeEntry(Entry *pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    assert(M != NULL);
    M->matrix = malloc((n+1) * (sizeof(List)));
    for (int y = 1; y < n+1; y++) {
        M->matrix[y] = newList();
    }
    M->rows = n;
    M->nonZero = 0;
    return M;
}

// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        Entry curr;
        for (int i = 1; i <= size(*pM); i++) {
            for (moveFront((*pM)->matrix[i]); index((*pM)->matrix[i]) >= 0; moveNext((*pM)->matrix[i])) {
                curr = get((*pM)->matrix[i]);
                freeEntry(&curr);
            }
            freeList(&((*pM)->matrix[i]));
        }
    }
    free((*pM)->matrix);
    free(*pM);
    *pM = NULL;
}

// Access functions -----------------------------------------------------------

// Return the size of square Matrix M.
int size(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling size() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    return M->rows;
}

// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling NNZ() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    return M->nonZero;
}

// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if (size(A) != size(B) || NNZ(A) != NNZ(B)) {
        return 0;
    }

    Entry curA, curB;
    for (int i = 1; i < size(A); i++) {
        if (length(A->matrix[i]) != length(B->matrix[i])) {
            return 0;
        }
        moveFront(A->matrix[i]);
        moveFront(B->matrix[i]);
        while (index(A->matrix[i]) >= 0 || index(B->matrix[i]) >= 0) {
            if (index(A->matrix[i]) == -1) {
                return 0;
            } else {
                curA = get(A->matrix[i]);
            }

            if (index(B->matrix[i]) == -1) {
                return 0;
            } else {
                curB = get(B->matrix[i]);
            }

            if (curA->col != curB->col || curA->val != curB->val) {
                return 0;
            } else {
                moveNext(A->matrix[i]);
                moveNext(B->matrix[i]);
            }
        }        
    }
    return 1;
}

// Manipulation procedures ---------------------------------------------------

// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Entry x;
    for (int i = 1; i <= size(M); i++) {
        moveFront(M->matrix[i]);
        while (index(M->matrix[i]) >= 0) {
            x = get(M->matrix[i]);
            freeEntry(&x);
            moveNext(M->matrix[i]);
        }
        clear(M->matrix[i]);
    }
    M->nonZero = 0;
}

// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > size(M) || j < 1 || j > size(M)) {
        fprintf(stderr, "Matrix Error: calling changeEntry() on an invalid row or column\n");
        exit(EXIT_FAILURE);
    }

    List curr = M->matrix[i];
    if (length(curr) == 0) {
        if (x == 0) {
            return;
        }
        Entry new = newEntry(j, x);
        append(curr, new);
        M->nonZero += 1;
        return;
    }

    Entry y;
    moveFront(curr);
    while (index(curr) >= 0) {
        y = get(curr);
        if (j == y->col) {
            if (x == 0) {
                delete(curr);
                freeEntry(&y);
                M->nonZero -= 1;
                return;
            }
            y->val = x;
            return;
        }
        else if (j < y->col) {
            if (x == 0) {
                return;
            }
            Entry new = newEntry(j, x);
            insertBefore(curr, new);
            M->nonZero += 1;
            return;
        }
        moveNext(curr);
    }
    if (x == 0) {
        return;
    }
    Entry new = newEntry(j, x);
    append(curr, new);
    M->nonZero += 1;
}

// Matrix Arithmetic operations ----------------------------------------------

// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix C = newMatrix(size(A));
    Entry curr;
    for (int i = 1; i <= size(A); i++) {
        for (moveFront(A->matrix[i]); index(A->matrix[i]) >= 0; moveNext(A->matrix[i])) {
            curr = get(A->matrix[i]);
            changeEntry(C, i, curr->col, curr->val);
        }
    }
    return C;
}

// Returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix T = newMatrix(size(A));
    Entry curr;
    for (int i = 1; i <= size(A); i++) {
        for (moveFront(A->matrix[i]); index(A->matrix[i]) >= 0; moveNext(A->matrix[i])) {
            curr = get(A->matrix[i]);
            changeEntry(T, curr->col, i, curr->val);
        }
    }
    return T;
}

// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling scalarMult() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix T = newMatrix(size(A));
    Entry curr;
    for (int i = 1; i <= size(A); i++) {
        for (moveFront(A->matrix[i]); index(A->matrix[i]) >= 0; moveNext(A->matrix[i])) {
            curr = get(A->matrix[i]);
            changeEntry(T, i, curr->col, x*curr->val);
        }
    }
    return T;
}

// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "Matrix Error: calling sum() on different sized matrices\n");
        exit(EXIT_FAILURE);
    }

    if (equals(A, B)) {
        return scalarMult(2, A);
    }

    Matrix S = newMatrix(size(A));
    Entry curA, curB;
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->matrix[i]);
        moveFront(B->matrix[i]);
        while (index(A->matrix[i]) >= 0 || index(B->matrix[i]) >= 0) {
            // If row[i] of A is finished but B isn't
            if (index(A->matrix[i]) == -1) {
                curB = get(B->matrix[i]);
                changeEntry(S, i, curB->col, curB->val);
                moveNext(B->matrix[i]);
                continue;
            }
            else {
                curA = get(A->matrix[i]);
            }

            // If row[i] of B is finished but A isn't
            if (index(B->matrix[i]) == -1) {
                changeEntry(S, i, curA->col, curA->val);
                moveNext(A->matrix[i]);
                continue;
            }
            else {
                curB = get(B->matrix[i]);
            }

            // If both row[i] of A and B aren't finished
            if (curA->col < curB->col) {
                changeEntry(S, i, curA->col, curA->val);
                moveNext(A->matrix[i]);
            }
            else if (curA->col > curB->col) {
                changeEntry(S, i, curB->col, curB->val);
                moveNext(B->matrix[i]);
            }
            else if (curA->col == curB->col) {
                changeEntry(S, i, curA->col, curA->val + curB->val);
                moveNext(A->matrix[i]);
                moveNext(B->matrix[i]);
            }
        }
    }
    return S;
}

// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
        if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "Matrix Error: calling diff() on different sized matrices\n");
        exit(EXIT_FAILURE);
    }

    Matrix D = newMatrix(size(A));

    if (equals(A, B)) {
        return D;
    }

    Entry curA, curB;
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->matrix[i]);
        moveFront(B->matrix[i]);
        while (index(A->matrix[i]) >= 0 || index(B->matrix[i]) >= 0) {
            // If row[i] of A is finished but B isn't
            if (index(A->matrix[i]) == -1) {
                curB = get(B->matrix[i]);
                changeEntry(D, i, curB->col, 0 - curB->val);
                moveNext(B->matrix[i]);
                continue;
            }
            else {
                curA = get(A->matrix[i]);
            }

            // If row[i] of B is finished but A isn't
            if (index(B->matrix[i]) == -1) {
                changeEntry(D, i, curA->col, curA->val);
                moveNext(A->matrix[i]);
                continue;
            }
            else {
                curB = get(B->matrix[i]);
            }

            // If both row[i] of A and B aren't finished
            if (curA->col < curB->col) {
                changeEntry(D, i, curA->col, curA->val);
                moveNext(A->matrix[i]);
            }
            else if (curA->col > curB->col) {
                changeEntry(D, i, curB->col, 0 - curB->val);
                moveNext(B->matrix[i]);
            }
            else if (curA->col == curB->col) {
                changeEntry(D, i, curA->col, curA->val - curB->val);
                moveNext(A->matrix[i]);
                moveNext(B->matrix[i]);
            }
        }
    }
    return D;
}

// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling product() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "Matrix Error: calling product() on different sized matrices\n");
        exit(EXIT_FAILURE);
    }

    Matrix P = newMatrix(size(A));
    double x;
    Matrix tB = transpose(B);            // Transpose B so the jth row of transpose(B)
    for (int i = 1; i <= size(A); i++) { // is the jth column of B
        for (int j = 1; j <= size(A); j++) {
            List LA = A->matrix[i];
            List LB = tB->matrix[j]; 
            if (length(LA) == 0 || length(LB) == 0) {
                continue;
            } 
            x = vectorDot(LA, LB);
            changeEntry(P, i, j, x);

        }
    }
    freeMatrix(&tB);
    return P;
}

// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling displayMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    List curr;
    for (int i = 0; i < size(M); i++) {
        curr = M->matrix[i+1];
        if (length(curr) == 0) {
            continue;
        }        
        fprintf(out, "%d: ", i+1);
        moveFront(curr);
        while (index(curr) >= 0) {
            Entry x = get(curr);
            fprintf(out, "(%d, %.1f) ", x->col, x->val);
            moveNext(curr);
        }
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
}

// Tester function that prints the non-zero entries of the Matrix
void displayMatrix(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling displayMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    List curr;
    for (int i = 0; i < size(M); i++) {
        curr = M->matrix[i+1];
        if (length(curr) == 0) {
            continue;
        }
        printf("%d: ", i+1);
        moveFront(curr);
        while (index(curr) >= 0) {
            Entry x = get(curr);
            printf("(%d, %.1f) ", x->col, x->val);
            moveNext(curr);
        }
        printf("\n");
    }
}

// Helper function that computes dot prdouct from two lists
double vectorDot(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling vectorDot() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    double x = 0;
    Entry curA, curB;
    moveFront(A);
    moveFront(B);
    // If at least one List is finished, exit loop since anything times 0 is 0
    while (index(A) >= 0 && index(B) >= 0) {
        curA = get(A);
        curB = get(B);

        // x * 0 = 0, so skip
        if (curA->col < curB->col) {
            moveNext(A);
        }
        // 0 * x = 0, so skip
        else if (curA->col > curB->col) {
            moveNext(B);
        }
        // Non-zero in row[i] of A & col[j] of B so multiply each value and add to sum
        else if (curA->col == curB->col) {
            x += curA->val * curB->val;
            moveNext(A);
            moveNext(B);
        }
    }
    return x;
}