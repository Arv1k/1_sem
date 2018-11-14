#include "list_p.h"

int main() {
    list myList = {};
    ListCtor(&myList);

    ListPush_front(&myList, 6);

    ListPush_front(&myList, 7);

    ListPush_front(&myList, 8);

    ListPush_front(&myList, 9);

    DumpList(&myList);

    ListDtor(&myList);

    DumpList(&myList);
}