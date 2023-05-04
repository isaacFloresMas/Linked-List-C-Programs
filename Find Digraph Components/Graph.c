/********************************************************************************* 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA3
* Graph.c 
* Implementation of Graph ADT
*********************************************************************************/ 

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "List.h"
#include "Graph.h"

void visit(Graph G, List s, int x, int *time);

// struct creation ------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj {
    List *edges; // An array of Lists whose ith element contains the edges of vertex i.
    int *color; // An array of ints (or chars, or strings) whose ith element is the color 
                // (white, gray, black) of vertex i.
    int *parent; // An array of ints whose ith element is the parent of vertex i.
    int *discTime; // Discover Time
    int *finTime; // Finish time
    int order; // number of vertices
    int size; // number of edges
} GraphObj;

typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------

// Creates and returns a new Graph.
Graph newGraph(int n) { 
    Graph G = malloc(sizeof(GraphObj));
    assert(G != NULL);
    G->edges = malloc((n+1) * (sizeof(List)));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->discTime = calloc(n+1, sizeof(int));
    G->finTime = calloc(n+1, sizeof(int));
    for (int i = 0; i < n+1; i++) {
        G->edges[i] = newList();
        G->discTime[i] = UNDEF;
        G->finTime[i] = UNDEF;
    }
    G->order = n;
    G->size = 0;
    return(G);
}

// Frees all heap memory associated with *pG, and sets *pG to NULL.
void freeGraph(Graph* pG) { 
    if (pG != NULL && *pG != NULL) {
        for (int i = 0; i < getOrder(*pG)+1; i++) {
            freeList(&((*pG)->edges[i]));
        }
        free((*pG)->edges);
        free((*pG)->color); // = calloc(n+1, sizeof(int));
        free((*pG)->parent); // = calloc(n+1, sizeof(int));
        free((*pG)->discTime); // = calloc(n+1, sizeof(int));
        free((*pG)->finTime); // = calloc(n+1, sizeof(int));
    }
    free(*pG);
    *pG = NULL;
}

// Access functions -----------------------------------------------------------

// Returns current order of G
int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    return G->order;
}


// Returns the current size of G
int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

// Returns the parent vertex of u
int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getParent() for a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

// Returns the discover time of vertex u
int getDiscover(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getDiscover() for a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }

    return G->discTime[u];
}

// Returns the finish time of vertex u
int getFinish(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getFinish() for a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }

    return G->finTime[u];
}

// Returns the list containing the edges(neighbors) of the vertex u
List getEdges(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getEdges() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getEdges() for a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }

    return G->edges[u];
}


// Manipulation procedures ----------------------------------------------------

// Returns the Graph to its original state without edges
void makeNull(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling makeNull() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < getOrder(G)+1; i++) {
        clear(G->edges[i]);
    }
    G->size = 0;
}

// Adds vertex v to u's edge list and vertex u to v's edge list
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addEdge() for 1 or more vertices that do not exist\n");
        exit(EXIT_FAILURE);
    }

    addArc(G, u, v);
    addArc(G, v, u);

    G->size -= 1;
}

// Adds vertex v to u's edge list 
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addArc() for 1 or more vertices that do not exist\n");
        exit(EXIT_FAILURE);
    }

    List uEdges = G->edges[u];

    // Adds v to vertex u's edge list in numerical order
    if (length(uEdges) != 0) {
        moveFront(uEdges);
        while (index(uEdges) >= 0) {
            if (get(uEdges) == v) { // Stops repeated edges from being added
                return;
            }
            else if (get(uEdges) > v) {
                insertBefore(uEdges, v);
                break;
            }
            moveNext(uEdges);
        }
        if (index(uEdges) == -1) {
            append(uEdges, v);
        }
    }
    else {
        append(uEdges, v);
    }    
    G->size += 1;
}

/* Pre: length(S)==getOrder(G) */
void DFS(Graph G, List s) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(s) != getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addArc() for 1 or more vertices that do not exist\n");
        exit(EXIT_FAILURE);
    }

    // Initialization
    for (int i = 1; i < getOrder(G)+1; i++) {
        G->color[i] = -1;
        G->parent[i] = NIL;
    }

    // Start of Main Loop
    int x, count, time;
    time = count = 0;
    moveFront(s);
    while (count < getOrder(G)) {
        x = get(s);
        if (G->color[x] == -1) {
            visit(G, s, x, &time);
        }
        moveNext(s);
        deletePrev(s);
        count++;
    }   
}

// Visits a vertex x in graph G and logs its discover & finish time
void visit(Graph G, List s, int x, int *time) {
    G->discTime[x] = ++(*time);
    G->color[x] = 0;

    int y;
    moveFront(G->edges[x]);
    while (index(G->edges[x]) >= 0) {
        y = get(G->edges[x]);
        if (G->color[y] == -1) {
            G->parent[y] = x;
            visit(G, s, y, time);
        }
        moveNext(G->edges[x]);
    }
    G->color[x] = 1;
    G->finTime[x] = ++(*time);
    prepend(s, x);
}

// Other operations -----------------------------------------------------------

// Prints the edges of the Graph to an outfile
void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < getOrder(G)+1; i++) {
        fprintf(out, "%d: ", i);
        printList(out, getEdges(G, i));
    }
}

// Makes a copy of Graph G but each arc direction is reversed
Graph transpose(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling transpose() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    // Copying each value into its respective place in the new Graph
    Graph T = newGraph(getOrder(G));
    for (int i = 1; i < getOrder(G)+1; i++) {
        T->color[i] = G->color[i];
        T->parent[i] = G->parent[i];
        T->discTime[i] = G->discTime[i];
        T->finTime[i] = G->finTime[i];
    }

    // Reversing each arc
    int v;
    for (int u = 1; u < getOrder(G)+1; u++) {
        moveFront(G->edges[u]);
        while (index(G->edges[u]) >= 0) {
            v = get(G->edges[u]);
            addArc(T, v, u);
            moveNext(G->edges[u]);
        }
    }
    return T;
}

Graph copyGraph(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling copyGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    Graph nG = newGraph(getOrder(G));
    // Copying each value into its respective place in the new Graph
    for (int i = 1; i < getOrder(G)+1; i++) {
        nG->color[i] = G->color[i];
        nG->parent[i] = G->parent[i];
        nG->discTime[i] = G->discTime[i];
        nG->finTime[i] = G->finTime[i];
    }

    for (int i = 0; i < getOrder(G)+1; i++) {
        freeList(&(nG->edges[i])); // Frees memory for initialized list
        nG->edges[i] = copyList(G->edges[i]); // Copies edge list to the new Graph
    }
    nG->size = getSize(G);
    return nG;
}

// Tester function to check if vertex edges are correct and sorted.
void displayEdges(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling displayEdges() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < getOrder(G)+1; i++) {
        printf("%d: ", i);
        displayList(G->edges[i]);
    }
}

// Tester function to check if vertex neighbors are correct and sorted. Also prints
// the discover time, finish time, and parent of each vertex
void displayAll(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling displayEdges() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < getOrder(G)+1; i++) {
        printf("%d: ", i);
        displayList(G->edges[i]);
    }

    printf("\nDiscover Time: \n");
    for (int i = 1; i < getOrder(G)+1; i++) {
        printf("%d: %d\n", i, G->discTime[i]);
    }
    printf("\nFinish Time: \n");
    for (int i = 1; i < getOrder(G)+1; i++) {
        printf("%d: %d\n", i, G->finTime[i]);
    }
    printf("\nParent: \n");
    for (int i = 1; i < getOrder(G)+1; i++) {
        printf("%d: %d\n", i, G->parent[i]);
    }  
}