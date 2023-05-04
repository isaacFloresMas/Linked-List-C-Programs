/********************************************************************************* 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA3
* GraphTest.c 
* Tester file for Graph ADT
*********************************************************************************/ 

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"

int main() {
    Graph OK = newGraph(8);
    addArc(OK, 1, 2);
    addArc(OK, 2, 3);
    addArc(OK, 2, 5);
    addArc(OK, 2, 6);
    addArc(OK, 3, 4);
    addArc(OK, 3, 7);
    addArc(OK, 4, 3);
    addArc(OK, 4, 8);
    addArc(OK, 5, 1);
    addArc(OK, 5, 6);
    addArc(OK, 6, 7);
    addArc(OK, 7, 6);
    addArc(OK, 7, 8);
    addArc(OK, 8, 8);
    addArc(OK, 8, 8); // checking if repeated arc is not added

    displayEdges(OK);
    printf("Order of Graph is %d and should be 8\n", getOrder(OK));
    printf("Size of Graph is %d and should be 14\n", getSize(OK));
    printf("\nTranspose:\n");
    Graph T = transpose(OK);
    displayEdges(T);
    printf("\n");

    List L = newList();
    for (int i = 1; i < 9; i++) {
        append(L, i);
    }

    printf("DFS Ran:\n");
    DFS(OK, L);
    displayAll(OK); // Display all shows each vertices edges, discover time, finish time, & parent
    printf("\nCopied Graph:\n"); // which is why I don't test those specific functions in this file
    Graph nG = copyGraph(OK);
    displayAll(nG);

    makeNull(nG);
    printf("\nNULL Graph:\n");
    displayEdges(nG);
    printf("\nOne Edge (2,4):\n");
    addEdge(nG, 2, 4);
    displayEdges(nG);

    freeList(&L);
    freeGraph(&T);
    freeGraph(&nG);
    freeGraph(&OK);
    return 0;
}