/********************************************************************************* 
* Isaac Flores, isgflore 
* 2023 Spring CSE101 PA4
* List.c 
* Doubly Linked List ADT
*********************************************************************************/ 

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "List.h"

// struct creation ------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {
    ListElement data;
    Node next;
    Node prev;
} NodeObj; 

// private ListObj type
typedef struct ListObj {
    Node head;
    Node tail;
    Node cursor;
    int length;
    int index;
} ListObj;

typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

// Creates and returns a new node.
Node newNode(ListElement dataIn) {
    Node N = malloc(sizeof(NodeObj));
    assert(N != NULL);
    N->data = dataIn;
    N->next = N->prev = NULL;
    return N;
}

// Frees all heap memory associated with *n, and sets *n to NULL.
void freeNode(Node *n) {
    if (n != NULL && *n != NULL) {
        free(*n);
        *n = NULL;
    }
}

// Creates and returns a new empty List.
List newList(void) { 
    List L = malloc(sizeof(ListObj));
    assert(L != NULL);
    int NIL = -1;
    L->head = newNode(&NIL);
    L->tail = newNode(&NIL);
    L->head->next = L->tail;
    L->tail->prev = L->head;
    L->head->prev = L->tail->next = NULL;
    L->cursor = L->head;
    L->length = 0;
    L->index = -1;
    return(L);
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL) { 
    if (pL != NULL && *pL != NULL) {
        for (Node curr = (*pL)->head; curr != NULL;) {
            Node temp = curr->next;
            freeNode(&curr);
            curr = temp;
        }
    }
    free(*pL);
    *pL = NULL;
}


// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->index >=0) {
        return L->index;
    }
    return(-1);
}

// Returns front element of L. Pre: length()>0
ListElement front(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling front() on an empty list\n");
        exit(EXIT_FAILURE);
    }   
    return L->head->next->data;
}

// Returns back element of L. Pre: length()>0
ListElement back(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling back() on an empty list\n");
        exit(EXIT_FAILURE);
    }
    return L->tail->prev->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
ListElement get(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling get() on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) <= -1) {
        fprintf(stderr, "List Error: calling get() when the cursor is undefined.\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    for (Node curr = L->head->next; curr != L->tail;) {
        Node temp = curr->next;
        freeNode(&curr);
        curr = temp;
    }
    L->head->next = L->tail;
    L->tail->prev = L->head;
    L->length = 0;
    L->index = -1;
}

// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, ListElement x) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling set() on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) <= -1) {
        fprintf(stderr, "List Error: calling set() when the cursor is undefined.\n");
        exit(EXIT_FAILURE);
    }

    L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) == 0) {
        return;
    }
    L->index = 0;
    L->cursor = L->head->next;
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) == 0) {
        return;
    }
    L->index = (L->length)-1;
    L->cursor = L->tail->prev;
}

/* If cursor is defined and not at front, move cursor one step toward the front of L; 
   if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing */
void movePrev(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->index == 0) {
        L->index = -1;
        L->cursor = L->head;
    }
    if (L->index > -1) {
        L->index -= 1;
        L->cursor = L->cursor->prev;
    }
}

/* If cursor is defined and not at back, move cursor one step toward the back of L; if cursor 
   is defined and at back, cursor becomes undefined; if cursor is undefined do nothing */
void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->index == L->length-1 && L->length != 0) {
        L->index = -1;
        L->cursor = L->head;
        return;
    }
    if (L->index > -1) {
        L->index += 1;
        L->cursor = L->cursor->next;
    }
}

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, ListElement x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(x);
    if (length(L) >= 0) {
        N->next = L->head->next;
        N->prev = L->head;
        N->next->prev = N;
        L->head->next = N;
        L->length += 1;
        L->index += 1;
    }
}

// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, ListElement x) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(x);
    if (length(L) >= 0) {
        N->next = L->tail;
        N->prev = L->tail->prev;
        L->tail->prev->next = N;
        L->tail->prev = N;
        L->length += 1;
    }
}

// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, ListElement x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling insertBefore() on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) <= -1) {
        fprintf(stderr, "List Error: calling insertBefore() when the cursor is undefined.\n");
        exit(EXIT_FAILURE);
    }

    Node New = newNode(x);
    New->prev = L->cursor->prev;
    New->next = L->cursor;
    L->cursor->prev->next = New;
    L->cursor->prev = New;
    L->length += 1;
    L->index += 1;
}

// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, ListElement x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling insertAfter() on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) <= -1) {
        fprintf(stderr, "List Error: calling insertAfter() when the cursor is undefined.\n");
        exit(EXIT_FAILURE);
    }

    Node New = newNode(x);
    New->next = L->cursor->next;
    New->prev = L->cursor;
    L->cursor->next->prev = New;
    L->cursor->next = New;
    L->length += 1;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling deleteFront() on an empty list.\n");
        exit(EXIT_FAILURE);
    }

    Node Bye = L->head->next;
    L->head->next = Bye->next;
    Bye->next->prev = L->head;
    L->length -= 1;
    L->index -= 1;
    freeNode(&Bye);
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling deleteBack() on an empty list.\n");
        exit(EXIT_FAILURE);
    }

    Node Bye = L->tail->prev;
    L->tail->prev = Bye->prev;
    Bye->prev->next = L->tail;
    L->length -= 1;
    if (L->index == L->length) {
        L->index = -1;
    }
    freeNode(&Bye);
}

// Delete the cursor's previous node
void deletePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deletePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling deletePrev() on an empty list.\n");
        exit(EXIT_FAILURE);
    }

    if (index(L) <= -1) {
        deleteBack(L);
        return;
    }
    Node curr = L->cursor->prev;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    L->length -= 1;
    L->index -= 1;
    freeNode(&curr);
}

// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling delete() on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) <= -1) {
        fprintf(stderr, "List Error: calling delete() when the cursor is undefined.\n");
        exit(EXIT_FAILURE);
    }

    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;
    L->length -= 1;
    L->index = -1;
    freeNode(&(L->cursor));
}


// Other operations -----------------------------------------------------------