#include "stack.h"


int main() {
    size_t check = 0;
    Stack test1 = {};

    StackCtor(&test1);

//    data_t val = 0;
//    for (data_t i = 1; i < 21; i++)  StackPush(&test1, i*2);
//    for (data_t i = 20; i >= 1; i--) UNITTEST(StackPop(&test1), ==, i*2);
//
//    StackPush(&test1, 11);
//    UNITTEST(StackPeek(&test1), ==, 11.0);
//    StackPop(&test1);
//
//    UNITTEST(std::isfinite(StackPop(&test1)), ==, 0.0);
//
//    UNITTEST(std::isfinite(StackPeek(&test1)), ==, 0.0);


    StackDtor(&test1);
}

