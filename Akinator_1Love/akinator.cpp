#include "akinator.h"

tree_elem* question(tree_elem* position) {
    for (;;) {
        if (position->Left == nullptr) {
            printf("Is it the %s?\n", position->Info);
            printf("# yes [y], no [n]\n");

            return position;
        }

        printf("Does it %s?\n", position->Info);
        printf("# yes [y], no [n]\n");

        char ans = 0;
        scanf("\n%c", &ans);

        if      (ans == 'n') position = position->Left;
        else if (ans == 'y') position = position->Right;
        else {
            printf("Invalid command!\n");

            abort();
        }
    }
}

char* TreeReadAkinator(tree* nameTree, FILE* enterTree) {
    fseek(enterTree, 0, SEEK_END);
    long size = ftell(enterTree);
    rewind(enterTree);

    char* buffer = (char*) calloc(size + 1, sizeof(char));
    fread(buffer, sizeof(char), size, enterTree);

//    int i = 0;
//    while (buffer[i] != '\0') {
//        if (buffer[i] == ' ') buffer[i] = '\0';
//        i++;
//    }

    int i = 0;
    nameTree->Tamyr = TreeCtorElem(nameTree, &i, buffer);

    return buffer;
}

int bre = 0;
tree_elem* TreeCtorElem(tree* nameTree, int* i, char* buffer) {
    //printf("in recursion, iteration %d\n", bre++);

    if (buffer[*i] == '{') {
        //printf("in if\n");

        //printf("i am constructing elem\n");
        tree_elem* node = (tree_elem*) calloc(1, sizeof(*node));
        (*i) += (2 * sizeof(char));
        nameTree->count++;

        //printf("Left branch?\n");
        //getchar();
        if (buffer[*i] == '{') {
            //printf("yes, going to left\n");

            node->Left = TreeCtorElem(nameTree, i, buffer);

            //printf("returned from left, reading info\n");
        }

        node->Info = &buffer[*i];
        while ( !(buffer[*i] == '{' || buffer[*i] == '}') ) (*i) ++;
        buffer[*i - 1] = '\0';
        //printf("%s - info\n", node->Info);

        //printf("Right branch?\n");
        //getchar();
        if (buffer[*i] == '{') {
            //printf("yes, going to right\n");

            node->Right = TreeCtorElem(nameTree, i, buffer);

            //printf("returned from right\n");
        }

        assert(buffer[*i] == '}');

        (*i) += (2 * sizeof(char));

        return node;
    }
}

void new_member(tree* nameTree, tree_elem* position) {
    assert_tree(nameTree);
    assert(position);

    char buffer[max_string] = {};

    printf("Who it is?\n");
    scanf("\n%s", buffer);
    char* member = strdup(buffer);

    printf("And what %s is different from %s?\n", member, position->Info);
    scanf("\n%s", buffer);
    char* question = strdup(buffer);

    char* before = position->Info;
    position->Info = question;

    TreeAdd(nameTree, before, 'L', position);
    TreeAdd(nameTree, member, 'R', position);

    assert_tree(nameTree);
}