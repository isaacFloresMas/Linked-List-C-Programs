/********************************************************************************* 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA2
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
    Graph OK = newGraph(10);
    addEdge(OK, 2, 3);
    addEdge(OK, 2, 4);
    addEdge(OK, 2, 1);
    addEdge(OK, 3, 5);
    addEdge(OK, 2, 7);
    addEdge(OK, 3, 10);
    addEdge(OK, 2, 8);
    addEdge(OK, 2, 5);
    addEdge(OK, 2, 9);
    addEdge(OK, 2, 6);
    displayEdges(OK);
    makeNull(OK);
    printf("\nCleared List:\n");
    displayEdges(OK);
    printf("\n");
    freeGraph(&OK);

    Graph OKC = newGraph(5);
    addEdge(OKC, 2, 3);
    addEdge(OKC, 2, 4);
    addEdge(OKC, 2, 4); // Making sure repeated edges aren't added
    addEdge(OKC, 4, 1);
    addEdge(OKC, 5, 1);
    displayEdges(OKC);
    BFS(OKC, 3);
    List path = newList();
    getPath(path, OKC, 5); // 3-5 path
    displayList(path);
    freeGraph(&OKC);
    freeList(&path);
    return 0;
}