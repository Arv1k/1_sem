#include "stack.h"

size_t StackCtor(Stack* nameStack, size_t capacity) {
    assert_var(nameStack == nullptr);
    assert_var(capacity);

    if (capacity == 0) {
        nameStack->petuh1 = petuhValue1;

        nameStack->Data = nullptr;
        nameStack->Capacity = 0;
        nameStack->Size = 0;
        nameStack->hash_sum = 0;

        nameStack->petuh2 = petuhValue1;
    }

    else {
        nameStack->petuh1 = petuhValue1;
        nameStack->Capacity = capacity;
        nameStack->Size = 0;

        nameStack->hash_sum = 0;

        nameStack->petuh2 = petuhValue1;

        size_t check = StackMem(nameStack, capacity);
        if (check == STACK_ERROR_INIT) return STACK_ERROR_CTOR;
    }

    assert_stack(nameStack);
    return 1;
}

size_t StackPush(Stack* nameStack, data_t variable) {
    assert_stack(nameStack);
    assert_var(variable);

    if (nameStack->Capacity == nameStack->Size) {
        size_t check = StackPushMemInc(nameStack);

        if (check == STACK_ERROR_PUSH_REALLOC) return STACK_ERROR_PUSH;
    }

    nameStack->Data[++nameStack->Size] = variable;

    HASH_SUM(nameStack->hash_sum, +, nameStack->Data[nameStack->Size]);

    assert_stack(nameStack);
    return 1;
}

data_t StackPop(Stack* nameStack) {
    assert_stack(nameStack);

    if (nameStack->Size == 0) {
        printf("There isn't any element to pop!\n");

        assert_stack(nameStack);
        return Poison;
    }

    HASH_SUM(nameStack->hash_sum, -, nameStack->Data[nameStack->Size]);

    data_t popElem = nameStack->Data[nameStack->Size--];

    if (nameStack->Capacity == (4 * nameStack->Size)) {
        size_t check = StackPopMemDec(nameStack);

        if (check == STACK_ERROR_POP_REALLOC) return STACK_ERROR_POP;
    }

    assert_stack(nameStack);
    return popElem;
}

data_t StackPeek(Stack* nameStack) {
    assert_stack(nameStack);

    if (nameStack->Size == 0) {
        printf("There isn't any element!\n");

        assert_stack(nameStack);
        return Poison;
    }

    assert_stack(nameStack);
    return nameStack->Data[nameStack->Size];
}

void StackClear(Stack* nameStack) {
    assert_stack(nameStack);

    if (nameStack->Data != nullptr) {
        memset(nameStack->Data, Poison, (nameStack->Capacity + 2));
        free(nameStack->Data);

        nameStack->hash_sum = 0;
        nameStack->Data = nullptr;
    }

    nameStack->Capacity = 0;
    nameStack->Size = 0;
}

void StackDtor(Stack* nameStack) {
    assert_stack(nameStack);

    if (nameStack->Data != nullptr) {
        memset(nameStack->Data, Poison, nameStack->Capacity + 2);
        free(nameStack->Data);

        nameStack->hash_sum = Poison;
        nameStack->Data = nullptr;
    }

    nameStack->petuh1 = Poison;

    nameStack->Capacity = Poison;
    nameStack->Size = Poison;


    nameStack->petuh2 = Poison;
}

size_t StackMem(Stack* nameStack, size_t initialSize) {
    assert_stack(nameStack);
    assert_var(initialSize);

    nameStack->Capacity = initialSize;
    nameStack->Data = (data_t*) calloc( (nameStack->Capacity + 2), sizeof(data_t));
    
    if (nameStack->Data == nullptr) {
        printf("ERROR! Can't initialise the Stack! Memory corruption!\n");

        return STACK_ERROR_INIT;
    }

    nameStack->Data[0] = petuhValue2;
    nameStack->Data[nameStack->Capacity + 1] = petuhValue2;

    assert_stack(nameStack);
    return 1;
}

size_t StackPushMemInc (Stack* nameStack) {
    assert_stack(nameStack);

    if (nameStack->Capacity == 0) nameStack->Capacity = InSize;
    else                          nameStack->Capacity *= 2;

    if (nameStack->Data)
        nameStack->Data = (data_t*) realloc(nameStack->Data, (nameStack->Capacity + 2) * sizeof(data_t));
    
    else
        nameStack->Data = (data_t*) calloc((nameStack->Capacity + 2), sizeof(data_t));

    if (nameStack->Data == nullptr) {
        printf("ERROR! Can't initialise the Stack! Memory corruption!\n");

        return STACK_ERROR_PUSH_REALLOC;
    }

    memset( ( nameStack->Data + sizeof(data_t) + (nameStack->Size * sizeof(data_t)) ),
            Poison,
            (nameStack->Capacity - nameStack->Size + 1) * sizeof(data_t) );

    nameStack->Data[0] = petuhValue2;
    nameStack->Data[nameStack->Capacity + 1] = petuhValue2;

    assert_stack(nameStack);
    return 1;
}

size_t StackPopMemDec(Stack* nameStack) {
    assert_stack(nameStack);

//    memset( ( nameStack->Data + sizeof(data_t) + (nameStack->Size * sizeof(data_t)) ),
//            Poison,
//            nameStack->Capacity - nameStack->Size - 1);

    nameStack->Capacity /= 2;
    nameStack->Data = (data_t*) realloc(nameStack->Data, (nameStack->Capacity + 2) * sizeof(data_t));

    if (nameStack->Data == nullptr) {
        printf("ERROR! Can't initialise the Stack! Memory corruption!\n");

        return STACK_ERROR_POP_REALLOC;
    }

    nameStack->Data[0] = petuhValue2;
    nameStack->Data[nameStack->Capacity + 1] = petuhValue2;

    assert_stack(nameStack);
    return 1;
}

bool StackOK(Stack* nameStack) {
    if (nameStack == nullptr)                                            return false;

    if ( (nameStack->petuh1 != petuhValue1) ||
         (nameStack->petuh2 != petuhValue1) )                            return false;

    if (nameStack->Capacity < 0 || nameStack->Capacity == Poison)        return false;

    if (nameStack->Size < 0 || nameStack->Capacity == Poison)            return false;

    if (nameStack->Capacity < nameStack->Size)                           return false;

    if (nameStack->Data != nullptr) {
        if ( (nameStack->Data[0] != petuhValue2) ||
             (nameStack->Data[nameStack->Capacity + 1]) != petuhValue2 ) return false;

        data_t sum = 0;
        for (int i = 1; i <= nameStack->Size; i++) HASH_SUM(sum, +, nameStack->Data[i]);

        if (sum != nameStack->hash_sum)                                  return false;
    }

    else if (nameStack->Size > 0 && nameStack->Size != Poison)           return false;

    return true;
}

void Dump(Stack* nameStack) {
    FILE *Dump = fopen("../DUMP.txt", "a");

    fprintf(Dump, "#----------------------------------------------------------\n");
    fprintf(Dump, "# Stack nameStack");
    fprintf(Dump, " [%p] ", nameStack);
    if (nameStack == nullptr) {
        fprintf(Dump, "(!!!ERROR!!!) {\n");
        return;
    }
    else fprintf(Dump, "{\n");

    fprintf(Dump, "#    capacity = %ld", nameStack->Capacity);
    if (nameStack->Capacity == Poison) fprintf(Dump, " (poison?)\n");
    else                               fprintf(Dump, "\n");

    fprintf(Dump, "#    size = %ld", nameStack->Size);
    if (nameStack->Size == Poison) fprintf(Dump, " (poison?)");

    if (nameStack->Capacity < nameStack->Size) fprintf(Dump, " (!!!!!)\n");
    else                                       fprintf(Dump, "\n");

    if (nameStack->Data != nullptr) {
        fprintf(Dump, "#    data[%ld] [%p]: {\n", nameStack->Size, nameStack->Data);
        for (size_t i = 0; i < nameStack->Capacity + 2; i++) {
            fprintf(Dump, "#      [%li] = %d", i, nameStack->Data[i]);

            if (nameStack->Data[i] == petuhValue2) fprintf(Dump, " (petuh)\n");
            else if (nameStack->Data[i] == Poison) fprintf(Dump, " (poison?)\n");
            else                                   fprintf(Dump, "\n");
        }

        fprintf(Dump, "#    }\n# }\n");
        fprintf(Dump, "#----------------------------------------------------------\n");
        fclose(Dump);
    }

    else {
        fprintf(Dump, "#    data = nullptr (!!!!!) {\n");
        fprintf(Dump, "# }\n");
        fprintf(Dump, "#----------------------------------------------------------\n");
        fclose(Dump);
    }
}

static int NumUnittest = 0;
static int TotalUnittest = 28;

#define UNITTEST(what, op, ref) {\
    (NumUnittest) += 1;\
    printf("UNITTEST_%d\n", (NumUnittest));\
    data_t result = (what);\
    if((result) op (ref)) printf("...PASSED...\n");\
    else                  printf("FAILED: %s " #op " %d, expected %d\n", #what, (data_t) (result), (ref));\
    printf("[%*.*s|%*.*s]\n\n", (NumUnittest),                     (NumUnittest),                      "||||||||||||||||||||||||||||",\
                                ((TotalUnittest) - (NumUnittest)), ((TotalUnittest) - (NumUnittest)) , "............................");\
}

void unittest(Stack* nameStack) {
    for (data_t i =  1; i < 21; i++) StackPush(nameStack, i*2);
    for (data_t i = 20; i >= 1; i--) UNITTEST(StackPop(nameStack), ==, i*2);

    StackPush(nameStack, 11);
    UNITTEST(StackPeek(nameStack), ==, 11);
    StackPop(nameStack);

    UNITTEST(StackPop(nameStack), ==, Poison);

    UNITTEST(StackPeek(nameStack), ==, Poison);

    for (data_t i =  1; i < 21; i++) StackPush(nameStack, i*2);
    StackClear(nameStack);
    UNITTEST(StackPop(nameStack), ==, Poison);

    for (data_t i =  1; i < 21; i++) StackPush(nameStack, i*2);
    data_t check = nameStack->Data[13];
    nameStack->Data[13] = nameStack->Data[10];
    nameStack->Data[10] = check;
    UNITTEST(StackOK(nameStack), ==, 0);
    check = nameStack->Data[13];
    nameStack->Data[13] = nameStack->Data[10];
    nameStack->Data[10] = check;
    StackClear(nameStack);

    nameStack->petuh1 = 0;
    UNITTEST(StackOK(nameStack), !=, 1);
    nameStack->petuh1 = petuhValue1;

    StackPush(nameStack, 11);
    nameStack->Data[0] = 0;
    UNITTEST(StackOK(nameStack), ==, 0);
    nameStack->Data[0] = petuhValue2;
    StackClear(nameStack);

    Stack test110900 = {};
    UNITTEST(StackOK(&test110900), ==, 0);
}
