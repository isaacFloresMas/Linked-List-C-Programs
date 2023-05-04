/****************************************************************************** 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA2
* Graph.h
* Header file for Graph ADT
******************************************************************************/ 
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include <stdbool.h>
#include "List.h"

#define INF -1
#define NIL 0

// Exported types -------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------

Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------

int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
List getEdges(Graph G, int u);

// Manipulation procedures ----------------------------------------------------

void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

// Other operations -----------------------------------------------------------

void printGraph(FILE* out, Graph G);
void displayEdges(Graph G);
void printPath(Graph G, int s, int x);

#endif