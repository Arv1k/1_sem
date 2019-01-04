#include "list_p.h"

int main() {
    list myList = {};
    ListCtor(&myList);

    ListPush_front(&myList, 7);
    list_elem* pos = ListPush_front(&myList, 6);
    ListInsert_before(&myList, 11, pos);

    DumpList(&myList);

    ListDtor(&myList);

    DumpList(&myList);
}