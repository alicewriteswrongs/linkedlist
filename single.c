#include <stdio.h>
#include "singlylinked.h"

// this is just a file to test my singly linked list
void main()
{
    list *mylist = listinit();

    printf("make a list, and add stuff!\n");
    char *strings[] = {"monday", "tuesday", "wednesday", "thursday",
         "friday", "saturday", "sunday"};
    int i;
    for (i = 0; i < 7; i++) {
        insertstart(mylist, nodegen(strings[i]));
    }
    printlist(mylist);
    printf("\n");

    printf("delete the first item\n");
    deletebeginning(mylist);
    printlist(mylist);
    printf("\n");

    printf("find 'thursday', add 'pants' afterwards:\n");
    node *thurs = listsearch(mylist, "thursday");
    insert(thurs, nodegen("pants"));
    printlist(mylist);
    printf("\n");

    printf("Insert 'shoes' at the beginning of the list\n");
    insertstart(mylist, nodegen("shoes"));
    printlist(mylist);
    printf("\n");

    printf("Make a new list, append it to our first\n");
    list *secondlist = listinit();
    char *newstrings[] = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY",
         "FRIDAY", "SATURDAY", "SUNDAY"};
    for (i = 0; i < 7; i++) {
        insertstart(secondlist, nodegen(newstrings[i]));
    }
    appendlist(mylist, secondlist);
    printlist(mylist);

    destroylist(mylist);
}




    


