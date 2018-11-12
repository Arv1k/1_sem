#include "stack.h"


int main() {
    size_t check = 0;
    Stack test1 = {};

    StackCtor(&test1);

    StackPush(&test1, 6);

    printf("%d\n", StackPop(&test1));

    //Dump(&test1);


    //unittest(&test1);

    StackDtor(&test1);
}

