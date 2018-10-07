#include "stack.h"

void StackCtor(Stack* nameStack, const size_t capacity) {
    nameStack->Capacity = capacity;
    nameStack->Data = (data_t*) calloc(nameStack->Capacity, sizeof(*(nameStack->Data)));

    nameStack->Size = 0;
}

data_t StackPush(Stack* nameStack, data_t variable) {
    if (nameStack->Capacity > nameStack->Size) {
        nameStack->Data[nameStack->Size++] = variable;
    }

    else if (nameStack->Capacity == nameStack->Size) {
        nameStack->Capacity *= 2;
        nameStack->Data = (data_t*) realloc(nameStack->Data, nameStack->Capacity * sizeof(nameStack->Data));

        if(nameStack->Data == nullptr) return STACK_ERROR_REALLOC;

        nameStack->Data[nameStack->Size++] = variable;
    }

    else return STACK_ERROR_PUSH;
}

data_t StackPop(Stack* nameStack) {
    if (nameStack->Size > 0){
        data_t popElem = nameStack->Data[--nameStack->Size];

        nameStack->Data[nameStack->Size] = {};

        if ((nameStack->Size != 0) &&(nameStack->Capacity / nameStack->Size) == 4) {
            nameStack->Capacity /= 2;
            nameStack->Data = (data_t*) realloc(nameStack->Data, nameStack->Capacity * sizeof(nameStack->Data));
        }

        return popElem;
    }

    else if (nameStack->Size == 0)  {
        printf("There isn't any element to pop!\n");

        return NOTHING_TO_POP;
    }

    else return STACK_ERROR_POP;
}

data_t StackPeek(Stack* nameStack) {
    if (nameStack->Size > 0) return nameStack->Data[nameStack->Size - 1];

    else if (nameStack->Size == 0)  {
        printf("There isn't any element!\n");

        return NOTHING_TO_PEEK;
    }

    else return STACK_ERROR_PEEK;
}

void StackClear(Stack* nameStack) {
    memset(nameStack->Data, 0, nameStack->Capacity);

    nameStack->Data = (data_t*) realloc(nameStack->Data, inSize * sizeof(nameStack->Data));
    nameStack->Capacity = 0;
    nameStack->Size = 0;
}

void StackDtor(Stack* nameStack) {
    memset(nameStack->Data, 0, nameStack->Capacity);
    free(nameStack->Data);

    nameStack->Size = 0;
    nameStack->Capacity = 0;
}
