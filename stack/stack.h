#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

typedef double data_t;

#define UNITTEST(what, ref){                                             \
    if((what) != (ref))                                                  \
        printf ("FAILED: %s = %d, expected %d\n", #what, (what), (ref)); \
    else printf("...PASSED...\n");                                       \
}                                                                        \

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
    NOTHING_TO_POP,
    NOTHING_TO_PEEK,
    STACK_ERROR_PEEK,
    STACK_ERROR_DTOR
};


const size_t inSize = 2;

void StackCtor(Stack* nameStack, size_t capacity);

data_t StackPush(Stack* nameStack, data_t variable);

data_t StackPop(Stack* nameStack);

data_t StackPeek(Stack* nameStack);

void StackClear(Stack* nameStack);

void StackDtor(Stack* nameStack);

//size_t StackOK(Stack* nameStack);

#endif //STACK_STACK_H
