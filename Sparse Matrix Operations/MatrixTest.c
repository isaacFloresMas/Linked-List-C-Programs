/****************************************************************************** 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA4
* MatrixTest.c
* Tester file for Matrix ADT
******************************************************************************/ 

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "List.h"
#include "Matrix.h"

int main () {
    Matrix OK = newMatrix(3);
    Matrix burger = newMatrix(3);
    Matrix cheeseBurger = newMatrix(3);

    changeEntry(OK, 1, 1, 1);
    changeEntry(OK, 1, 3, 3);
    changeEntry(OK, 2, 2, 5);
    changeEntry(OK, 2, 3, 6);
    changeEntry(OK, 3, 1, 7);
    changeEntry(OK, 3, 3, 9);
    changeEntry(OK, 3, 3, 9);

    changeEntry(burger, 1, 2, 1);
    changeEntry(burger, 1, 3, 2);
    changeEntry(burger, 2, 1, 3);
    changeEntry(burger, 3, 2, 3);
    changeEntry(burger, 3, 3, 5);

    changeEntry(cheeseBurger, 1, 2, 1);
    changeEntry(cheeseBurger, 1, 3, 2);
    changeEntry(cheeseBurger, 2, 1, 3);
    changeEntry(cheeseBurger, 3, 2, 3);
    changeEntry(cheeseBurger, 3, 3, 5);

    printf("Non-zero entries is %d and should be 6\n", NNZ(OK));
    printf("Size of matrix is %d and should be 3\n\n", size(OK));

    printf("A:\n");
    displayMatrix(OK);
    printf("\nB:\n");
    displayMatrix(burger);

    printf("\nTranspose(A):\n");
    Matrix TM = transpose(OK);
    displayMatrix(TM);

    printf("\nScalar(A) 2x:\n");
    Matrix SM = scalarMult(2, OK);
    displayMatrix(SM);

    printf("\nSum:\n");
    Matrix SUM = sum(OK, burger);
    displayMatrix(SUM);

    printf("\nDifference:\n");
    Matrix D = diff(OK, burger);
    displayMatrix(D);

    printf("\nDot Product:\n");
    Matrix P = product(OK, burger);
    displayMatrix(P);

    printf("\nCopy of B:\n");
    Matrix C = copy(burger);
    displayMatrix(C);

    printf("\nIs Matrix B = Matrix B Copy: %d\n", equals(burger, cheeseBurger));
    printf("Is Matrix A = Matrix B: %d\n", equals(OK, burger));

    printf("\nZero State A:\n");
    makeZero(OK);
    displayMatrix(OK);

    freeMatrix(&OK);
    freeMatrix(&burger);
    freeMatrix(&cheeseBurger);
    freeMatrix(&TM);
    freeMatrix(&SM);
    freeMatrix(&SUM);
    freeMatrix(&D);
    freeMatrix(&P);
    freeMatrix(&C);
    return 0;
}