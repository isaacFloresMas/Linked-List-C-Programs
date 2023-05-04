#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 4
#
# make                   makes Sparse
# make Matrix            makes Matrix
# make MatrixTest        makes MatrixTest
# make List              makes List
# make ListTest          makes ListTest
# make clean             removes all binaries
# make checkMatrix       checks MatrixTest for memory errors
# make checkSparse       checks Sparse for memory errors
#------------------------------------------------------------------------------

Sparse: Sparse.o Matrix.o List.o
	gcc -std=c17 -Wall -o Sparse Sparse.o Matrix.o List.o

Matrix: Matrix.o List.o
	gcc -std=c17 -Wall -o Matrix Matrix.o List.o

MatrixTest: MatrixTest.o Matrix.o List.o
	gcc -std=c17 -Wall -o MatrixTest MatrixTest.o Matrix.o List.o

List: List.o
	gcc -std=c17 -Wall -o List List.o

ListTest: ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o

%.o: %.c
	gcc -std=c17 -Wall -c $<

clean:
	rm -f Sparse Matrix MatrixTest List ListTest *.o

checkMatrix: 
	valgrind --leak-check=full ./MatrixTest

checkSparse:
	valgrind --leak-check=full Sparse in1.txt out1.txt
