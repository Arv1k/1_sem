#ifndef STACK_STACK_H
#define STACK_STACK_H


#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>

#define assert_stack(nameStack) {\
    if ( !(StackOK(nameStack)) ) {\
        printf("| !!!Assertion failed!!!\n");\
        printf("|       what: StackOK(%s),\n", #nameStack);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        printf("|   !!!Look at DUMP!!!\n");\
        Dump(nameStack);\
        abort();\
    }\
}\

#define assert_var(variable) {\
    if ( !(std::isfinite(variable)) ) {\
        printf("| !!!Assertion failed!!!\n");\
        printf("|       what: StackOK(%s),\n", #variable);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        printf("|   !!!Look at DUMP!!!\n");\
        Dump(nameStack);\
        abort();\
    }\
}\


typedef double data_t;

const size_t InSize = 2;

const size_t petuhValue1 = 110900;

const data_t petuhValue2 = 160716;

const size_t Poison = 31415;

struct Stack {
    size_t petuh1 = petuhValue1;

    data_t* Data = nullptr;
    size_t  Size = NAN;
    size_t  Capacity = NAN;
    data_t hash_sum = NAN;

    size_t petuh2 = petuhValue1;
};

enum STACK_ERRORS {
    STACK_ERROR_CTOR = 100010,
    STACK_ERROR_INIT = 0b100001,
    STACK_ERROR_PUSH = 100011,
    STACK_ERROR_PUSH_REALLOC = 100100,
    STACK_ERROR_POP = 100101,
    STACK_ERROR_POP_REALLOC = 100110,
};


size_t StackCtor(Stack* nameStack, size_t capacity = 0);

data_t StackPush(Stack* nameStack, data_t variable);

data_t StackPop(Stack* nameStack);

data_t StackPeek(Stack* nameStack);

void StackClear(Stack* nameStack);

void StackDtor(Stack* nameStack);

size_t StackMem(Stack* nameStack, size_t initialSize = 0);

size_t StackPushMemInc (Stack* nameStack);

size_t StackPopMemDec(Stack* nameStack);

bool StackOK(Stack* nameStack);

size_t Dump(Stack* nameStack);

void unittest(Stack* nameStack);


#endif //STACK_STACK_H
