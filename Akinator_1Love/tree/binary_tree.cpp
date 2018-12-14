#include "binary_tree.h"

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

    fprintf(enterTree, "{\n");
    TreePrint(position->Left, enterTree);

    fprintf(enterTree, "%s\n", position->Info);
    TreePrint(position->Right, enterTree);

    fprintf(enterTree, "}\n");
}

bool TreeDtor(tree* nameTree) {
    assert_tree(nameTree);

    TreeDoyElems(nameTree->Tamyr);

    nameTree->count = yad_count;
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

    free(position->Info);
    position->Info = yad_elem;

    free(position);
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

tree_elem* TreeSearch(tree_elem* position, data_t elem) {
    if (!position) return nullptr;

    if (strcmp(position->Info, elem) == 0){
        return position;
    }

    tree_elem* cur = nullptr;

    cur = TreeSearch(position->Left, elem);
    if (!cur) cur = TreeSearch(position->Right, elem);

    return cur;
}

void akinator_dot (tree* nameTree, char* dot_out) {
    FILE *file_dot = fopen(dot_out, "wb");
    assert(file_dot);

    fprintf(file_dot, "digraph {\n");
    fprintf(file_dot, "\tnode[shape = \"octagon\", color = \"#191970\", fontsize = 12, style = \"filled\", fillcolor = \"#87CEFA\"];\n"
                      "\tedge[color = \"#191970\", fontsize = 14];\n");

    create_tree (nameTree->Tamyr, file_dot);

    fprintf(file_dot, "}");

    assert(file_dot);
    fclose(file_dot);

    system("dot -Tjpg -o tree.jpg dot_out.dot");
    system("xviewer tree.jpg");
}

void create_tree (tree_elem* pos, FILE* dot_out) {
    if (pos->Left != nullptr) {
        fprintf (dot_out, "\n\t\t\"%s\"[shape = \"ellipse\", color=\"#191970\", style=\"filled\", fillcolor = \"#E0FFFF\"];\n"
                          "\t\t\"%s\"->\"%s\"[label = \"No\"];\n", pos->Info, pos->Info, (pos->Left)->Info);

        create_tree (pos->Left, dot_out);
    }

    if (pos->Right != nullptr) {
        fprintf (dot_out, "\n\t\t\"%s\"[shape = \"egg\", color=\"#191970\", style=\"filled\", fillcolor = \"#E0FFFF\"];\n"
                          "\t\t\"%s\"->\"%s\"[label = \"Yes\"];\n", pos->Info, pos->Info, (pos->Right)->Info);

        create_tree (pos->Right, dot_out);
    }
}

