#include "list_p.h"

int main() {
    list myList = {};
    ListCtor(&myList);

    list_elem* pos = ListPush_front(&myList, 6);

    ListPush_front(&myList, 7);

    ListPush_front(&myList, 8);

    ListPush_front(&myList, 9);

    DumpList(&myList);

    ListInsert_after(&myList, 9 , pos);

    DumpList(&myList);

    ListDtor(&myList);
}