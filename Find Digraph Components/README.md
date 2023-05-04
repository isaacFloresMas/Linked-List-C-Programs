# PA3: Digraphs & Depth First Search

This program creates a digraph from a given input file. The program then runs a depth first search algorithm on the digraph and the transpose of the digraph. This allows the program to find the strongly connected components of the digraph. The adjacency list of the digraph, as well as the strongly connected components are written into a given outfile.

## Warnings and Issues:

This program was designed for the Unix timeshare. You should run this program on the same environment to guarantee no errors arise.

## Files Included:

`List.c`: List.c contains a doubly linked list ADT and a node ADT. The linked list contains a cursor that acts as a highlighter for the current element in the list. This is used as a stack inside the depth first search algorithm.

`List.h`: List.h links the list ADT to Graph.c, FindComponents.c, & GraphTest.c so the linked list and its operations can be used in those files.

`Graph.c`: Graph.c contains the implementation of the Graph ADT. The graph is represented by an adjacency list and can represent undirected or directed graphs. In this assignment, it represents a digraph and contains a depth first search algorithm.

`Graph.h`: Graph.h links the Graph ADT to FindComponents.c & GraphTest.c so the Graph and its operations can be used in those files.

`GraphTest.c`: A tester function for the Graph ADT to ensure each function returns the desired results.

`FindComponents.c`: The client program which creates a digraph from an input file. The program prints out each vertices edges and the strongly connected components of the digraph.

`Makefile`: Compiles and builds the entire program.

`README.md`: A table of contents for the PA3 program.
