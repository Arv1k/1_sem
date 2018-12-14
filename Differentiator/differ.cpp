#include "differ.h"

size_t CoUNT = 0;
void ReadEquation(tree* nameTree, char* input) {
    assert(input);
    assert_tree(nameTree);

    FILE* inFile = fopen(input, "rb");
    assert(inFile);

    fseek(inFile, 0, SEEK_END);
    long file_size = ftell(inFile);
    rewind(inFile);

    char* buffer = (char*) calloc(file_size + 1, sizeof(*buffer));
    buffer[file_size] = '\0';

    fread(buffer, file_size, sizeof(char), inFile);

    assert(inFile);
    fclose(inFile);

    nameTree->Tamyr = GetG(buffer);
    nameTree->count = CoUNT;

    assert_tree(nameTree);
    free(buffer);
}

char* pc = nullptr;
tree_elem* GetG(char* buff) {
    dassert(buff);

    pc = buff;

    tree_elem* val = GetE();

    dassert(pc);
    pc_assert(pc);
    return val;
}

tree_elem* GetE() {
    dassert(pc);

    tree_elem* val1 = GetT();

    while(*pc == '+' || *pc == '-') {
        char op = (*pc);

        pc++;
        while ((*pc) == ' ') pc++;

        tree_elem* val2 = GetT();

        tree_elem* val3 = (tree_elem*) calloc(1, sizeof(*val3));
        CoUNT++;

        (val3->Info).mode = MODE_SIGN;
        (val3->Info).sign = op;

        tree_elem* tmp = val1;
        val1 = val3;
        val3 = tmp;

        val1->Right = val2;
        val2->Parent = val1;

        val1->Left = val3;
        val3->Parent = val1;
    }

    dassert(pc);
    return val1;
}

tree_elem* GetT() {
    dassert(pc);

    tree_elem* val1 = GetL();

    while(*pc == '*' || *pc == '/') {
        char op = (*pc);

        pc++;
        while ((*pc) == ' ') pc++;

        tree_elem* val2 = GetP();

        tree_elem* val3 = (tree_elem*) calloc(1, sizeof(*val3));
        CoUNT++;

        (val3->Info).mode = MODE_SIGN;
        (val3->Info).sign = op;

        tree_elem* tmp = val1;
        val1 = val3;
        val3 = tmp;

        val1->Right = val2;
        val2->Parent = val1;

        val1->Left = val3;
        val3->Parent = val1;
    }

    dassert(pc);
    return val1;
}

tree_elem* GetL() {
    dassert(pc);

    tree_elem* val1 = GetP();

    if (*pc == '^') {
        tree_elem* val2 = (tree_elem*) calloc(1, sizeof(*val2));
        CoUNT++;

        pc++;
        while ((*pc) == ' ') pc++;

        (val2->Info).mode = MODE_SIGN;
        (val2->Info).sign = '^';

        val2->Left = val1;
        val1->Parent = val2;

        val2->Right = GetP();
        (val2->Right)->Parent = val2;

        return val2;
    }

    return val1;
}

tree_elem* GetP() {
    dassert(pc);

    tree_elem* val = nullptr;

    if (*pc == '(') {
        pc++;
        while ((*pc) == ' ') pc++;

        val = GetE();
        assert(*pc == ')');

        pc++;
        while ((*pc) == ' ') pc++;

        dassert(pc);
        return val;
    }

    if (*pc == 's' || *pc == 'c' || *pc == 'l' || *pc == 't' || *pc == 'a' || *pc == 'e') {

        char* word = which_word();

        if (!word) return GetN();

        while ((*pc) == ' ') pc++;

        val = GetP();

        tree_elem* val2 = (tree_elem*) calloc(1, sizeof(*val2));
        CoUNT++;

        (val2->Info).mode = MODE_OP;
        (val2->Info).op = word;

        val2->Right = val;
        val->Parent = val2;

        dassert(pc);
        return val2;
    }

    dassert(pc);
    return GetN();
}

tree_elem* GetN() {
    dassert(pc);

    tree_elem* val = (tree_elem*) calloc(1, sizeof(*val));
    CoUNT++;

    if ('0' <= (*pc) && (*pc) <= '9') {
        (val->Info).mode = MODE_NUMBER;

        while ('0' <= (*pc) && (*pc) <= '9') {
            (val->Info).number = ((val->Info).number * 10) + (*pc - '0');

            pc++;
        }
    }

    else if ('a' <= (*pc) && (*pc) <= 'z') {
        char var[max_word] = "";
        (val->Info).mode = MODE_VAR;

        int i = 0;
        while ('a' <= (*pc) && (*pc) <= 'z') {
            var[i] = (*pc);

            pc++;
            i++;
        }

        (val->Info).var = strdup(var);
    }

    else {
        printf("Invalid entry!!!\n--> %c\n", *pc);

        abort();
    }

    while ((*pc) == ' ') pc++;

    dassert(pc);
    return val;
}

size_t CooooooUnt = 0;
tree Derivative(tree* nameTree) {
    //assert_tree(nameTree);

    tree new_tree = {};
    TreeCtor(&new_tree);
    //assert_tree(&new_tree);

    new_tree.Tamyr = diff(nameTree->Tamyr);
    new_tree.count = CooooooUnt;

    //assert_tree(&new_tree);
    //assert_tree(nameTree);
    return new_tree;
}

tree_elem* diff(tree_elem* position) {
    int oper = 0;
    switch ((position->Info).mode) {
        case MODE_SIGN:
            switch ((position->Info).sign) {
                case '+':
                    return CrtNode(MODE_SIGN, '+',
                                   diff(position->Left),
                                   diff(position->Right));

                case '-':
                    return CrtNode(MODE_SIGN, '-',
                                   diff(position->Left),
                                   diff(position->Right));

                case '*':
                    return CrtNode(MODE_SIGN, '+',
                                   CrtNode(MODE_SIGN, '*',
                                           diff(position->Left),
                                           copy(position->Right)),
                                   CrtNode(MODE_SIGN, '*',
                                           copy(position->Left),
                                           diff(position->Right)));

                case '/':
                    return CrtNode(MODE_SIGN, '/',
                                   CrtNode(MODE_SIGN, '-',
                                           CrtNode(MODE_SIGN, '*',
                                                   diff(position->Left),
                                                   copy(position->Right)),
                                           CrtNode(MODE_SIGN, '*',
                                                   copy(position->Left),
                                                   diff(position->Right))),
                                   CrtNode(MODE_SIGN, '^',
                                           copy(position->Right),
                                           CrtNode(MODE_NUMBER, 2,
                                                   nullptr,
                                                   nullptr)));

                case '^':
                    return CrtNode(MODE_SIGN, '*',
                                   CrtNode(MODE_SIGN, '*',
                                           copy(position->Right),
                                           CrtNode(MODE_SIGN, '^',
                                                   copy(position->Left),
                                                   CrtNode(MODE_SIGN, '-',
                                                           copy(position->Right),
                                                           CrtNode(MODE_NUMBER, 1,
                                                                   nullptr,
                                                                   nullptr)))),
                                   diff(position->Left));
                default:
                    printf("Invalid sign!\n");

                    abort();
            }

        case MODE_NUMBER:
            return CrtNode(MODE_NUMBER, 0, nullptr, nullptr);

        case MODE_VAR:
            return CrtNode(MODE_NUMBER, 1, nullptr, nullptr);

        case MODE_OP:
            oper = which_oper((position->Info).op);

            switch (oper) {
                #define CMD_FORM(com, len, num, code) case num: {code}

                #include "com.h"

                #undef CMD_FORM

                default:
                    printf("Invalid operator!\n");

                    abort();
            }

        default:
            printf("Invalid node mode!\n");

            abort();
    }
}

int which_oper(const char* name) {
    #define CMD_FORM(com, len, num, code) if (strcmp(name, #com) == 0) return num;

    #include "com.h"

    #undef CMD_FORM
}

tree_elem* CrtNode(size_t mode, int op, tree_elem* left_guy, tree_elem* right_girl) {
    tree_elem* iskan = (tree_elem*) calloc(1, sizeof(*iskan));
    CooooooUnt++;

    (iskan->Info).mode = mode;

    switch ((iskan->Info).mode) {
        case MODE_SIGN:   (iskan->Info).sign = char (op); break;

        case MODE_NUMBER: (iskan->Info).number = op; break;

        default: abort();
    }

    iskan->Right = right_girl;
    if (right_girl != nullptr) right_girl->Parent = iskan;

    iskan->Left = left_guy;
    if (left_guy != nullptr) left_guy->Parent = iskan;

    return iskan;
}

tree_elem* CrtNode_op(const char* name, tree_elem* right_girl) {
    tree_elem* new_member = (tree_elem*) calloc(1, sizeof(*new_member));
    CooooooUnt++;

    (new_member->Info).mode = MODE_OP;
    (new_member->Info).op = strdup(name);

    new_member->Right = right_girl;
    if (right_girl != nullptr) right_girl->Parent = new_member;

    new_member->Left = nullptr;

    return new_member;
}

tree_elem* copy(tree_elem* position) {
    if (!position) return nullptr;

    tree_elem* elem = (tree_elem*) calloc(1, sizeof(*elem));
    CooooooUnt++;

    if ((position->Info).var) {
        (elem->Info).mode = (position->Info).mode;
        (elem->Info).var = strdup((position->Info).var);
    }

    else if ((position->Info).op) {
        (elem->Info).mode = (position->Info).mode;
        (elem->Info).op = strdup((position->Info).op);
    }

    else elem->Info = position->Info;

    elem->Right = copy(position->Right);

    elem->Left = copy(position->Left);

    return elem;
}

char* which_word() {
    dassert(pc);

    int i = 0;
    while (pc[i] >= 'a' && pc[i] <= 'z') i++;

    char tmp = pc[i];
    pc[i] = '\0';

    #define CMD_FORM(com, len, num, code) if (strcmp(pc, #com) == 0) {\
                                             pc[i] = tmp;\
                                             pc += len;\
                                             return strdup(#com);\
                                          }

    #include "com.h"

    #undef CMD_FORM

    pc[i] = tmp;

    dassert(pc);
    return nullptr;
}

void simple_tree(tree_elem* position, size_t* num) {
    if (!position || is_leaf(position)) return;

    simple_tree(position->Left, num);
    simple_tree(position->Right, num);

    tree_elem* tmp = nullptr;
    if ((position->Info).mode == MODE_SIGN) {
        switch ((position->Info).sign) {
            case '+':
                if (can_simp(position)) {
                    (position->Info).mode = MODE_NUMBER;

                    (position->Info).number = ((position->Left)->Info).number +
                                              ((position->Right)->Info).number;

                    TreeDoyElems(position->Left, num);
                    TreeDoyElems(position->Right, num);

                    position->Left = nullptr;
                    position->Right = nullptr;

                    break;
                }

                if (is_zero(position->Left)) {
                    if (!position->Parent) {
                        is_tamyr(position, num, 'L');
                        break;
                    }

                    (position->Right)->Parent = position->Parent;

                    if (which_side(position->Parent, position) == 1)
                        (position->Parent)->Right = position->Right;
                    else
                        (position->Parent)->Left = position->Right;

                    position->Parent = nullptr;
                    position->Right = nullptr;

                    TreeDoyElems(position, num);

                    break;
                }

                if (is_zero(position->Right)) {
                    if (!position->Parent) {
                        is_tamyr(position, num, 'R');
                        break;
                    }

                    (position->Left)->Parent = position->Parent;

                    if (which_side(position->Parent, position) == 1)
                        (position->Parent)->Right = position->Left;
                    else
                        (position->Parent)->Left = position->Left;

                    position->Parent = nullptr;
                    position->Left = nullptr;

                    TreeDoyElems(position, num);

                    break;
                }

                break;

            case '-':
                if (can_simp(position)) {
                    (position->Info).mode = MODE_NUMBER;

                    (position->Info).number = ((position->Left)->Info).number -
                                              ((position->Right)->Info).number;

                    TreeDoyElems(position->Left, num);
                    TreeDoyElems(position->Right, num);

                    position->Left = nullptr;
                    position->Right = nullptr;

                    break;
                }

                if (is_zero(position->Left)) {
                    (position->Info).sign = '*';
                    ((position->Left)->Info).number = -1;
                }

                if (is_zero(position->Right)) {
                    if (!position->Parent) {
                        is_tamyr(position, num, 'R');
                        break;
                    }

                    (position->Left)->Parent = position->Parent;

                    if (which_side(position->Parent, position) == 1)
                        (position->Parent)->Right = position->Left;
                    else
                        (position->Parent)->Left = position->Left;

                    position->Parent = nullptr;
                    position->Left = nullptr;

                    TreeDoyElems(position, num);

                    break;
                }

                break;

            case '*':
                if (can_simp(position)) {
                    (position->Info).mode = MODE_NUMBER;

                    (position->Info).number = ((position->Left)->Info).number *
                                              ((position->Right)->Info).number;

                    TreeDoyElems(position->Left, num);
                    TreeDoyElems(position->Right, num);

                    position->Left = nullptr;
                    position->Right = nullptr;

                    break;
                }

                if (is_zero(position->Left) || is_zero(position->Right)) {
                    (position->Info).mode = MODE_NUMBER;
                    (position->Info).number = 0;

                    TreeDoyElems(position->Right, num);
                    TreeDoyElems(position->Left, num);

                    position->Left = nullptr;
                    position->Right = nullptr;

                    break;
                }

                if (is_one(position->Left)) {
                    if (!position->Parent) {
                        is_tamyr(position, num, 'L');
                        break;
                    }

                    (position->Right)->Parent = position->Parent;

                    if (which_side(position->Parent, position) == 1)
                        (position->Parent)->Right = position->Right;
                    else
                        (position->Parent)->Left = position->Right;

                    position->Parent = nullptr;
                    position->Right  = nullptr;

                    TreeDoyElems(position, num);

                    break;
                }

                if (is_one(position->Right)) {
                    if (!position->Parent) {
                        is_tamyr(position, num, 'R');
                        break;
                    }

                    (position->Left)->Parent = position->Parent;

                    if (which_side(position->Parent, position) == 1)
                        (position->Parent)->Right = position->Left;
                    else
                        (position->Parent)->Left = position->Left;

                    position->Parent = nullptr;
                    position->Left   = nullptr;

                    TreeDoyElems(position, num);

                    break;
                }

                break;

            case '/':
                if (can_simp(position)) {
                    (position->Info).mode = MODE_NUMBER;

                    (position->Info).number = ((position->Left)->Info).number /
                                              ((position->Right)->Info).number;

                    TreeDoyElems(position->Left, num);
                    TreeDoyElems(position->Right, num);

                    position->Left  = nullptr;
                    position->Right = nullptr;

                    break;
                }

                if (is_zero(position->Left)) {
                    (position->Info).mode = MODE_NUMBER;
                    (position->Info).number = 0;

                    TreeDoyElems(position->Right, num);
                    TreeDoyElems(position->Left, num);

                    position->Left  = nullptr;
                    position->Right = nullptr;

                    break;
                }

                if (is_zero(position->Right)) {
                    printf("Dividing to zero!!!\n");

                    abort();
                }

                if (is_one(position->Right)) {
                    if (!position->Parent) {
                        is_tamyr(position, num, 'R');
                        break;
                    }

                    (position->Left)->Parent = position->Parent;

                    if (which_side(position->Parent, position) == 1)
                        (position->Parent)->Right = position->Left;
                    else
                        (position->Parent)->Left = position->Left;

                    position->Parent = nullptr;
                    position->Left   = nullptr;

                    TreeDoyElems(position, num);

                    break;
                }

                break;

            case '^':
                if (can_simp(position)) {
                    (position->Info).mode = MODE_NUMBER;

                    (position->Info).number = 1;
                    for (int i = 0; i < ((position->Right)->Info).number; i++)
                        (position->Info).number *= ((position->Left)->Info).number;

                    TreeDoyElems(position->Left, num);
                    TreeDoyElems(position->Right, num);

                    position->Left  = nullptr;
                    position->Right = nullptr;

                    break;
                }

                if (is_zero(position->Right) || is_one(position->Left)) {
                    (position->Info).mode = MODE_NUMBER;
                    (position->Info).number = 1;

                    TreeDoyElems(position->Right, num);
                    TreeDoyElems(position->Left, num);

                    position->Left  = nullptr;
                    position->Right = nullptr;

                    break;
                }

                if (is_one(position->Right)) {
                    if (!position->Parent) {
                        is_tamyr(position, num, 'R');

                        break;
                    }

                    (position->Left)->Parent = position->Parent;

                    if (which_side(position->Parent, position) == 1)
                        (position->Parent)->Right = position->Left;
                    else
                        (position->Parent)->Left = position->Left;

                    position->Parent = nullptr;
                    position->Left   = nullptr;

                    TreeDoyElems(position, num);

                    break;
                }

                if (is_zero(position->Left)) {
                    (position->Info).mode = MODE_NUMBER;
                    (position->Info).number = 0;

                    TreeDoyElems(position->Right, num);
                    TreeDoyElems(position->Left, num);

                    position->Left  = nullptr;
                    position->Right = nullptr;

                    break;
                }

                break;
        }
    }
}

bool is_leaf(tree_elem* position) {
    assert(position);

    if (!position->Left && !position->Right) return true;

    return false;
}

bool can_simp(tree_elem* position) {
    assert(position);

    if (((position->Left)->Info).mode == MODE_NUMBER &&
        ((position->Right)->Info).mode == MODE_NUMBER) return true;

    return false;
}

bool is_zero(tree_elem* position) {
    if (!position) return false;

    if ((position->Info).mode == MODE_NUMBER &&
        (position->Info).number == 0) return true;

    return false;
}

bool is_one(tree_elem* position) {
    if (!position) return false;

    if ((position->Info).mode == MODE_NUMBER &&
        (position->Info).number == 1) return true;

    return false;
}

void is_tamyr(tree_elem* position, size_t* num, char side) {
    tree_elem *tmp = nullptr;

    if (side == 'L') {
        TreeDoyElems(position->Left, num);
        position->Left = nullptr;

        tmp = position->Right;

        position->Info = tmp->Info;
        tmp->Parent = nullptr;

        position->Right = tmp->Right;
        (tmp->Right)->Parent = position;
        tmp->Right = nullptr;

        position->Left = tmp->Left;
        (tmp->Left)->Parent = position;
        tmp->Left = nullptr;

        TreeDoyElems(tmp, num);
    }

    else if (side == 'R') {
        TreeDoyElems(position->Right, num);
        position->Right = nullptr;

        tmp = position->Left;

        position->Info = tmp->Info;
        tmp->Parent = nullptr;

        position->Right = tmp->Right;
        (tmp->Right)->Parent = position;
        tmp->Right = nullptr;

        position->Left = tmp->Left;
        (tmp->Left)->Parent = position;
        tmp->Left = nullptr;

        TreeDoyElems(tmp, num);
    }
}




int which_side(tree_elem* par, tree_elem* son) {
    assert(par);

    if (par->Right == son) return 1;
    if (par->Left  == son) return -1;
    else return 0;
}

void tree_dot(tree* nameTree, char* dot_out) {
    assert(dot_out);
    assert_tree(nameTree);

    FILE *file_dot = fopen(dot_out, "wb");
    assert(file_dot);

    fprintf(file_dot, "digraph {\n");
    fprintf(file_dot, "\tnode[color = \"#000000\", fontsize = 20];\n"
                      "\tedge[color = \"#000000\", fontsize = 20];\n");

    create_tree(nameTree->Tamyr, file_dot);

    fprintf(file_dot, "}");

    assert(file_dot);
    fclose(file_dot);

    system("dot -Tjpg -o tree.jpg dot_out.dot");
    system("xviewer tree.jpg");

    assert_tree(nameTree);
}

int tmp = 0;
void create_tree(tree_elem* pos, FILE* dot_out) {
    assert(dot_out);
    assert(pos);

    fprintf(dot_out, "\t\they%d", tmp);
    print_mode(pos, dot_out);
    fprintf(dot_out, ";\n");

    int iskan = tmp;

    if (pos->Left != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_tree(pos->Left, dot_out);
    }

    if (pos->Right != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_tree(pos->Right, dot_out);
    }

    assert(pos);
    assert(dot_out);
}

void print_mode(tree_elem* pos, FILE* dot_out) {
    assert(pos);
    assert(dot_out);

    switch ((pos->Info).mode) {
        case MODE_OP:     fprintf(dot_out, "[label = \"%s\", shape = \"Mcircle\", "
                                           "color=\"#006400\", style=\"filled\", "
                                           "fillcolor = \"#32CD32\"]", (pos->Info).op);
                          break;

        case MODE_SIGN:   fprintf(dot_out, "[label = \"%c\", shape = \"diamond\", "
                                           "color=\"#FFD700\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->Info).sign);
                          break;

        case MODE_VAR:    fprintf(dot_out, "[label = \"%s\", shape = \"component\", "
                                           "color=\"#8B008B\", style=\"filled\", "
                                           "fillcolor = \"#9932CC\"]", (pos->Info).var);
                          break;

        case MODE_NUMBER: fprintf(dot_out, "[label = \"%d\", shape = \"Msquare\", "
                                           "color=\"#8B0000\", style=\"filled\", "
                                           "fillcolor = \"#FFA07A\"]", (pos->Info).number);
                          break;

        default:          fprintf(dot_out, "\"error\"");
                          break;
    }

    assert(pos);
    assert(dot_out);
}

void Latex(tree* nameTree, char* output) {
    FILE* out = fopen(output, "wb");
    assert(out);

    fprintf(out, "\\documentclass{article}\n"
                 "\n"
                 "\\title{formula}\n"
                 "\\author{Arv1k}\n"
                 "\n"
                 "\\begin{document}\n"
                 "\\maketitle\n"
                 "\n"
                 "$");

    TreePrint(nameTree->Tamyr, out);

    fprintf(out, "$\n"
                 "\n"
                 "\\end{document}");

    assert(out);
    fclose(out);
}
