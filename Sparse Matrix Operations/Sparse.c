/****************************************************************************** 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA4
* Sparse.c
* Performs matrix operations on two sparse matrices given from an input file
******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "List.h"
#include "Matrix.h"

int main(int argc, char **argv) {
    FILE *fIN;
    FILE *fOUT;
    int row, col, n, nzA, nzB;
    double value;

    // Checking for the correct amount of arguments
    if (argc != 3) {
        fprintf(stderr, "Sparse Error: Incorrect number of arguments. Correct usage should be ./Sparse <input file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    // Opening infile and outfile for reading and writing respectively
    if ((fIN = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Sparse Error: Unable to open %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((fOUT = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "Sparse Error: Unable to open %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    // End of opening infile and outfile for reading and writing respectively

    // Reading the size and number of NNZ entries for the matrices and creating new matrices
    fscanf(fIN, "%d %d %d\n", &n, &nzA, &nzB);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    // End of reading the size and number of NNZ entries for the matrices and creating new matrices

    // Reading and adding in matrix entries
    for (int i = 0; i < nzA; i++) {
        fscanf(fIN, "%d %d %lf\n", &row, &col, &value);
        changeEntry(A, row, col, value);
    }
    fscanf(fIN, "\n");
    for (int i = 0; i < nzB; i++) {
        fscanf(fIN, "%d %d %lf\n", &row, &col, &value);
        changeEntry(B, row, col, value);
    }
    // End of reading and adding in matrix entries
  
    // Performing matrix operations and printing results to outfile
    fprintf(fOUT, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(fOUT, A);

    fprintf(fOUT, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(fOUT, B);

    Matrix scalar = scalarMult(1.5, A);
    fprintf(fOUT, "(1.5)*A =\n");
    printMatrix(fOUT, scalar);

    Matrix aPb = sum(A, B);
    fprintf(fOUT, "A+B =\n");
    printMatrix(fOUT, aPb);

    Matrix aPa = sum(A, A);
    fprintf(fOUT, "A+A =\n");
    printMatrix(fOUT, aPa);

    Matrix bMa = diff(B, A);
    fprintf(fOUT, "B-A =\n");
    printMatrix(fOUT, bMa);

    Matrix aMa = diff(A, A);
    fprintf(fOUT, "A-A =\n");
    printMatrix(fOUT, aMa);

    Matrix T = transpose(A);
    fprintf(fOUT, "Transpose(A) =\n");
    printMatrix(fOUT, T);

    Matrix P = product(A, B);
    fprintf(fOUT, "A*B =\n");
    printMatrix(fOUT, P);

    Matrix PB = product(B, B);
    fprintf(fOUT, "B*B =\n");
    printMatrix(fOUT, PB);
    // End of performing matrix operations and printing results to outfile

    // Freeing files and matrices created
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scalar);
    freeMatrix(&aPb);
    freeMatrix(&aPa);
    freeMatrix(&bMa);
    freeMatrix(&aMa);
    freeMatrix(&T);
    freeMatrix(&P);
    freeMatrix(&PB);
    fclose(fIN);
    fclose(fOUT);
    // End of freeing files and matrices created
    return 0;
}