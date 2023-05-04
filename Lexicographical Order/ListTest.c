/********************************************************************************* 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA1 
* ListTest.c 
* List ADT Tester
*********************************************************************************/ 

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() {
    List OK = newList();
    prepend(OK, 808);
    prepend(OK, 52);
    prepend(OK, 916);
    prepend(OK, 1111);
    prepend(OK, 99);
    moveFront(OK);
    moveNext(OK);
    moveNext(OK);
    printf("Front element is %d\n", front(OK));
    printf("Back element is %d\n", back(OK));
    printf("Length of the list is %d\n", length(OK));
    insertBefore(OK, 3);
    insertAfter(OK, 444);
    delete(OK);
    printf("Index of the list is %d and should be -1\n", index(OK));
    displayList(OK);
    clear(OK);
    displayList(OK);
    List Sir = newList();
    for (int i = 0; i < 10; i++) {
        append(OK, i*3+i);
        append(Sir, i*3+i);
    }
    printf("Are both lists equal: %x\n", equals(OK, Sir));
    append(Sir, 2*3+6);
    printf("Are both lists equal now: %x\n", equals(OK, Sir));
    displayList(OK);
    freeList(&OK);
}
