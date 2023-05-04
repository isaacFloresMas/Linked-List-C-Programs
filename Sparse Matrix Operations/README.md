# PA4: Sparse Matrix Operations

This program computes matrix operations on two sparse matrices given from an input file. The program computes and prints 𝐴, 𝐵, (1.5)𝐴, 𝐴 + 𝐵, 𝐴 + 𝐴, 𝐵 − 𝐴, 𝐴 − 𝐴, 𝐴<sup>T</sup> , 𝐴𝐵 and 𝐵<sup>2</sup>. A matrix is sparse if the number of non-zero entries is small compared to the total number of entries.

## Warnings and Issues:

This program was designed for the Unix timeshare. You should run this program on the same environment to guarantee no errors arise.

## Files Included:

`Sparse.c`: Sparse.c is the client file that takes an input file that provides the location and value of entries for two matrices. Multiple operations are computed with both matrices and the result is printed to an outfile.

`Matrix.c`: Matrix.c contains the implementation for the Sparse Matrix ADT. The file also includes addition, subtraction, scalar, multiplication, and transpose operations for a matrix or matrices.

`Matrix.h`: Matrix.h links the Sparse Matrix ADT to Sparse.c so the matrix and its operations can be used in that file.

`MatrixTest.c`: MatrixTest.c contains testing functions used to ensure the Sparse Matrix ADT is functional.

`List.c`: List.c contains a doubly linked list ADT and a node ADT. The linked list contains a cursor that acts as a highlighter for the current element in the list. This is used to contain the entries for each row of a matrix.

`List.h`: List.h links the list ADT to Matrix.c and Sparse.c so the linked list and its operations can be used in those files.

`ListTest.c`: ListTest.c contains testing functions used to ensure the List ADT is functional.

`Makefile`: Compiles and builds multiple programs.

`README.md`: A table of contents for the PA4 program.
