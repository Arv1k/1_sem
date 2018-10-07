#include "stack.h"

int main() {
    size_t check = 0;
    Stack test1 = {};

    StackCtor(&test1, inSize);

    StackPush(&test1, 5);
    StackPush(&test1, 6);
    StackPush(&test1, 6);
    StackPush(&test1, 6);
    StackPush(&test1, 6);
    StackPush(&test1, 6);
    StackPush(&test1, 6);
    StackPush(&test1, 6);
    StackPush(&test1, 6);
    StackPush(&test1, 6);
    StackPush(&test1, 6);

    StackClear(&test1);

    StackPop(&test1);

    printf("%lg\n", test1.Data[0]);

    StackDtor(&test1);
}

