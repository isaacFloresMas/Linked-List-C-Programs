/********************************************************************************* 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA3
* FindComponents.c 
* Finds the strongly connected components of a digraph
*********************************************************************************/ 

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char **argv) {
    FILE *fIN;
    FILE *fOUT;
    int left, right, n;

    // Checking for the correct amount of arguments
    if (argc != 3) {
        fprintf(stderr, "FindComponents Error: Incorrect number of arguments. Correct usage should be ./FindComponents <input file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    // Opening infile and outfile for reading and writing respectively
    if ((fIN = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "FindComponents Error: Unable to open %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((fOUT = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "FindComponents Error: Unable to open %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    // End of opening infile and outfile for reading and writing respectively

    // Reading the number of vertices of the graph and creating new graph
    fscanf(fIN, "%d\n", &n);
    Graph G = newGraph(n);
    // End of eading the number of vertices of the graph and creating new graph

    // Reading and adding in arcs
    while (!feof(fIN)) {
        fscanf(fIN, "%d %d\n", &left, &right);
        if (left == 0 && right == 0) {
            break;
        }
        addArc(G, left, right);
    }
    fprintf(fOUT, "Adjacency list representation of G:\n");
    printGraph(fOUT, G);
    // End of reading and adding in arcs

    // Conducting DFS on G then on transpose(G)
    List S = newList();
    for (int i = 1; i < getOrder(G)+1; i++) {
        append(S, i);
    }
    DFS(G, S);
    Graph T = transpose(G);
    DFS(T, S);
    // End of conducting DFS on G then on transpose(G)

    // Gathering each start of the DFS forests
    int amount = 0;
    for (int i = 1; i < n+1; i++) {
        if (getParent(T, i) == NIL) {
            amount++;
        }
    }
    fprintf(fOUT, "\nG contains %d strongly connected components:\n", amount);
    // End of gathering each start of the DFS forests

    // Printing each component
    int x;
    int count = 1;
    List comp = newList();
    moveBack(S);
    while (index(S) >= 0) {
        x = get(S);
        prepend(comp, x);
        if (getParent(T, x) == NIL) { // Once a start vertex is reached, print and move on
            fprintf(fOUT, "Component %d: ", count);
            printList(fOUT, comp);
            clear(comp);
            count++;
        }
        movePrev(S);
    }
    // End of printing each component

    // Freeing all graphs, lists, and files used
    freeList(&S);
    freeList(&comp);
    freeGraph(&G);
    freeGraph(&T);
    fclose(fIN);
    fclose(fOUT);
    // End of freeing all graphs, lists, and files used
    return 0;
}