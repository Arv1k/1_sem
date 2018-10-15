#include "stack.h"

static int NumUnittest = 0;
static int TotalUnittest = 23;

#define UNITTEST(what, op, ref) {\
    (NumUnittest) += 1;\
    printf("UNITTEST_%d\n", (NumUnittest));\
    data_t result = (what);\
    if((result) op (ref)) printf ("...PASSED...\n");\
    else                  printf("FAILED: %s " #op " %lg, expected %lg\n", #what, (double) (result), (ref));\
    printf("[%.*s|%.*s]\n\n", (NumUnittest), "|||||||||||||||", ((TotalUnittest) - (NumUnittest)) , "...............");\
}\

void unittest(Stack* nameStack) {
    for (data_t i = 1; i < 21; i++)  StackPush(nameStack, i*2);
    for (data_t i = 20; i >= 1; i--) UNITTEST(StackPop(nameStack), ==, i*2);

    StackPush(nameStack, 11);
    UNITTEST(StackPeek(nameStack), ==, 11.0);
    StackPop(nameStack);

    UNITTEST(std::isfinite(StackPop(nameStack)), ==, 0.0);

    UNITTEST(std::isfinite(StackPeek(nameStack)), ==, 0.0);
}
