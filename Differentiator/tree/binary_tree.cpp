#include "binary_tree.h"
#include "../differ.h"

bool TreeCtor(tree* nameTree) {
    assert(nameTree);

    nameTree->count = 0;

    assert_tree(nameTree);
    return true;
}

tree_elem* TreeAdd(tree* nameTree, data_t elem, char branch, tree_elem* position) {
    assert_tree(nameTree);

    tree_elem* element = (tree_elem*) calloc(1, sizeof(tree_elem));
    element->Info = elem;

    if (nameTree->count == 0) {
        element->Parent = nullptr;

        nameTree->Tamyr = element;
        nameTree->count++;

        assert_tree(nameTree);
        return element;
    }

    if (branch == 'L') {
        element->Parent = position;

        position->Left = element;

        nameTree->count++;
    }

    if (branch == 'R') {
        element->Parent = position;

        position->Right = element;

        nameTree->count++;
    }

    assert_tree(nameTree);
    return nullptr;
}

tree_elem* TreeNode(tree* nameTree, data_t elem, char branch, tree_elem* position) {
    assert_tree(nameTree);
    assert(position);

    tree_elem* element = (tree_elem*) calloc(1, sizeof(tree_elem));
    element->Info = elem;

    element->Parent = position->Parent;
    position->Parent = element;

    if      (branch == 'L') element->Left = element;
    else if (branch == 'R') element->Right = element;

    assert_tree(nameTree);
    return nullptr;
}

void TreePrint(tree_elem* position, FILE* enterTree) {
    if (!position) return;

    if ((position->Info).mode == MODE_SIGN) {
        if ((position->Info).sign == '/') {
            fprintf(enterTree, "\\frac{");

            TreePrint(position->Left, enterTree);
            fprintf(enterTree, "}{");

            TreePrint(position->Right, enterTree);
            fprintf(enterTree, "}");

            return;
        }

        if ((position->Info).sign == '^') {
            if (is_leaf(position->Left)) TreePrint(position->Left, enterTree);

            else {
                fprintf(enterTree, "(");
                TreePrint(position->Left, enterTree);
                fprintf(enterTree, ")");
            }

            fprintf(enterTree, "^{");
            TreePrint(position->Right, enterTree);
            fprintf(enterTree, "}");

            return;
        }

        if ((position->Info).sign == '*') {
            if (is_leaf(position->Left)) TreePrint(position->Left, enterTree);

            else if (((position->Left)->Info).sign == '^' ||
                     ((position->Left)->Info).sign == '*' ||
                     ((position->Left)->Info).sign == '/' ||
                     ((position->Left)->Info).mode == MODE_OP) TreePrint(position->Left, enterTree);

            else {
                fprintf(enterTree, "(");
                TreePrint(position->Left, enterTree);
                fprintf(enterTree, ")");
            }

            if (is_leaf(position->Right)) TreePrint(position->Right, enterTree);

            else if (((position->Right)->Info).sign == '^' ||
                     ((position->Right)->Info).sign == '*' ||
                     ((position->Right)->Info).sign == '/' ||
                     ((position->Right)->Info).mode == MODE_OP) TreePrint(position->Right, enterTree);

            else {
                fprintf(enterTree, "(");
                TreePrint(position->Right, enterTree);
                fprintf(enterTree, ")");
            }

            return;
        }
    }

    TreePrint(position->Left, enterTree);

    if      ((position->Info).mode == MODE_VAR) fprintf(enterTree, "%s", (position->Info).var);

    else if ((position->Info).mode == MODE_OP) {
        if (is_leaf(position->Right)) fprintf(enterTree, "\\%s ", (position->Info).op);

        else {
            fprintf(enterTree, "\\%s(", (position->Info).op);
            TreePrint(position->Right, enterTree);
            fprintf(enterTree, ")");
        }

        return;
    }

    else if ((position->Info).mode == MODE_SIGN)   fprintf(enterTree, "%c", (position->Info).sign);

    else if ((position->Info).mode == MODE_NUMBER) fprintf(enterTree, "%d", (position->Info).number);

    TreePrint(position->Right, enterTree);
}

bool TreeDtor(tree* nameTree) {
    assert_tree(nameTree);

    TreeDoyElems(nameTree->Tamyr, &nameTree->count);

    nameTree->count = yad_count;
    nameTree->Tamyr = nullptr;

    assert(nameTree);
    return true;
}

void TreeDoyElems(tree_elem* position, size_t* con) {
    if (!position) return;

    TreeDoyElems(position->Left, con);
    TreeDoyElems(position->Right, con);

    position->Parent = nullptr;
    position->Left = nullptr;
    position->Right = nullptr;

    if ((position->Info).var != nullptr) free((position->Info).var);
    if ((position->Info).op  != nullptr) free((position->Info).op);

    (position->Info).op  = nullptr;
    (position->Info).var = nullptr;

    (position->Info).sign   = yad_sign;
    (position->Info).number = yad_num;
    (position->Info).mode   = yad_mode;

    free(position);
    (*con)--;
}

void TreeElemsOK(tree_elem* position, int* i) {
    if (!position) return;

    TreeElemsOK(position->Left, i);
    TreeElemsOK(position->Right, i);

    (*i)++;
}

bool TreeOK(tree* nameTree) {
    if (!nameTree)                                               return false;
    if (nameTree->count == 0 && nameTree->Tamyr == nullptr)      return true;
    else if (nameTree->count == 0 || nameTree->Tamyr == nullptr) return false;

    int i = 0;
    TreeElemsOK(nameTree->Tamyr, &i);
    if (i != nameTree->count)                                    return false;

    return true;
}

/*tree_elem* TreeSearch(tree_elem* position, data_t elem) {
    if (!position) return nullptr;

    if (strcmp(position->Info, elem) == 0){
        return position;
    }

    tree_elem* cur = nullptr;

    cur = TreeSearch(position->Left, elem);
    if (!cur) cur = TreeSearch(position->Right, elem);

    return cur;
}*/


