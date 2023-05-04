/********************************************************************************* 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA4
* ListTest.c 
* Tester Function for Doubly Linked List ADT
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]) {

    List A = newList();
    List B = newList();
    int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int count, i;
    count = 1;

    // initialize Lists A and B
    for(i=1; i<=20; i++){
        append(A, &X[i]);
        prepend(B, &X[i]);
    }

    // print both lists of integers in forward direction
    for(moveFront(A); index(A)>=0; moveNext(A)){
        printf("%d ", *(int*)get(A));
    }
    printf("\n");
    for(moveFront(B); index(B)>=0; moveNext(B)){
        printf("%d ", *(int*)get(B));
    }
    printf("\n");

    // print both lists of integers in backward direction
    for(moveBack(A); index(A)>=0; movePrev(A)){
        printf("%d ", *(int*)get(A));
    }
    printf("\n");
    for(moveBack(B); index(B)>=0; movePrev(B)){
        printf("%d ", *(int*)get(B));
    }
    printf("\n\n");

    // Testint insertBefore and insertAfter
    for(moveFront(A); index(A)>=0; moveNext(A), count++){
        insertBefore(A, &X[count]);
    }
    count = 1;
    for(moveBack(B); index(B)>=0; movePrev(B), count++){
        insertAfter(B, &X[count]);
    }
    for(moveFront(A); index(A)>=0; moveNext(A)){
        printf("%d ", *(int*)get(A));
    }
    printf("\n");
    for(moveFront(B); index(B)>=0; moveNext(B)){
        printf("%d ", *(int*)get(B));
    }
    printf("\n\n");

    printf("Front Element is %d and Back Element is %d\n", *(int*)front(B), *(int*)back(B));
    printf("Length is %d\n", length(B));
    deleteFront(B);
    deleteFront(B);
    deleteBack(B);
    deleteBack(B);
    printf("Front Element is %d and Back Element is %d\n", *(int*)front(B), *(int*)back(B));
    printf("Length is %d\n\n", length(B));

    count = 20;
    for(moveFront(A); index(A)>=0; moveNext(A), moveNext(A), count--){
        set(A, &X[count]);
    }
    for(moveFront(A); index(A)>=0; moveNext(A)){
        printf("%d ", *(int*)get(A));
    }
    printf("\n");

    // Delete first 10 elements
    count = 0;
    for(moveFront(A); count < 5; moveFront(A), count++){
        delete(A);
    }
    for(moveFront(A); index(A)>=0; moveNext(A)){
        printf("%d ", *(int*)get(A));
    }    

    clear(B);
    printf("\n\nCleared List: Length = %d\n", length(B));
    for(moveFront(B); index(B)>=0; moveNext(B)){
        printf("%d ", *(int*)get(A));
    }   

    freeList(&A);
    freeList(&B);
    return(0);
}
