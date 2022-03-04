#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

const char CANARY = 21;


typedef struct _ListItem_
{
    int data;
    struct _ListItem_* next;
    struct _ListItem_* prev;
} ListItem;

typedef struct
{
    ListItem* head;

    unsigned int size;
} List;

List*     ListCtr        ();
void      ListDtr        (List* list);

ListItem* ListInsert     (List* list, ListItem* item, int data);
ListItem* ListAdd        (List* list, int data);
ListItem* ListDelete     (List* list, ListItem* item);

ListItem* ListSet        (ListItem* item, int data);
int       ListGet        (ListItem* item);

bool      ListDump       (List* list);

#endif
