#****************************************************************************** 
# Isaac Flores, isgflore 
# 2023 Spring CSE101 PA1 
# Makefile
# File Compiler
#****************************************************************************** 

#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListClient        makes ListClient
# make clean             removes all binaries
# make checkClient       checks ListClient for memory errors
# make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------

Lex: Lex.o List.o
	gcc -std=c17 -Wall -o Lex Lex.o List.o
	
List: List.o
	gcc -std=c17 -Wall -o List List.o

ListTest: ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o

ListClient: ListClient.o List.o
	gcc -std=c17 -Wall -o ListClient ListClient.o List.o

%.o: %.c
	gcc -std=c17 -Wall -c $<

clean :
	rm -f Lex ListClient List ListTest *.o

checkClient : 
	valgrind --leak-check=full ListClient

checkLex :
	valgrind --leak-check=full Lex in3 blah3
