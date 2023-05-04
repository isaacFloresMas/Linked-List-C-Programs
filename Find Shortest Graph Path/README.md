# PA2: Breadth First Search, Shortest Paths, & Graphs

This program takes an input file which holds the number of vertices and edges of the desired graph. This graph is created and the neighbors of each vertex are printed to the outfile. The desired path(s) from s-x are read from the input file. The program prints out the shortest path from s-x to the outfile if it exists. The shortest path is found by conducting a breadth first search from the source vertex.

## Warnings and Issues:

This program was designed for the Unix timeshare. You should run this program on the same environment to guarantee no errors arise.

## Files Included:

`List.c`: List.c contains a doubly linked list ADT and a node ADT. The linked list contains a cursor that acts as a highlighter for the current element in the list. This is used to create a FIFO Queue and to hold the edges of each vertex.

`List.h`: List.h links the list ADT to Graph.c, FindPath.c, & GraphTest.c so the linked list and its operations can be used in those files.

`Graph.c`: Graph.c contains the implementation of the Graph ADT. The graph is represented by an adjacency list and can represent undirected or directed graphs. Also contains a breadth first search function from a given source vertex.

`Graph.h`: Graph.h links the Graph ADT to FindPath.c & GraphTest.c so the Graph and its operations can be used in those files.

`GraphTest.c`: A tester function for the Graph ADT to ensure each function returns the desired results.

`FindPath.c`: The client program which creates a Graph from an input file. The program prints out each vertices neighbors and the shortest path from a source vertex to a given vertex to an outfile.

`Makefile`: Compiles and builds the entire program.

`README.md`: A table of contents for the PA2 program.
