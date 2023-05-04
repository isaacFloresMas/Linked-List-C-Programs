#****************************************************************************** 
# Isaac Flores, isgflore 
# 2023 Spring CSE101 PA2
# Makefile
# File Compiler
#****************************************************************************** 

#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 2
#
# make                   makes FindPath
# make Graph             makes Graph
# make GraphTest         makes GraphTest
# make GraphClient       makes GraphClient
# make clean             removes all binaries
# make checkTest         checks GraphTest for memory errors
# make checkFindPath     checks FindPath for memory errors
#------------------------------------------------------------------------------

FindPath: FindPath.o Graph.o List.o
	gcc -std=c17 -Wall -o FindPath FindPath.o Graph.o List.o

Graph: Graph.o List.o
	gcc -std=c17 -Wall -o Graph Graph.o List.o

GraphTest: GraphTest.o Graph.o List.o
	gcc -std=c17 -Wall -o GraphTest GraphTest.o Graph.o List.o

GraphClient: GraphClient.o Graph.o List.o
	gcc -std=c17 -Wall -o GraphClient GraphClient.o Graph.o List.o

%.o: %.c
	gcc -std=c17 -Wall -c $<

clean:
	rm -f Graph GraphTest GraphClient FindPath *.o

checkTest: 
	valgrind --leak-check=full GraphTest

checkFindPath:
	valgrind --leak-check=full FindPath in1 out1
