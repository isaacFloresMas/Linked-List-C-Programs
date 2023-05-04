/****************************************************************************** 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA3
* Graph.h
* Header file for Graph ADT
******************************************************************************/ 
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include <stdbool.h>
#include "List.h"

#define UNDEF -1
#define NIL 0

// Exported types -------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------

Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------

int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
List getEdges(Graph G, int u);

// Manipulation procedures ----------------------------------------------------

void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List s);

// Other operations -----------------------------------------------------------

void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void displayEdges(Graph G);
void displayAll(Graph G);

#endif