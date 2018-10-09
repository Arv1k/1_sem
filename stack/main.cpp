#include "stack.h"
#include "UNITTESTS.h"

int main() {
    size_t check = 0;
    Stack test1 = {};

    StackCtor(&test1, 'c');

    StackPush(&test1, 1);
    StackPush(&test1, 1);

    StackPop(&test1);

    printf("%li",test1.Capacity);

    StackDtor(&test1);
}

