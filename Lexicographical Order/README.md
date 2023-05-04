# PA1: List ADT and Lexicographical Ordering

This program takes an input file and indirectly sorts each sentence alphabetically. Then each sorted sentence is written into an output file.

## Warnings :

This program was designed for the Unix timeshare. You should run this program on the same environment to guarantee no errors arise.

## Files Included:

`Lex.c`: Lex.c is the main file that uses a linked list to indirectly sort an input file. This data is written into the given outfile. Lex.c must be ran by entering ./Lex <input file> <output file> into the terminal.

`List.c`: List.c contains a doubly linked list ADT and a node ADT. The linked list contains a cursor that acts as a highlighter for the current element in the list.

`ListTest.c`: ListTest.c contains testing functions used to ensure the List ADT is functional.

`List.h`: List.h links the list ADT to Lex.c so the linked list and its operations can be used in Lex.c.

`Makefile`: Compiles and builds the entire program.

`README.md`: A table of contents for the PA1 program.
