#ifndef AKINATOR_1LOVE_AKINATOR_H
#define AKINATOR_1LOVE_AKINATOR_H


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include "tree/binary_tree.h"

const int max_string = 100;

tree_elem* question(tree_elem* position);

char* TreeReadAkinator(tree* nameTree, FILE* enterTree);

tree_elem* TreeCtorElem(tree* nameTree, int* i, char* buffer);

void new_member(tree* nameTree, tree_elem* position);


#endif //AKINATOR_1LOVE_AKINATOR_H
