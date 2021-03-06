#ifndef AKINATOR_1LOVE_TREE_H
#define AKINATOR_1LOVE_TREE_H


#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <cstring>

#define assert_tree(nameTree) {\
    if ( !(TreeOK(nameTree)) ) {\
        printf("| !!! Assertion failed !!!\n");\
        printf("|       what: TreeOK(%s),\n", #nameTree);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        /*printf("| !!! Look at DumpTree !!!");\
        DumpTree(nameTree);*/\
        abort();\
    }\
}


enum {
    MODE_NUMBER = 65,
    MODE_VAR    = 66,
    MODE_SIGN   = 67,
    MODE_OP     = 68
};

const int yad_num = -111;
const char yad_sign = -22;
const size_t yad_mode = 911;

struct DatA {
    char* var   = nullptr;
    char* op    = nullptr;
    char sign   = yad_sign;
    int number  = yad_num;
    size_t mode = yad_mode;
};


typedef DatA data_t;


struct tree_elem {
    data_t Info = {};
    tree_elem* Parent = nullptr;
    tree_elem* Left   = nullptr;
    tree_elem* Right  = nullptr;
};


const int yad_count = 119;

struct tree {
    tree_elem* Tamyr = nullptr;
    size_t     count = yad_count;
};


//----------------------------------------------------------------------------------------------------------------------
//! TreeCtor\n\n
//! TreeCtor function initialise the Tree.
//!
//! \param nameTree - pointer to the Tree.
//! \return returns true if all is well.
//----------------------------------------------------------------------------------------------------------------------
bool TreeCtor(tree* nameTree);

//----------------------------------------------------------------------------------------------------------------------
//! TreeDtor/n/n
//! TreeDtor function destroys the Tree.
//!
//! \param nameTree - pointer to the Tree.
//! \return - returns true if all is well.
//----------------------------------------------------------------------------------------------------------------------
bool TreeDtor(tree* nameTree);

//----------------------------------------------------------------------------------------------------------------------
//! TreeOK/n/n
//! TreeOK function checks the Tree for errors.
//!
//! \param nameTree - pointer to the Tree.
//! \return - returns true if all is well or false if something wrong
//----------------------------------------------------------------------------------------------------------------------
bool TreeOK(tree* nameTree);

//----------------------------------------------------------------------------------------------------------------------
//!
//! \param nameTree
//! \param elem
//! \param branch
//! \param position
//! \return
//----------------------------------------------------------------------------------------------------------------------
tree_elem* TreeAdd(tree* nameTree, data_t elem, char branch = '\0', tree_elem* position = nullptr);

//----------------------------------------------------------------------------------------------------------------------
//!
//! \param nameTree
//! \param elem
//! \param branch
//! \param position
//! \return
//----------------------------------------------------------------------------------------------------------------------
tree_elem* TreeNode(tree* nameTree, data_t elem, char branch, tree_elem* position);

//----------------------------------------------------------------------------------------------------------------------
//!
//! \param position
//! \param enterTree
//----------------------------------------------------------------------------------------------------------------------
void TreePrint(tree_elem* position, FILE* enterTree);

//----------------------------------------------------------------------------------------------------------------------
//!
//! \param position
//----------------------------------------------------------------------------------------------------------------------
void TreeDoyElems(tree_elem* position, size_t* con);

//----------------------------------------------------------------------------------------------------------------------
//!
//! \param position
//! \param i
//----------------------------------------------------------------------------------------------------------------------
void TreeElemsOK(tree_elem* position, int* i);

//----------------------------------------------------------------------------------------------------------------------
//!
//! \param nameTree
//! \param elem
//! \return
//----------------------------------------------------------------------------------------------------------------------
tree_elem* TreeSearch(tree_elem* position, data_t elem);


#endif //AKINATOR_1LOVE_TREE_H
