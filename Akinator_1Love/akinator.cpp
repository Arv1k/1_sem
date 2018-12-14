#include "akinator.h"

tree_elem* question(tree_elem* position) {
    for (;;) {
        if (position->Left == nullptr) {
            printf("Может быть, это %s?\n", position->Info);
            printf("# да [y], нет [n]\n");

            return position;
        }

        printf("Это %s?\n", position->Info);
        printf("# да [y], нет [n]\n");

        char ans = 0;
        scanf("\n%c", &ans);

        if      (ans == 'n') position = position->Left;
        else if (ans == 'y') position = position->Right;
        else {
            printf("Неверная команда!\n");

            abort();
        }
    }
}

void TreeReadAkinator(tree* nameTree, FILE* enterTree) {
    assert_tree(nameTree);
    assert(enterTree);

    fseek(enterTree, 0, SEEK_END);
    long size = ftell(enterTree);
    rewind(enterTree);

    char* buffer = (char*) calloc(size + 1, sizeof(char));
    fread(buffer, sizeof(char), size, enterTree);

    int i = 0;
    nameTree->Tamyr = TreeCtorElem(nameTree, &i, buffer);

    free(buffer);
    assert_tree(nameTree);
}

//int bre = 0;
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
            (node->Left)->Parent = node;
            //printf("returned from left, reading info\n");
        }

        node->Info = &buffer[*i];
        while ( !(buffer[*i] == '{' || buffer[*i] == '}') ) (*i) ++;
        buffer[*i - 1] = '\0';
        node->Info = strdup(node->Info);
        //printf("%s - info\n", node->Info);

        //printf("Right branch?\n");
        //getchar();
        if (buffer[*i] == '{') {
            //printf("yes, going to right\n");

            node->Right = TreeCtorElem(nameTree, i, buffer);
            (node->Right)->Parent = node;

            //printf("returned from right\n");
        }

        //assert(buffer[*i] == '}');

        if (buffer[*i] != '}') {
            printf("Проблема с буфером!\n");
            abort();
        }

        (*i) += (2 * sizeof(char));

        return node;
    }

    else {
        printf("Проблема с синтаксисом буфера!\n");
        abort();
    }
}

void new_member(tree* nameTree, tree_elem* position) {
    assert_tree(nameTree);
    assert(position);

    char buffer[max_string] = {};

    printf("А кто же это?\n");
    scanf("\n%[^\n]", buffer);
    char* member = strdup(buffer);

    printf("И чем %s отличается от %s?\n", member, position->Info);
    scanf("\n%[^\n]", buffer);
    char* question = strdup(buffer);

//    position = TreeNode(nameTree, question, 'L', position);
//    TreeAdd(nameTree, member, 'R', position);

    char* before = position->Info;
    position->Info = question;

    TreeAdd(nameTree, before, 'L', position);
    TreeAdd(nameTree, member, 'R', position);

    printf("Хорошо, я запомню это.\n\n");

    assert_tree(nameTree);
}

void search_member(tree* nameTree, char* elem) {
    tree_elem* cur = TreeSearch(nameTree->Tamyr, elem);

    if (!cur) {
        printf("Здесь такого нет!\n\n");

        return;
    }

    std::stack <char*> search_stack;
    search_stack.push(nullptr);

    while (cur) {
        search_stack.push(cur->Info);

        cur = cur->Parent;
    }

    cur = nameTree->Tamyr;

    printf("Это, как мне известно");
    while (search_stack.top()) {
        search_stack.pop();

        if (search_stack.top() == nullptr) break;

        if (strcmp((cur->Left)->Info, search_stack.top()) == 0) {
            printf(", не %s", cur->Info);

            cur = cur->Left;
        }

        else {
            printf(", %s", cur->Info);

            cur = cur->Right;
        }
    }

    printf(".\n\n");
}
