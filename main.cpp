#include <stdio.h>

#include "List.h"

int main ()
{
    List* list = ListCtr ();

    ListAdd (list, 10);
    ListAdd (list, 20);
    ListItem* item1 = ListAdd (list, 30);
    ListItem* item2 = ListAdd (list, 40);
    ListAdd (list, 50);

    ListInsert (list, item2, 2);
    ListDelete (list, item1);

    ListDump (list);

    ListDtr (list);

    return 0;
}
