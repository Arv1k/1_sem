#include "binary_tree.h"

bool TreeCtor(tree* nameTree) {
    assert(nameTree);

    nameTree->count = 0;

    assert_tree(nameTree);
    return true;
}

tree_elem* TreeAdd(tree* nameTree, data_t elem, char branch, tree_elem* position) {
    assert_tree(nameTree);
//    assert(position);

    if (nameTree->count == 0) {
        tree_elem* element = (tree_elem*) calloc(1, sizeof(tree_elem));
        element->Info = elem;

        element->Parent = nullptr;

        nameTree->Tamyr = element;
        nameTree->count++;

        assert_tree(nameTree);
        return element;
    }

    if (branch == 'L') {
        tree_elem* element = (tree_elem*) calloc(1, sizeof(tree_elem));
        element->Info = elem;

        element->Parent = position;

        position->Left = element;

        nameTree->count++;

        assert_tree(nameTree);
        return element;
    }

    if (branch == 'R') {
        tree_elem* element = (tree_elem*) calloc(1, sizeof(tree_elem));
        element->Info = elem;

        element->Parent = position;

        position->Right = element;

        nameTree->count++;

        assert_tree(nameTree);
        return element;
    }

    assert_tree(nameTree);
    return nullptr;
}

tree_elem* TreeNode(tree* nameTree, data_t elem, char branch, tree_elem* position) {
    assert_tree(nameTree);
    assert(position);

    if (branch == 'L') {
        tree_elem* element = (tree_elem*) calloc(1, sizeof(tree_elem));
        element->Info = elem;

        element->Parent = position->Parent;
        position->Parent = element;

        if ((element->Parent)->Left == position) {
            (element->Parent)->Left = element;

            element->Left = position;

            nameTree->count++;

            assert_tree(nameTree);
            return element;
        }

        else if ((element->Parent)->Right == position) {
            (element->Parent)->Right = element;

            element->Left = position;

            nameTree->count++;

            assert_tree(nameTree);
            return element;
        }

        assert_tree(nameTree);
        return nullptr;
    }

    else if (branch == 'R') {
        tree_elem* element = (tree_elem*) calloc(1, sizeof(tree_elem));
        element->Info = elem;

        element->Parent = position->Parent;
        position->Parent = element;

        if ((element->Parent)->Left == position) {
            (element->Parent)->Left = element;

            element->Right = position;

            nameTree->count++;

            assert_tree(nameTree);
            return element;
        }

        else if ((element->Parent)->Right == position) {
            (element->Parent)->Right = element;

            element->Right = position;

            nameTree->count++;

            assert_tree(nameTree);
            return element;
        }

        assert_tree(nameTree);
        return nullptr;
    }

    assert_tree(nameTree);
    return nullptr;
}



void TreePrint(tree_elem* position, FILE* enterTree) {
    if (!position) return;

    fprintf(enterTree, "{\n");
    TreePrint(position->Left, enterTree);

    fprintf(enterTree, "%s\n", position->Info);
    TreePrint(position->Right, enterTree);

    fprintf(enterTree, "}\n");
}

bool TreeDtor(tree* nameTree) {
    assert_tree(nameTree);

    TreeDoyElems(nameTree->Tamyr);

    nameTree->count = 0;
    nameTree->Tamyr = nullptr;

    assert(nameTree);
    return true;
}

void TreeDoyElems(tree_elem* position) {
    if (!position) return;

    TreeDoyElems(position->Left);
    TreeDoyElems(position->Right);

    position->Parent = nullptr;
    position->Left = nullptr;
    position->Right = nullptr;

    position->Info = yad_elem;

    free(position);
}

bool TreeOK(tree* nameTree) {
    if (!nameTree)                                               return false;
    if (nameTree->count == 0 && nameTree->Tamyr == nullptr)      return true;
    else if (nameTree->count == 0 || nameTree->Tamyr == nullptr) return false;

    return true;
}



