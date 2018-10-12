#ifndef STACK_STACK_H
#define STACK_STACK_H


#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>

static int NumUnittest = 0;
static int TotalUnittest = 23;

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

#define UNITTEST(what, op, ref) {\
    printf("UNITTEST_%d\n", (NumUnittest));\
    data_t result = (what);\
    (NumUnittest) += 1;\
    if((result) op (ref)) printf ("...PASSED...\n");\
    else                  printf("FAILED: %s " #op " %lg, expected %lg\n", #what, (double) (result), (ref));\
    printf("[%.*s|%.*s]\n\n", (NumUnittest), "|||||||||||||||", ((TotalUnittest) - (NumUnittest)) , "...............");\
}\

typedef double data_t;

struct Stack {
    data_t* Data = {};
    size_t  Size = 0;
    size_t  Capacity = 0;
    size_t* petuh_stack[2] = {};
    size_t* petuh_data[2] = {};
};

enum STACK_ERRORS {
    STACK_ERROR_INIT = 100001,
    STACK_ERROR_CTOR = 100010,
    STACK_ERROR_PUSH = 100011,
    STACK_ERROR_PUSH_REALLOC = 100100,
    STACK_ERROR_POP = 100101,
    STACK_ERROR_POP_REALLOC = 100110,
};

const size_t InSize = 2;
const size_t Poison = 110900;


size_t StackCtor(Stack* nameStack,size_t capacity = 0);

data_t StackPush(Stack* nameStack, data_t variable);

data_t StackPop(Stack* nameStack);

data_t StackPeek(Stack* nameStack);

void StackClear(Stack* nameStack);

void StackDtor(Stack* nameStack);

size_t StackMem(Stack* nameStack, size_t initialSize = 0);

size_t StackPushMemInc (Stack* nameStack);

size_t StackPopMemDec(Stack* nameStack);

size_t StackOK(Stack* nameStack);

size_t Dump(Stack* nameStack);


#endif //STACK_STACK_H
