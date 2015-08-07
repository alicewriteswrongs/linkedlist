#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    struct node *previous;
    struct node *next;
    char *data;
} node;

typedef struct list {
    node *head;
    node *tail;
} list;

list *listinit();
node *nodegen(char *input);
void printlist(list *toprint);
node *listsearch(list *search, char *query);
void insertafter(node *after, node *newnode);
void prepend(list *list, node *newnode);
void appendlist(list *first, list *second);

// functions

list *listinit()
{
    list *newlist;
    newlist = malloc(sizeof newlist);
    node *sentinel;
    sentinel = malloc(sizeof sentinel);

    sentinel->data = '\0';
    sentinel->next = sentinel;
    sentinel->previous = sentinel;

    newlist->head = sentinel;
    newlist->tail = sentinel;
    
    return newlist;
}

node *nodegen(char *input)
{
    node *newnode;
    newnode = malloc(sizeof newnode);
    newnode->data = input;
    return newnode;
}

void prepend(list *list, node *newnode)
{
    newnode->next = list->head;
    list->head->previous = newnode;
    list->head = newnode;
}
    
void insertafter(node *after, node *newnode)
{ // insert newnode after after (lol)
    newnode->previous = after;
    after->next->previous = newnode;
    newnode->next = after->next;
    after->next = newnode;
}

void printlist(list *toprint)
{
    node *iternode = toprint->head;
    while (iternode != toprint->tail) {
	printf("%s\n", iternode->data);
	iternode = iternode->next;
    }
}

node *listsearch(list *search, char *query)
{
    node *iternode;
    iternode = search->head;

    while (iternode != search->tail) {
        if (strcmp(iternode->data, query) == 0)
            return iternode;
        else
            iternode = iternode->next;
    }
    return search->tail;
}

void appendlist(list *first, list *second)
{
    node *last;
    last = first->tail->previous;
    last->next = second->head;
    second->head->previous = last;
    free(first->tail);
    first->tail = second->tail;
    free(second);
}
