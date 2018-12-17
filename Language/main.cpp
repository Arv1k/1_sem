#include "language.h"

int main(int argc, char* argv[]) {
    char* buffer = nullptr;

    buffer = Fill_the_Buffer(argv[1]);

    tree TrEE = {};
    TreeCtor(&TrEE);


    makeTree(&TrEE, buffer);
    /*int i = 0;
    while (buffer[i] != '\0') {
        printf("%d\n", buffer[i]);
        i++;
    }*/

    /*FILE* her = fopen(argv[1], "rb");
    printf("%ld\n", Size(her));
    fclose(her);

    printf("%s\n", buffer);*/

    tree_dot(&TrEE, argv[2]);

    TreeDtor(&TrEE);
    free(buffer);
}