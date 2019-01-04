#ifndef LIST_POINTER_LIST_P_H
#define LIST_POINTER_LIST_P_H


#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <cstring>

#define assert_list(nameList) {\
    if ( !(ListOK(nameList)) ) {\
        printf("| !!! Assertion failed !!!\n");\
        printf("|       what: ListOK(%s),\n", #nameList);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        printf("| !!! Look at DumpList !!!");\
        DumpList(nameList);\
        abort();\
    }\
}

#define assert_var(variable) {\
    if ( !(std::isfinite(variable)) ) {\
        printf("| !!!Assertion failed!!!\n");\
        printf("|       what: variable error!,\n");\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        abort();\
    }\
}

typedef int data_t;

const int yad_count = 119;
const data_t yad_elem = 167;


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


//----------------------------------------------------------------------------------------------------------------------
//! ListCtor\n\n
//! ListCtor function initialise the list.
//!
//! \param nameList - pointer to the list.
//! \return returns true if all is well.
//----------------------------------------------------------------------------------------------------------------------
bool ListCtor(list* nameList);

//----------------------------------------------------------------------------------------------------------------------
//! ListPop_front/n/n
//! ListPop_front function pops the top element from the list.
//!
//! \param nameList - pointer to the list.
//! \return returns true if all is well.
//----------------------------------------------------------------------------------------------------------------------
bool ListPop_front(list* nameList);

//----------------------------------------------------------------------------------------------------------------------
//! ListPop_back/n/n
//! ListPop_back function pops the bottom element from the list.
//!
//! \param nameList - pointer to the list.
//! \return returns true if all is well.
//----------------------------------------------------------------------------------------------------------------------
bool ListPop_back(list* nameList);

//----------------------------------------------------------------------------------------------------------------------
//! ListPush_front/n/n
//! ListPush_front function pushes the element in the top of the list.
//!
//! \param nameList - pointer to the list.
//! \param elem - the element, which we push in the list
//! \return returns the pointer to the element in the list
//----------------------------------------------------------------------------------------------------------------------
list_elem* ListPush_front(list* nameList, data_t elem);

//----------------------------------------------------------------------------------------------------------------------
//! ListPush_back/n/n
//! ListPush_back function pushes the element in the bottom of the list.
//!
//! \param nameList - pointer to the list.
//! \param elem - the element, which we push in the list.
//! \return returns the pointer to the element in the list.
//----------------------------------------------------------------------------------------------------------------------
list_elem* ListPush_back(list* nameList, data_t elem);

//----------------------------------------------------------------------------------------------------------------------
//! ListInsert_before/n/n
//! ListInsert_before function insert the element before the another element pointed by position.
//!
//! \param nameList - pointer to the list.
//! \param elem - the element, which we insert in the list.
//! \param position - pointer to the element in the list.
//! \return - returns the pointer to the element in the list or nullptr if something wrong.
//----------------------------------------------------------------------------------------------------------------------
list_elem* ListInsert_before(list* nameList, data_t elem, list_elem* position);

//----------------------------------------------------------------------------------------------------------------------
//! ListInsert_after/n/n
//! ListInsert_after function insert the element after the another element pointed by position.
//!
//! \param nameList - pointer to the list.
//! \param elem - the element, which we insert in the list.
//! \param position - pointer to the element in the list.
//! \return - returns the pointer to the element in the list or nullptr if something wrong.
//----------------------------------------------------------------------------------------------------------------------
list_elem* ListInsert_after(list* nameList, data_t elem, list_elem* position);

//----------------------------------------------------------------------------------------------------------------------
//! ListDelete/n/n
//! ListDelete function deletes the element pointed by position.
//!
//! \param nameList - pointer to the list.
//! \param position - pointer to the element in the list.
//! \return - returns true if all is well or false if something wrong.
//----------------------------------------------------------------------------------------------------------------------
bool ListDelete(list* nameList, list_elem* position);

//----------------------------------------------------------------------------------------------------------------------
//! ListDtor/n/n
//! ListDtor function destroys the list.
//!
//! \param nameList - pointer to the list.
//! \return - returns true if all is well.
//----------------------------------------------------------------------------------------------------------------------
bool ListDtor(list* nameList);

//----------------------------------------------------------------------------------------------------------------------
//! ListOK/n/n
//! ListOK function checks the list for errors.
//!
//! \param nameList - pointer to the list.
//! \return - returns true if all is well or false if something wrong
//----------------------------------------------------------------------------------------------------------------------
bool ListOK(list* nameList);

//----------------------------------------------------------------------------------------------------------------------
//! DumpList/n/n
//! DumpList function creates dump of the list.
//!
//! \param nameList
//----------------------------------------------------------------------------------------------------------------------
void DumpList(list* nameList);


#endif //LIST_POINTER_LIST_P_H
