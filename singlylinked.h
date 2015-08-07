#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// nodes in our list
typedef struct node {
    struct node *cdr;
    char *data;
} node;

// pointer to the first element
typedef struct list {
    node *car;
    node *tail;
} list;

// function declarations
list *listinit();
int insert(node *after, node *new);
node *nodegen(char *data);
void deletenext(node *after);
int insertstart(list *list, node *insert);
void deletebeginning(list *list);
void printlist(list *list);
node *listsearch(list *list, char *query);
void destroylist(list *list);
int appendlist(list *first, list *second);

// list operation functions

node *listsearch(list *list, char *query)
{
    node *first = list->car;
    while (first != list->tail) {
        if (strcmp(first->data, query) == 0)
            return first;
        else 
            first = first->cdr;
    }
    return list->tail;
}

void destroylist(list *list)
{
    while (list->car != list->tail) {
        deletebeginning(list);
    }
    free(list->tail);
    free(list);
}

int appendlist(list *first, list *second)
{ // append the second list to the first
  // this is super inefficient because this isn't
  // a circular or double linked list
    node *iternode = first->car;
    while (iternode != first->tail) {
        if (iternode->cdr == first->tail) {
            iternode->cdr = second->car;
            first->tail = second->tail;
            free(first->tail);
            free(second);
            return 0;
        } else {
            iternode = iternode->cdr;
        }
    }
    return 1;
}

void printlist(list *list)
{
    node *first = list->car;
    node *temp;

    while (first != list->tail) {
        printf("%s\n", first->data);
        temp = first;
        first = temp->cdr;
    }
}

list *listinit() 
{ // initialize a list with a sentinel node

    list *newlist;
    newlist = malloc(sizeof *newlist);
    node *sentinel;
    sentinel = malloc(sizeof *sentinel);
    if (sentinel == NULL)
        return 0; 

    sentinel->data = '\0';
    sentinel->cdr = sentinel;
    newlist->car = sentinel;
    newlist->tail = sentinel;

    return newlist;
}

int insert(node *after, node *new)
{ // insert 'new' following 'after'
    new->cdr = after->cdr;
    after->cdr = new;
    return 0;
}

int insertstart(list *list, node *insert)
{
    insert->cdr = list->car;
    list->car = insert;
    return 0;
}

node *nodegen(char *input)
{ // make a new node, returns ptr
    node *newnode;
    newnode = malloc(sizeof *newnode);
    newnode->data = input;
    return newnode;
}

void deletenext(node *after)
{ // delete the node following
    node *toremove = after->cdr;
    after->cdr = toremove->cdr;
    free(toremove);
}

void deletebeginning(list *list)
{ //delete the node at the beginning
    node *toremove = list->car;
    list->car = toremove->cdr;
    free(toremove);
}


