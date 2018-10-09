#ifndef STACK_UNITTESTS_H
#define STACK_UNITTESTS_H

#define UNITTEST_1(what, ref) {                                                                                        \
    printf("UNITTEST_1\n");                                                                                            \
    if((what) != (ref)) printf ("FAILED: %s = %lg, expected %lg\n", #what, (what), (ref));                             \
    else                printf("...PASSED...\n");                                                                      \
}                                                                                                                      \


#define UNITTEST_2(what, ref) { \
    if((what) != (ref)) printf ("FAILED: %s = %lg, expected %lg\n", #what, (what), ref);                           \
    else                       printf("...PASSED...\n");                                                                        \
}                                                                                                                      \

#define UNITTEST_3(what) {                                                                                             \
    StackClear(what);                                                                                                  \
    data_t check = StackPeek(what);\
    if ((check) != (NAN)) printf ("FAILED: StackPeek(%s) = %lg, expected NAN\n",#what, (check));\
    else                            printf("...PASSED...\n");\
}\

#endif //STACK_UNITTESTS_H

