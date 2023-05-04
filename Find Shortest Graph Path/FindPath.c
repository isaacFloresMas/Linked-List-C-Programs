/********************************************************************************* 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA2
* FindPath.c 
* Finds shortest path from a source vertex to a given vertex in a graph
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
    int left, right, length;

    // Checking for the correct amount of arguments
    if (argc != 3) {
        fprintf(stderr, "FindPath Error: Incorrect number of arguments. Correct usage should be ./FindPath <input file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    // Opening infile and outfile for reading and writing respectively
    if ((fIN = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "FindPath Error: Unable to open %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((fOUT = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "FindPath Error: Unable to open %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    // End of opening infile and outfile for reading and writing respectively

    // Reading the number of vertices of the graph and creating new graph
    fscanf(fIN, "%d\n", &length);
    Graph G = newGraph(length);
    // End of eading the number of vertices of the graph and creating new graph

    // Reading and adding in edges
    while (!feof(fIN)) {
        fscanf(fIN, "%d %d\n", &left, &right);
        if (left == 0 && right == 0) {
            break;
        }
        addEdge(G, left, right);
    }
    printGraph(fOUT, G);
    // End of reading and adding in edges

    // Running BFS for the desired source and printing the shortest path
    List pathL = newList();
    while (!feof(fIN)) {
        fscanf(fIN, "%d %d\n", &left, &right);
        if (left == 0 && right == 0) {
            break;
        }
        fprintf(fOUT, "\n");
        BFS(G, left);
        if (getDist(G, right) != INF) {
            fprintf(fOUT, "The distance from %d to %d is %d\n", left, right, getDist(G, right));
            fprintf(fOUT, "A shortest %d-%d path is: ", left, right);
            getPath(pathL, G, right);
            printList(fOUT, pathL);
        }
        else {
            fprintf(fOUT, "The distance from %d to %d is infinity\n", left, right);
            fprintf(fOUT, "No %d-%d path exists\n", left, right);
        }
        clear(pathL);
    }
    // End of running BFS for the desired source and printing the shortest path

    // Freeing allocated memory and closing files
    freeGraph(&G);
    freeList(&pathL);
    fclose(fIN);
    fclose(fOUT);
    // End of freeing allocated memory and closing files

    return 0;
}