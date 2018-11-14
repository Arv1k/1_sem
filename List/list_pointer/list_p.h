#ifndef LIST_POINTER_LIST_P_H
#define LIST_POINTER_LIST_P_H


#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <cstring>

#define assert_list(nameList) {\
    if ( !(ListOK(nameList)) ) {\
        printf("| !!!Assertion failed!!!\n");\
        printf("|       what: ListOK(%s),\n", #nameList);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        abort();\
    }\
}

#define assert_var(variable) {\
    if ( !(std::isfinite(variable)) ) {\
        printf("| !!!Assertion failed!!!\n");\
        printf("|       what: ListOK(%s),\n", #variable);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        abort();\
    }\
}

typedef int data_t;


const int yad_count = 119;
const data_t yad_elem = 167;


enum ListErrors {
    PUSH_FRONT_ERROR = 65,
    PUSH_BACK_ERROR = 66,
    POP_FRONT_ERROR = 67,
    POP_BACK_ERROR = 68,
};

struct list_elem {
    data_t Info = yad_elem;
    list_elem* Next = nullptr;
    list_elem* Prev = nullptr;
};

struct list {
    list_elem* Head = nullptr;
    list_elem* Tail = nullptr;
    size_t count = yad_count;
};


bool ListCtor(list* nameList);

bool ListPop_front(list* nameList);

bool ListPop_back(list* nameList);

list_elem* ListPush_front(list* nameList, data_t elem);

list_elem* ListPush_back(list* nameList, data_t elem);

list_elem* ListInsert_before(list* nameList, data_t elem, list_elem* position);

list_elem* ListInsert_after(list* nameList, data_t elem, list_elem* position);

bool ListDelete(list* nameList, list_elem* position);

bool ListDtor(list* nameList);

bool ListOK(list* nameList);

void DumpList(list* nameList);

#endif //LIST_POINTER_LIST_P_H
