#Linked List

A linked list is a pretty simple data structure. This image stolen from
wikipedia gives you an overview of what they look like:

![](http://upload.wikimedia.org/wikipedia/commons/thumb/6/6d/Singly-linked-list.svg/816px-Singly-linked-list.svg.png)


basically we have a series of nodes, and each node has either some data or
a pointer to some data and a pointer to the next node. Cool! This lets us so
some fun things, like insert new nodes between existing ones, and delete nodes
without affecting the surrounding nodes.

There are a couple different kinds of linked lists, several of which I've
implemented.

##Singly Linked List

A singly linked list is probably the most simple, and is the variant which
stores the least information about other nodes. This is sort of a trade-off: we
get a slight decrease in storage size, but certain operations (like append
operations, or reversing the list) are not efficient.

Anyway, my singly linked list implementation is in `singlylinked.h`, with tests
and so on in `single.c`. If you want to see those tests you can do:

```bash
gcc single.c -o single.bin
./single.bin
```

Nice! Let's dig into what we've got going on here a little. Basically, to
start off we need some structs to represent nodes in our list, and also to
hold a reference to the first and last elements of the list. We'll call
these `node` and `list`, respectively (creative naming!):

```C
typedef struct node {
    struct node *cdr;
    char *data;
} node;

typedef struct list {
    node *car;
    node *tail;
} list;
```

So each `node` has a pointer to some string (our data) and to `cdr`, which
is the rest of the list. I took this naming convention from Scheme because
I like it.

`cdr` is always going to be a pointer to either another node in the list
or to the sentinel node. A sentinal node is basically a special node which
signifies the end of the list, we add it when we initialize the list.
Speaking of which, how do we initialize a list? Well, it looks like this:

```C
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
```

So we have a function `listinit` which returns a pointer to a list. We
also allocate a `node` which has no data in it (`sentinel->data = '\0'`).
We tell our list that this sentinel is the end by assigning it to
`newlist->tail`. For now, since we have no other list elements, the
sentinel node is both the first and last element, so it's also the `car`
of this list. Cool!

Since the singly linked list makes some things a bit tricky it's nice to
have this sentinel node. How I went about implementing all this is a bit
strange, I think, but in order to work with our list we need a helper
function, `nodegen`, which takes in the data we want to store and returns
a reference to that node. We can use this along with `insertstart`, which
inserts a `node` at the head of the list (the most efficient insert operation
we can do without knowing a `node` pointer already):

```C
node *nodegen(char *input)
{ // make a new node, returns ptr
    node *newnode;
    newnode = malloc(sizeof *newnode);
    newnode->data = input;
    return newnode;
}

int insertstart(list *list, node *insert)
{
    insert->cdr = list->car;
    list->car = insert;
    return 0;
}
```

This is how we might use this together:

```C
list *mylist = listinit();
char *strings[] = {"monday", "tuesday", "wednesday", "thursday",
     "friday", "saturday", "sunday"};
int i;
for (i = 0; i < 7; i++) {
    insertstart(mylist, nodegen(strings[i]));
}
```

This will give us a linked list, with the days of the week backwards!
Handy! You can look in `single.c` for more examples of basic operations on
this list. I wrote a couple more operations on the list, including `printlist`,
`appendlist`, `listsearch`, `destroylist`, and a few others. Since this is
a singly linked list some of these are not great algorithms (`appendlist`, for
instance, requires us to walk down the entirety of the list in order to locate
the penultimate `node`, whose `cdr` is the sentinel node).

Check out `singlylinked.h` for more!

##Doubly Linked List

A doubly linked list is a lot like a singly linked list, just, well,
doubly linked? Exactly! Anyway, this is what the relevant structs look
like:

```C
typedef struct node {
    struct node *previous;
    struct node *next;
    char *data;
} node;

typedef struct list {
    node *head;
    node *tail;
} list;
```

Like before we define a `node` struct, which both holds the info about
nodes around it and the data we want to store. Then we have a `list`
struct, which holds the head and tail of the list (the first and last
elements, respectively). Cool!

One opperation that is a lot more efficient with the doubly linked list is
appending a list to an existing list. Here's the function to do that:

```C
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
```

We can see why that is: before we had to traverse the whole list in order
to locate the node which was going to 'join' the two lists (the node which
would have a pointer to `head` of `second` as `next`). Now though, we
store the tail, so we can just go backwards by one from there! Nice.
