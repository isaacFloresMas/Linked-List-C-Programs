/********************************************************************************* 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA2
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

// struct creation ------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj {
    List *edges; // An array of Lists whose ith element contains the edges of vertex i.
    int *color; // An array of ints (or chars, or strings) whose ith element is the color 
                // (white, gray, black) of vertex i.
    int *parent; // An array of ints whose ith element is the parent of vertex i.
    int *distance; // An array of ints whose ith element is the distance from the 
                   // (most recent) source to vertex i.
    int order; // number of vertices
    int size; // number of edges
    int source; // label of the vertex that was most recently used as source for BFS.
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
    G->distance = calloc(n+1, sizeof(int));
    for (int i = 0; i < n+1; i++) {
        G->edges[i] = newList();
    }
    G->order = n;
    G->size = 0;
    G->source = NIL;
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
        free((*pG)->distance); // = calloc(n+1, sizeof(int));
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

// Returns the last source vertex in G, or NIL if BFS has not been conducted
int getSource(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
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
    if (G->source == NIL) {
        return NIL;
    } else {
        return G->parent[u];
    }
}

// Returns the distance between the source vertex and the given vertex u
int getDist(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getDist() for a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }
    if (G->source == NIL) {
        return INF;
    } else {
        return G->distance[u];
    }
}

// Recursively finds the path between the source vertex and the given vertex u
void getPath(List L, Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getPath() for a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        fprintf(stderr, "Graph Error: calling getPath() when BFS() hasn't been called\n");
        exit(EXIT_FAILURE);
    }

    int s = getSource(G);
    if (u == s) {
        append(L, u);
    }
    else if (G->parent[u] == NIL) {
        append(L, NIL);
    }
    else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
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
    G->source = NIL;
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
                break;
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

// Conducts a Breadth First Search from the given source vertex s
void BFS(Graph G, int s) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (s < 1 || s > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling BFS() for a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < getOrder(G)+1; i++) {
        G->color[i] = -1; // -1 = white, 0 = grey, 1 = black
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = 0;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Queue = newList();
    append(Queue, s);
    int x;
    int curr;
    while (length(Queue) != 0) {
        x = front(Queue);
        deleteFront(Queue);
        moveFront(G->edges[x]);
        while (index(G->edges[x]) >= 0) {
            if (G->color[get(G->edges[x])] == -1) {
                curr = get(G->edges[x]);
                G->color[curr] = 0; // = grey
                G->distance[curr] = G->distance[x] + 1;
                G->parent[curr] = x;
                append(Queue, curr);
            }
            moveNext(G->edges[x]);
        G->color[x] = 1; // = black
        }
    }
    G->source = s;
    freeList(&Queue);
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

// Tester function to check if vertex neighbors are correct and sorted
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

// Tester function to check if path is correct
void printPath(Graph G, int s, int x) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling printPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (x == s) {
        printf("%d\n", s);
    }
    else if (G->parent[x] == NIL) {
        printf("%d is not reachable from %d\n", x, s);
    }
    else {
        printPath(G, s, G->parent[x]);
        printf("%d\n", x);
    }
}
