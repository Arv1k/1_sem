#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>

#define assert_stack( check ) {                                                                                                             \
    if( !(check) ) {                                                                                                                        \
        printf("Assertion failed! \n %s,\n in: %s,\n function: %s,\n on: %d line.\n ", #check, __FILE__, __PRETTY_FUNCTION__, __LINE__);    \
        abort();                                                                                                                            \
    }                                                                                                                                       \
}                                                                                                                                           \

typedef double data_t;

struct Stack {
    data_t* Data;
    size_t  Size;
    size_t  Capacity;
};

enum STACK_ERRORS {
    STACK_ERROR_NULLPTR,
    STACK_ERROR_PUSH,
    STACK_ERROR_REALLOC,
    STACK_ERROR_POP,
    NOTHING_TO_PEEK,
    STACK_ERROR_PEEK,
    STACK_ERROR_DTOR
};

const size_t inSize = 2;
const size_t Poison = 110900;


size_t StackCtor(Stack* nameStack,size_t capacity = 0);

data_t StackPush(Stack* nameStack, data_t variable);

data_t StackPop(Stack* nameStack);

data_t StackPeek(Stack* nameStack);

void StackClear(Stack* nameStack);

void StackDtor(Stack* nameStack);

void StackOK(Stack* nameStack);

#endif //STACK_STACK_H
