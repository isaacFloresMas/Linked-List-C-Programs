/********************************************************************************* 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA1 
* Lex.c 
* Lexicographical Ordering
*********************************************************************************/ 

#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "List.h"

#define MAX_LINE_LENGTH 300

int main(int argc, char **argv) {
    FILE *fIN;
    FILE *fOUT;
    int n = 0;
    int letter;

    // Checking for the correct amount of arguments
    if (argc != 3) {
        fprintf(stderr, "Lex Error: Incorrect number of arguments. Correct usage should be ./Lex <input file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    // Opening infile and outfile for reading and writing respectively
    if ((fIN = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Lex Error: Unable to open %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((fOUT = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "Lex Error: Unable to open %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    // End of opening infile and outfile for reading and writing respectively

    // Getting line count and setting it to n
    while (!feof(fIN)) {
        letter = fgetc(fIN);
        if (letter == '\n') {
            n += 1;
        }
    }
    rewind(fIN);
    // End of getting line count

    // Allocating and filling the string array from the input
    char **readLines = malloc(n * sizeof(char *));
    if (readLines == NULL) {
        fprintf(stderr, "Lex Error: Failure when allocated memory for the string array");
        exit(EXIT_FAILURE);
    }
    for (int j = 0; j < n; j++) {
        readLines[j] = malloc(MAX_LINE_LENGTH);
    }

    for (int i = 0; i < n; i++) {
        fgets(readLines[i], MAX_LINE_LENGTH, fIN);
    }
    // End of allocating and filling the string array from the input

    // Start of Insertion Sort
    List inSort = newList();
    char *key;
    for (int j = 0; j < n; j++) {
        if (length(inSort) == 0) {
            append(inSort, j);
            continue;
        }
        key = readLines[j];
        moveBack(inSort);
        while (index(inSort) >= 0 && (strcmp(readLines[get(inSort)], key)) > 0) {
            movePrev(inSort);
        }
        if (index(inSort) == -1) {
            prepend(inSort, j);
        }
        else {
            insertAfter(inSort, j);
        }
    }
    
    // End of Insertion Sort

    // Writing lexicographic;y ordered data into outfile
    moveFront(inSort);
    int curNode;
    while (index(inSort) >= 0) {
        curNode = get(inSort);
        fprintf(fOUT, "%s", readLines[curNode]);
        moveNext(inSort);
    }
    // End of writing lexicographicly ordered data into outfile

    // Freeing the list, string array, and closing files
    for (int j = 0; j < n; j++) {
        free(readLines[j]);
    }
    fclose(fIN);
    fclose(fOUT);
    free(readLines);
    freeList(&inSort);
    // End of freeing list, string array, and closing files

    return 0;
}