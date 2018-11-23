#include "akinator.h"

int main() {
    printf("Hello)\n"
           "Make a wish for someone or something, and I will try to guess it!\n\n"
           "Do you want to play?\n"
           "# press [y] if you want and [n] if you don't want\n");

    char ans = 0;
    scanf("%c", &ans);

    if (ans == 'n') {
        printf("Bye!\n");

        return 0;
    }

    else if (ans != 'y') {
        printf("Invalid command!\n");

        return 0;
    }

    printf("Let's start!)\n\n");

    tree myTree = {};
    TreeCtor(&myTree);

    FILE* enterTree = fopen("../enterTree", "rb");
    char* buffer = TreeReadAkinator(&myTree, enterTree);
    fclose(enterTree);

    tree_elem* pos = question(myTree.Tamyr);

    scanf("\n%c", &ans);

    if (ans == 'n')      new_member(&myTree, pos);
    else if (ans == 'y') printf("Ha! I knew this =)\n");
    else                 printf("Invalid command!\n");

    FILE* outputFile = fopen("../enterTree", "w");
    TreePrint(myTree.Tamyr, outputFile);
    fclose(outputFile);

    int heyhey = sizeof(buffer);
    memset(buffer, 0, heyhey);
    free(buffer);
    TreeDtor(&myTree);
}