#ifndef DIFFERENTIATOR_DIFFER_H
#define DIFFERENTIATOR_DIFFER_H


#include "tree/binary_tree.h"

#define dassert(pointer) {\
    if (!pointer) {\
        printf("| !!! Dassertion failed !!!\n");\
        printf("|       what: %s is nullptr\n", #pointer);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        abort();\
    }\
}

#define pc_assert(pc) {\
    if ( !((*pc) == '\n' || (*pc) == '\0') ) {\
        printf("| !!! Pc_assertion failed !!!\n");\
        printf("|       what: expected %d instead 0\n", *pc);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        abort();\
        }\
}


const int max_word = 1000;

enum {
    #define CMD_FORM(com, len, num, code) OP_##com = num,

    #include "com.h"

    #undef CMD_FORM
};


void ReadEquation(tree* nameTree, char* input);

//G ::= E'\0'
tree_elem* GetG(char* buff);

// E ::= T{[+-]T}*
tree_elem* GetE();

// T ::= L{[*/]P}L
tree_elem* GetT();

// L ::= P{'^'P}*
tree_elem* GetL();

// P :: = (E) | sin(E) | cos(E) | ln(E) | lg(E) | N
tree_elem* GetP();

// N ::= [a-z & 0-9]{[a-z & 0-9]}*
tree_elem* GetN();

tree Derivative(tree* nameTree);

tree_elem* diff(tree_elem* position);

tree_elem* CrtNode(size_t mode, int op, tree_elem* left_guy, tree_elem* right_girl);

tree_elem* CrtNode_op(const char* name, tree_elem* right_girl);

tree_elem* copy(tree_elem* position);

int which_oper(const char* name);

char* which_word();

void simple_tree(tree_elem* position, size_t* num);

bool is_leaf(tree_elem* position);

bool can_simp(tree_elem* position);

bool is_zero(tree_elem* position);

bool is_one(tree_elem* position);

void is_tamyr(tree_elem* position, size_t* num, char side);

int which_side(tree_elem* par, tree_elem* son);

void tree_dot(tree* nameTree, char* dot_out);

void create_tree(tree_elem* pos, FILE* dot_out);

void print_mode(tree_elem* pos, FILE* dot_out);

void Latex(tree* nameTree, char* output);

#endif //DIFFERENTIATOR_DIFFER_H
