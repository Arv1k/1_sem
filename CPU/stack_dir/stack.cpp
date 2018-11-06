#include "stack.h"

#define HASH_SUM(what, op, ref) {\
    if ((#op)[0] == '+') {\
        (what) = ( (what) op (ref) );\
        (what) = ( ( (int) (what) ) << 1 );\
    }\
    else {\
        (what) = ( ( (int) (what) ) >> 1 );\
        (what) = ( (what) op (ref) );\
    }\
}\

//----------------------------------------------------------------------------------------------------------------------
//! StackCtor\n\n
//! StackCtor function initialise stack.
//!
//! \param nameStack - pointer to stack.
//! \param capacity - stack capacity.
//! \return - returns 1 if all is well and returns STACK_ERROR_CTOR if can't allocate memory.
//----------------------------------------------------------------------------------------------------------------------

size_t StackCtor(Stack* nameStack, size_t capacity) {
    assert_stack(nameStack);
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
        size_t check = StackMem(nameStack, capacity);
        if (check == STACK_ERROR_INIT) return STACK_ERROR_CTOR;

        nameStack->Size = 0;
    }

    assert_stack(nameStack);
    return 1;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackPush\n\n
//! StackPush function pushes element in stack.
//!
//! \param nameStack - pointer to stack.
//! \param variable - the variable we want to push in stack.
//! \return - returns 1 if all is well and returns STACK_ERROR_PUSH if something uncommon.
//----------------------------------------------------------------------------------------------------------------------

data_t StackPush(Stack* nameStack, data_t variable) {
    assert_stack(nameStack);
    assert_var(variable);

    if (nameStack->Capacity == nameStack->Size) {
        size_t check = StackPushMemInc(nameStack);

        if (check == STACK_ERROR_PUSH_REALLOC) return STACK_ERROR_PUSH;
    }

    nameStack->Data[++nameStack->Size] = variable;

    //HASH_SUM(nameStack->hash_sum, +, 5);
    nameStack->hash_sum += nameStack->Data[nameStack->Size];
    nameStack->hash_sum = ((int) nameStack->hash_sum) << 1;

    assert_stack(nameStack);
    return 1;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackPop\n\n
//! StackPop function pops element from stack.
//!
//! \param nameStack - pointer to stack.
//! \return - returns element which was popped. If there isn't any element to pop returns NAN
//! and returns STACK_ERROR_POP if can't allocate memory.
//----------------------------------------------------------------------------------------------------------------------

data_t StackPop(Stack* nameStack) {
    assert_stack(nameStack);

    if (nameStack->Size == 0) {
        printf("There isn't any element to pop!\n");

        assert_stack(nameStack);
        return NAN;
    }

    nameStack->hash_sum = ((int) nameStack->hash_sum) >> 1;
    nameStack->hash_sum -= nameStack->Data[nameStack->Size];

    data_t popElem = nameStack->Data[nameStack->Size--];

    if (nameStack->Capacity == (4 * nameStack->Size)) {
        size_t check = StackPopMemDec(nameStack);

        if (check == STACK_ERROR_POP_REALLOC) return STACK_ERROR_POP;
    }

    nameStack->Data[nameStack->Size + 1] = NAN;


    assert_stack(nameStack);
    return popElem;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackPeek\n\n
//! StackPeek function shows the top element.

//! \param nameStack - pointer to stack.
//! \return - returns the top element. If there isn't any element returns NAN,
//! and returns STACK_ERROR_PEEK if something uncommon.
//----------------------------------------------------------------------------------------------------------------------

data_t StackPeek(Stack* nameStack) {
    assert_stack(nameStack);

    if (nameStack->Size == 0) {
        printf("There isn't any element!\n");

        assert_stack(nameStack);
        return NAN;
    }

    assert_stack(nameStack);
    return nameStack->Data[nameStack->Size];
}

//----------------------------------------------------------------------------------------------------------------------
//! StackClear\n\n
//! StackClear function clears all stack (memory is filled with nan's).
//!
//! \param nameStack - pointer to stack.
//----------------------------------------------------------------------------------------------------------------------

void StackClear(Stack* nameStack) {
    assert_stack(nameStack);

    if (nameStack->Data != nullptr) {

        memset(nameStack->Data, NAN, nameStack->Capacity + 2);
        free(nameStack->Data);
        nameStack->hash_sum = 0;
        nameStack->Data = nullptr;
    }

    nameStack->Capacity = 0;
    nameStack->Size = 0;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackDtor\n\n
//! Destroy the stack.
//!
//! \param nameStack - pointer to stack.
//----------------------------------------------------------------------------------------------------------------------

void StackDtor(Stack* nameStack) {
    assert_stack(nameStack);

    if (nameStack->Data != nullptr) {
        memset(nameStack->Data, NAN, nameStack->Capacity + 2);
        free(nameStack->Data);
        nameStack->hash_sum = NAN;
        nameStack->Data = nullptr;
    }

    nameStack->petuh1 = Poison;

    nameStack->Capacity = Poison;
    nameStack->Size = Poison;

    nameStack->petuh2 = Poison;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackMem\n\n
//! StackMem function allocates memory for stack.
//!
//! \param nameStack - pointer to stack.
//! \param initialSize - size of initialise for stack.
//! \return - return STACK_ERROR_INIT if can't allocate memory and 1 if all is well.
//----------------------------------------------------------------------------------------------------------------------

size_t StackMem(Stack* nameStack, size_t initialSize) {
    assert_stack(nameStack);
    assert_var(initialSize);

    nameStack->petuh1 = petuhValue1;

    nameStack->Capacity = initialSize;
    nameStack->Data = (data_t*) calloc(nameStack->Capacity + 2, sizeof(data_t));

    nameStack->Data[0] = petuhValue2;
    nameStack->Data[nameStack->Capacity + 1] = petuhValue2;

    nameStack->hash_sum = 0;

    nameStack->petuh2 = petuhValue1;

    if (nameStack->Data == nullptr) {
        printf("ERROR! Can't initialise the Stack! Memory corruption!\n");

        return STACK_ERROR_INIT;
    }

    assert_stack(nameStack);
    return 1;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackPushMemInc\n\n
//! StackPushMemInc function allocate new memory if it's needed.
//!
//! \param nameStack - pointer to stack.
//! \return - returns STACK_ERROR_REALLOC if can't allocate memory and 1 if all is well.
//----------------------------------------------------------------------------------------------------------------------

size_t StackPushMemInc (Stack* nameStack) {
    assert_stack(nameStack);

    if (nameStack->Capacity == 0) nameStack->Capacity = InSize;
    else                          nameStack->Capacity *= 2;

    nameStack->Data = (data_t*) realloc(nameStack->Data, (nameStack->Capacity + 2) * sizeof(data_t));

    if (nameStack->Data == nullptr) {
        printf("ERROR! Can't initialise the Stack! Memory corruption!\n");

        return STACK_ERROR_PUSH_REALLOC;
    }

    nameStack->Data[0] = petuhValue2;
    nameStack->Data[nameStack->Capacity + 1] = petuhValue2;

    memset(nameStack->Data + sizeof(data_t) + nameStack->Size * sizeof(data_t), NAN, nameStack->Capacity - nameStack->Size);

    assert_stack(nameStack);
    return 1;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackPopMemDec\n\n
//! StackPopMemDec function decrease memory if it's not needed.
//!
//! \param nameStack - pointer to stack.
//! \return - returns STACK_ERROR_REALLOC if can't allocate memory and 1 if all is well.
//----------------------------------------------------------------------------------------------------------------------

size_t StackPopMemDec(Stack* nameStack) {
    assert_stack(nameStack);

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

//----------------------------------------------------------------------------------------------------------------------
//! StackOK\n\n
//! StackOK function checks stack.
//!
//! \param nameStack - pointer to stack.
//! \return - returns 0 if there is something wrong, and 1 if all is well.
//----------------------------------------------------------------------------------------------------------------------

bool StackOK(Stack* nameStack) {
    if (nameStack == nullptr)                                            return false;

    if ( (nameStack->petuh1 != petuhValue1) ||
         (nameStack->petuh2 != petuhValue1) )                            return false;

    if (nameStack->Capacity < 0)                                         return false;

    if (nameStack->Size < 0)                                             return false;

    if (nameStack->Capacity < nameStack->Size)                           return false;

    if (nameStack->Data != nullptr) {
        if ( (nameStack->Data[0] != petuhValue2) ||
             (nameStack->Data[nameStack->Capacity + 1]) != petuhValue2 ) return false;

        data_t sum = 0;
        for (int i = 1; i <= nameStack->Size; i++) {
            sum += nameStack->Data[i];
            sum = ((int) sum) << 1;
        }

        if (sum != nameStack->hash_sum)                                  return false;
    }

    else if (nameStack->Size > 0 && nameStack->Size != Poison)           return false;

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
//! Dump\n\n
//! Dump function creates DUMP.txt file and writes there information about Stack
//!
//! \param nameStack - pointer to stack.
//----------------------------------------------------------------------------------------------------------------------

size_t Dump(Stack* nameStack) {
    FILE *Dump = fopen("../stack_dir/DUMP.txt", "a");

    fprintf(Dump, "#----------------------------------------------------------\n");
    fprintf(Dump, "# Stack nameStack");
    fprintf(Dump, " [%p] ", nameStack);
    if (nameStack == nullptr) fprintf(Dump, "(!!!ERROR!!!) {\n");
    else                      fprintf(Dump, "{\n");

    fprintf(Dump, "#    capacity = %ld\n", nameStack->Capacity);
    fprintf(Dump, "#    size = %ld ", nameStack->Size);

    if (nameStack->Capacity < nameStack->Size) fprintf(Dump, " (!!!!!)\n");
    else                                       fprintf(Dump, "\n");

    if (nameStack->Data != nullptr) {
        fprintf(Dump, "#    data[%ld] [%p]: {\n", nameStack->Size, nameStack->Data);
        for (size_t i = 0; i < nameStack->Capacity + 2; i++) {
            fprintf(Dump, "#      [%li] = %d", i, nameStack->Data[i]);

            if (nameStack->Data[i] == petuhValue2) fprintf(Dump, " (petuh)\n");
            else if (std::isfinite(nameStack->Data[i])) fprintf(Dump, "\n");
            else                                   fprintf(Dump, " (!!!!!)\n");
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
