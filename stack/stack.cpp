#include "stack.h"
#include "UNITTESTS.h"

//----------------------------------------------------------------------------------------------------------------------
//! StackCtor\n\n
//! StackCtor function initialise stack (allocates memory, fills stack information like size and capacity).
//!
//! \param nameStack - pointer to stack.
//! \param capacity - stack capacity.
//! \return - returns zero if memory allocation failed.
//----------------------------------------------------------------------------------------------------------------------

size_t StackCtor(Stack* nameStack, size_t capacity) {
    assert_stack(nameStack != nullptr);
    assert_stack(std::isfinite(capacity));

    if (capacity == 0) {
        nameStack->Capacity = inSize;
        nameStack->Data = (data_t *) calloc(nameStack->Capacity, sizeof(*(nameStack->Data)));

        if (nameStack->Data == nullptr) {
            printf("ERROR! Can't initialise the Stack! Memory corruption!\n");

            return 0;
        }

        nameStack->Size = 0;
    }

    else {
        nameStack->Capacity = capacity;
        nameStack->Data = (data_t *) calloc(nameStack->Capacity, sizeof(*(nameStack->Data)));

        if (nameStack->Data == nullptr) {
            printf("ERROR! Can't initialise the Stack! Memory corruption!\n");

            return 0;
        }

        nameStack->Size = 0;
    }
}

//----------------------------------------------------------------------------------------------------------------------
//! StackPush\n\n
//! StackPush function pushes element in stack. If capacity of stack insufficiently, allocate more memory.
//!
//! \param nameStack - pointer to stack.
//! \param variable - the variable we want to push in stack.
//! \return - returns STACK_ERROR_REALLOC if can't allocate new memory and STACK_ERROR_PUSH if something uncommon.
//----------------------------------------------------------------------------------------------------------------------

data_t StackPush(Stack* nameStack, data_t variable) {
    assert_stack(nameStack != nullptr);
    assert_stack(std::isfinite(variable));

    if (nameStack->Capacity > nameStack->Size) {
        nameStack->Data[nameStack->Size++] = variable;
    }

    else if (nameStack->Capacity == nameStack->Size) {
        nameStack->Capacity *= 2;
        nameStack->Data = (data_t*) realloc(nameStack->Data, nameStack->Capacity * sizeof(nameStack->Data));

        if (nameStack->Data == nullptr) {
            printf("ERROR! Can't initialise the Stack! Memory corruption!\n");

            return STACK_ERROR_PUSH;
        }

        nameStack->Data[nameStack->Size++] = variable;
    }

    else return STACK_ERROR_PUSH;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackPop\n\n
//! StackPop function pops element from stack. If capacity much more than needed, reallocates less memory.
//!
//! \param nameStack - pointer to stack.
//! \return - returns element which was popped. If there isn't any element to pop returns NAN,
//! and returns STACK_ERROR_POP if something uncommon.
//----------------------------------------------------------------------------------------------------------------------

data_t StackPop(Stack* nameStack) {
    assert_stack(nameStack != nullptr);

    if (nameStack->Size > 0){
        data_t popElem = nameStack->Data[--nameStack->Size];

        nameStack->Data[nameStack->Size] = NAN;

        if ((nameStack->Size != 0) && (nameStack->Capacity / nameStack->Size) == 4) {
            nameStack->Capacity /= 2;
            nameStack->Data = (data_t*) realloc(nameStack->Data, nameStack->Capacity * sizeof(nameStack->Data));

            if (nameStack->Data == nullptr) {
                printf("ERROR! Can't initialise the Stack! Memory corruption!\n");

                return STACK_ERROR_POP;
            }
        }

        return popElem;
    }

    else if (nameStack->Size == 0)  {
        printf("There isn't any element to pop!\n");

        return NAN;
    }

    else return STACK_ERROR_POP;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackPeek\n\n
//! StackPeek function shows the top element.

//! \param nameStack - pointer to stack
//! \return - returns the top element. If there isn't any element returns NAN,
//! and returns STACK_ERROR_PEEK if something uncommon.
//----------------------------------------------------------------------------------------------------------------------

data_t StackPeek(Stack* nameStack) {
    assert_stack(nameStack != nullptr);

    if (nameStack->Size > 0) return nameStack->Data[nameStack->Size - 1];

    else if (nameStack->Size == 0)  {
        printf("There isn't any element!\n");

        return NAN;
    }

    else return STACK_ERROR_PEEK;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackClear\n\n
//! StackClear function clears all stack (memory is filled with nan's).
//!
//! \param nameStack - pointer to stack
//----------------------------------------------------------------------------------------------------------------------

void StackClear(Stack* nameStack) {
    assert_stack(nameStack != nullptr)

    memset(nameStack->Data, NAN, nameStack->Capacity);

    nameStack->Data = (data_t*) realloc(nameStack->Data, inSize * sizeof(nameStack->Data));
    nameStack->Capacity = 0;
    nameStack->Size = 0;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackDtor\n\n
//! Destroy the stack.
//!
//! \param nameStack - pointer to stack
//----------------------------------------------------------------------------------------------------------------------

void StackDtor(Stack* nameStack) {
    memset(nameStack->Data, NAN, nameStack->Capacity);
    free(nameStack->Data);

    nameStack->Size = Poison;
    nameStack->Capacity = Poison;
}

//----------------------------------------------------------------------------------------------------------------------
//! StackOK\n\n
//! StackOK function checks stack.
//!
//! \param nameStack - pointer to stack
//----------------------------------------------------------------------------------------------------------------------

void StackOK(Stack* nameStack) {
    StackPush(nameStack, 6);
    UNITTEST_1(StackPeek(nameStack), 6.0);

    UNITTEST_2(StackPop(nameStack), NAN);
    UNITTEST_3(nameStack);
}
