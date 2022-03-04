#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "List.h"

List* ListCtr ()
{
    List* list = (List*) calloc (1, sizeof (List));
    if (list == nullptr)
        return nullptr;

    list -> head = (ListItem*) calloc (1, sizeof (ListItem));

    if (list -> head == nullptr)
        return nullptr;

    list -> size = 0;
    list -> head -> data = 0;
    list -> head -> next = list -> head;
    list -> head -> prev = list -> head;

    return list;
}

void ListDtr (List* list)
{
    assert (list);

    ListItem* itemToDel = nullptr;
    ListItem* prevItem = list -> head -> prev;

    do
    {
        itemToDel = prevItem;
        prevItem = prevItem -> prev;

        itemToDel -> data = 0;
        itemToDel -> next = nullptr;
        itemToDel -> prev = nullptr;

        free (itemToDel);
    }
    while (itemToDel != list -> head);

    list -> head = nullptr;
    list -> size = 0;
    
    free (list);
}


ListItem* ListInsert (List* list, ListItem* item, int data)
{
    assert (list);
    assert (item);

    if (item == list -> head)
        return nullptr;

    ListItem* newItem = (ListItem*) calloc (1, sizeof (ListItem));
    if (newItem == nullptr)
       return nullptr; 

    newItem -> data = data;

    item -> prev -> next = newItem;
    newItem -> prev = item -> prev;

    newItem -> next = item;
    item -> prev = newItem;

    list -> size ++;

    return newItem;
}

ListItem* ListAdd (List* list, int data)
{
    assert (list);

    ListItem* newItem = (ListItem*) calloc (1, sizeof (ListItem));
    if (newItem == nullptr)
       return nullptr; 

    newItem -> data = data;

    list -> head -> prev -> next = newItem;
    newItem -> prev = list -> head -> prev;

    newItem -> next = list -> head;
    list -> head -> prev = newItem;

    list -> size ++;

    return newItem;
}

ListItem* ListDelete (List* list, ListItem* item)
{
    assert (list);
    assert (item);

    if (item == list -> head)
        return nullptr;

    ListItem* newptr = nullptr;
    if (item -> next != list -> head)
        newptr = item -> next;
    else
        newptr = item -> prev;

    item -> prev -> next = item -> next;
    item -> next -> prev = item -> prev;

    item -> next = nullptr;
    item -> prev = nullptr;
    item -> data = 0;

    free (item);

    list -> size --;

    return newptr;
}


ListItem* ListSet (ListItem* item, int data)
{
    assert (item);

    item -> data = data;

    return item;
}

int ListGet (ListItem* item)
{
    assert (item);

    return item -> data;
}

bool ListDump (List* list)
{
    assert (list);

    system ("mkdir -p ./dump");
    FILE* file = fopen ("./dump/test.dot", "w");

    fprintf (file, "digraph G{\n");

    fprintf (file, "graph [rankdir = LR];\n"); 

    ListItem* item = list -> head;

    do
    {
        fprintf (file, "subgraph cluster%p                          \
                        {                                           \
                            style = \"filled, rounded\";            \
                            fillcolor = \"#b0ffb0\";                \
                            color = \"#b0ffb0\";                    \
                                                                    \
                            label = \"%p\"                          \
                                                                    \
                            item%p                                  \
                            [                                       \
                                style = \"rounded, filled\",        \
                                fillcolor = \"#ffffff\",            \
                                shape = \"record\",                 \
                                label = \"<addr> addr: %p |         \
                                          <next> nxt: %p |         \
                                          <prev> prv: %p |         \
                                          <data> dat: %d\"         \
                            ];                                      \
                        }\n", item, item, item, item, item -> next, item -> prev, item -> data);
        if (item -> next != list -> head)
            fprintf (file, "item%p -> item%p [style = invis, weight = 100, minlen = 2];\n", item, item -> next);

        fprintf (file, "item%p : next -> item%p : addr [weight = 1, minlen = 0];\n", item, item -> next);
        fprintf (file, "item%p : prev -> item%p : addr [weight = 1, minlen = 0];\n", item, item -> prev);

        item = item -> next;
    }
    while (item != list -> head);

    fprintf (file, "}\n");

    fclose (file);

    system ("dot ./dump/test.dot -T svg -o ./dump/test.svg");


    return 1;
}
