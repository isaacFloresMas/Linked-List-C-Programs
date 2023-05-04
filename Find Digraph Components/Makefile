#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 3
#
# make                     makes FindComponents
# make Graph               makes Graph
# make GraphTest           makes GraphTest
# make GraphClient         makes GraphClient
# make clean               removes all binaries
# make checkTest           checks GraphTest for memory errors
# make checkFindComponents checks FindComponents for memory errors
#------------------------------------------------------------------------------

FindComponents: FindComponents.o Graph.o List.o
	gcc -std=c17 -Wall -o FindComponents FindComponents.o Graph.o List.o

Graph: Graph.o List.o
	gcc -std=c17 -Wall -o Graph Graph.o List.o

GraphTest: GraphTest.o Graph.o List.o
	gcc -std=c17 -Wall -o GraphTest GraphTest.o Graph.o List.o

GraphClient: GraphClient.o Graph.o List.o
	gcc -std=c17 -Wall -o GraphClient GraphClient.o Graph.o List.o

%.o: %.c
	gcc -std=c17 -Wall -c $<

clean:
	rm -f Graph GraphTest GraphClient FindComponents *.o

checkTest: 
	valgrind --leak-check=full ./GraphTest

checkFindComponents:
	valgrind --leak-check=full ./FindComponents in1.txt out1.txt
