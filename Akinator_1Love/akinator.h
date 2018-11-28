#ifndef AKINATOR_1LOVE_AKINATOR_H
#define AKINATOR_1LOVE_AKINATOR_H


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include "tree/binary_tree.h"


const int max_string = 100;


//----------------------------------------------------------------------------------------------------------------------
//!
//! \param position
//! \return
//----------------------------------------------------------------------------------------------------------------------
tree_elem* question(tree_elem* position);

//----------------------------------------------------------------------------------------------------------------------
//!
//! \param nameTree
//! \param enterTree
//----------------------------------------------------------------------------------------------------------------------
void TreeReadAkinator(tree* nameTree, FILE* enterTree);

//----------------------------------------------------------------------------------------------------------------------
//!
//! \param nameTree
//! \param i
//! \param buffer
//! \return
//----------------------------------------------------------------------------------------------------------------------
tree_elem* TreeCtorElem(tree* nameTree, int* i, char* buffer);

//----------------------------------------------------------------------------------------------------------------------
//!
//! \param nameTree
//! \param position
//----------------------------------------------------------------------------------------------------------------------
void new_member(tree* nameTree, tree_elem* position);

void search_member(tree* nameTree, char* elem);


#endif //AKINATOR_1LOVE_AKINATOR_H
