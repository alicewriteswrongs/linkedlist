#include <stdio.h>
#include <string.h>
#include "doublylinked.h"

void main()
{
    list *mylist = listinit();

    char *strings[] = {"monday", "tuesday",
        "wednesday", "thursday", "friday",
        "saturday", "sunday"};
    int i;
    for (i = 0; i < 7; i++) {
        prepend(mylist, nodegen(strings[i]));
    }
    printlist(mylist);

    node *tuesday;
    tuesday = listsearch(mylist, "tuesday");

    insertafter(tuesday, nodegen("pants"));
    printlist(mylist);

    // make a new list to play with
    list *newlist = listinit(); 

    for (i = 0; i < 7; i++) {
        prepend(newlist, nodegen(strings[i]));
    }

    printf("\n\n trying out the append operation\n\n");
    appendlist(mylist, newlist);
    printlist(mylist);

}

