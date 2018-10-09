#ifndef STACK_UNITTESTS_H
#define STACK_UNITTESTS_H

#define UNITTEST_1(what, ref) {                                                                                        \
    printf("UNITTEST_1\n");                                                                                            \
    if((what) != (ref))                                                                                                \
        printf ("FAILED: %s = %lg, expected %lg\n", #what, (what), (ref));                                             \
    else printf("...PASSED...\n");                                                                                     \
}                                                                                                                      \


#define UNITTEST_2(what) {                                                                                             \
    if((what) != (4))                                                                                                  \
        printf ("FAILED: %s = %lg, expected NOTHING_TO_POP", #what, (what));                                           \
    else printf("...PASSED...\n");                                                                                     \
}                                                                                                                      \

#endif //STACK_UNITTESTS_H
