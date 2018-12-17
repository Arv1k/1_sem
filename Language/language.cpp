#include "language.h"

size_t CoUNT = 0;
char* pc = nullptr;

void makeTree(tree* nameTree, char* buffer) {
    assert_tree(nameTree);
    assert(buffer);

    nameTree->Tamyr = GetG(buffer);
    nameTree->count = CoUNT;

    assert_tree(nameTree);
}

tree_elem* GetG(char* buff) {
    dassert(buff);

    pc = buff;

    tree_elem* val = GetTo();

    dassert(pc);
    pc_assert(pc);
    return val;
}

tree_elem* GetTo() {
    dassert(pc);

    tree_elem* val1 = nullptr;

    int smth = which_To();
    switch (smth) {
        case EGER:
            val1 = GetIf();
            break;

        case ELE:
            val1 = GetL();
            break;

        case OP_TOP:
            val1 = GetOp();
            break;

        default:
            printf("Smth wrong!\n");
            abort();
    }

    if ( (*pc) == '.') {
        tree_elem *val3 = (tree_elem *) calloc(1, sizeof(*val1));
        CoUNT++;

        (val3->Info).mode = MODE_OPERATORR;

        val3->Left = val1;
        val1->Parent = val3;

        return val3;
    }

    tree_elem* val2 = nullptr;

    while ((*pc) == ',' || (*pc) == '.') {
        pc++;

        if (*pc == '\0') break;

        while (((*pc) == ' ') || ((*pc) == '\n')) pc++;

        smth = which_To();
        switch (smth) {
            case EGER:
                val2 = GetIf();
                break;

            case ELE:
                val2 = GetL();
                break;

            case OP_TOP:
                val2 = GetOp();
                break;

            default:
                printf("Smth wrong!\n");
                abort();
        }

        tree_elem *val3 = (tree_elem *) calloc(1, sizeof(*val1));
        CoUNT++;

        (val3->Info).mode = MODE_OPERATORR;

        tree_elem* tmp = val1;
        val1 = val3;
        val3 = tmp;

        val1->Right = val2;
        val2->Parent = val1;

        val1->Left = val3;
        val3->Parent = val1;
    }


    dassert(pc);
    pc_assert((*pc) == '\n' || (*pc) == '\0');
    return val1;
}

tree_elem* GetL() {
    dassert(pc);

    tree_elem* val1 = GetC();

    pc_assert((*pc) == '"');

    pc++;
    pc_assert((*pc) == ':');

    pc++;
    while (((*pc) == ' ') || ((*pc) == '\n')) pc++;

    tree_elem* val2 = GetTo();

    tree_elem* val3 = (tree_elem *) calloc(1, sizeof(*val1));
    CoUNT++;

    (val3->Info).mode = MODE_LOOP;

    val3->Left = val1;
    val1->Parent = val3;

    val3->Right = val2;
    val2->Parent = val3;

    dassert(pc);
    return val3;
}

tree_elem* GetIf() {
    dassert(pc);

    tree_elem* val1 = GetC();

    pc_assert((*pc) == '"');

    pc++;
    pc_assert((*pc) == ':');

    pc++;
    while (((*pc) == ' ') || ((*pc) == '\n')) pc++;

    tree_elem* val2 = GetTo();

    tree_elem* val3 = (tree_elem *) calloc(1, sizeof(*val1));
    CoUNT++;

    (val3->Info).mode = MODE_IF;

    val3->Left = val1;
    val1->Parent = val3;

    val3->Right = val2;
    val2->Parent = val3;

    dassert(pc);
    return val3;
}

tree_elem* GetOp() {
    dassert(pc);

    tree_elem* val1 = GetA();

    /*while((*pc) == ',') {
        pc++;
        while (((*pc) == ' ') || ((*pc) == '\n')) pc++;

        tree_elem* val2 = GetTo();

        tree_elem* val3 = (tree_elem*) calloc(1, sizeof(*val3));
        CoUNT++;

        (val3->Info).mode = MODE_OPERATORR;

        tree_elem* tmp = val1;
        val1 = val3;
        val3 = tmp;

        val1->Right = val2;
        val2->Parent = val1;

        val1->Left = val3;
        val3->Parent = val1;
    }*/

    pc_assert(((*pc) == '.') || ((*pc) == ',') );

    dassert(pc);
    return val1;
}

tree_elem* GetA() {
    dassert(pc);

    tree_elem* val1 = nullptr;

    if ((*pc) == '"') {
        val1 = GetE();

        pc_assert((*pc) == '"');

        pc++;
        while (((*pc) == ' ') || ((*pc) == '\n')) pc++;

        if(which_A() == KURSET) {
            tree_elem* val2 = (tree_elem*) calloc(1, sizeof(*val2));
            CoUNT++;

            (val2->Info).mode = MODE_OUT;

            val2->Left = val1;
            val1->Parent = val2;

            val2->Right = nullptr;

            dassert(pc);
            return val2;
        }

        else abort();
    }

    else val1 = GetId();

    tree_elem* val2 = (tree_elem*) calloc(1, sizeof(*val2));
    CoUNT++;

    tree_elem* val3 = nullptr;
    switch (which_A()) {
        case EIT:
            (val2->Info).mode = MODE_IN;
            break;

        case TUDY:
            (val2->Info).mode = MODE_BORN;
            break;

        case BU:
            (val2->Info).mode = MODE_ASSIGN;

            while ((*pc) == ' ') pc++;

            val3 = GetE();

            val2->Left = val1;
            val1->Parent = val2;

            val2->Right = val3;
            val1->Parent = val3;

            return val2;

        case KURSET:
            (val2->Info).mode = MODE_OUT;
            break;

        default:
            abort();
    }

    val2->Left = val1;
    val1->Parent = val2;

    val2->Right = nullptr;

    dassert(pc);
    return val2;
}

tree_elem* GetC() {
    tree_elem* val1 = GetE();
    tree_elem* val2 = GetE();

    char* tmp = pc;
    pc = strchr(pc, '"');
    (*pc) = '\0';

    tree_elem* val3 = (tree_elem*) calloc(1, sizeof(*val3));
    CoUNT++;

    if      (strcmp(tmp, "зуррак") == 0)     (val3->Info).mode = MODE_BIGGER;

    else if (strcmp(tmp, "кечкенәрәк") == 0) (val3->Info).mode = MODE_LESS;

    else if (strcmp(tmp, "тигез") == 0)      (val3->Info).mode = MODE_EQUAL;

    else if (strcmp(tmp, "түгeл") == 0)      (val3->Info).mode = MODE_NOT_EQUAL;

    val3->Left = val1;
    val1->Parent = val3;

    val3->Right = val2;
    val2->Parent = val3;

    (*pc) = '"';

    dassert(pc);
    return val3;
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
        (val3->Info).number = op;

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

    tree_elem* val1 = GetP();

    while(*pc == '*' || *pc == '/') {
        char op = (*pc);

        pc++;
        while ((*pc) == ' ') pc++;

        tree_elem* val2 = GetP();

        tree_elem* val3 = (tree_elem*) calloc(1, sizeof(*val3));
        CoUNT++;

        (val3->Info).mode = MODE_SIGN;
        (val3->Info).number = op;

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
        (val2->Info).name = word;

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

    else if (('a' <= (*pc) && (*pc) <= 'z') || ('A' <= (*pc) && (*pc) <= 'Z')) {
        char var[max_word] = "";
        (val->Info).mode = MODE_VAR;

        int i = 0;
        while (('a' <= (*pc) && (*pc) <= 'z') || ('A' <= (*pc) && (*pc) <= 'Z')) {
            var[i] = (*pc);

            pc++;
            i++;
        }

        (val->Info).name = strdup(var);
    }

    else {
        printf("Invalid entry!!!\n--> %c\n", *pc);

        abort();
    }

    while ((*pc) == ' ') pc++;

    dassert(pc);
    return val;
}

tree_elem* GetId() {
    dassert(pc);

    tree_elem* val = (tree_elem*) calloc(1, sizeof(*val));
    CoUNT++;

    if (('a' <= (*pc) && (*pc) <= 'z') || ('A' <= (*pc) && (*pc) <= 'Z')) {
        char var[max_word] = "";
        (val->Info).mode = MODE_VAR;

        int i = 0;
        while (('a' <= (*pc) && (*pc) <= 'z') || ('A' <= (*pc) && (*pc) <= 'Z')) {
            var[i] = (*pc);

            pc++;
            i++;
        }

        (val->Info).name = strdup(var);
    }

    else {
        printf("Invalid entry!!!\n--> %c\n", *pc);

        abort();
    }

    while ((*pc) == ' ' || (*pc) == '\n') pc++;

    dassert(pc);
    return val;
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

int which_To() {
    dassert(pc);

    char* tmp = pc;
    pc = strchr(pc, ' ');
    (*pc) = '\0';

    if (strcmp(tmp, "әле") == 0) {
        (*pc) = ' ';

        pc += 2;

        return ELE;
    }

    else if (strcmp(tmp, "әгәр") == 0) {
        (*pc) = ' ';

        pc += 2;

        return EGER;
    }

    else {
        (*pc) = ' ';

        pc = tmp;
        while (((*pc) == ' ') || ((*pc) == '\n')) pc++;

        return OP_TOP;
    }
}

int which_A() {
    dassert(pc);

    char* tmp = pc;
    while ( !((*pc) == ',' || (*pc) == '.' || (*pc) == ' ') ) pc++;

    char tmp1 = (*pc);
    (*pc) = '\0';

    if (strcmp(tmp, "бу") == 0) {
        (*pc) = tmp1;

        return BU;
    }

    else if (strcmp(tmp, "туды") == 0) {
        (*pc) = tmp1;

        return TUDY;
    }

    if (strcmp(tmp, "әйт") == 0) {
        (*pc) = tmp1;

        return EIT;
    }

    else if (strcmp(tmp, "күрсәт") == 0) {
        (*pc) = tmp1;

        return KURSET;
    }
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

    system("dot -Tjpg -o tree.jpg dott.dot");
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
                                           "fillcolor = \"#32CD32\"]", (pos->Info).name);
            break;

        case MODE_SIGN:   fprintf(dot_out, "[label = \"%c\", shape = \"diamond\", "
                                           "color=\"#FFD700\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->Info).number);
            break;

        case MODE_VAR:    fprintf(dot_out, "[label = \"%s\", shape = \"component\", "
                                           "color=\"#8B008B\", style=\"filled\", "
                                           "fillcolor = \"#9932CC\"]", (pos->Info).name);
            break;

        case MODE_NUMBER: fprintf(dot_out, "[label = \"%d\", shape = \"Msquare\", "
                                           "color=\"#8B0000\", style=\"filled\", "
                                           "fillcolor = \"#FFA07A\"]", (pos->Info).number);
            break;

        case MODE_NAME:     fprintf(dot_out, "[label = \"%s\", shape = \"invtriangle\", "
                                           "color=\"#000000\", style=\"filled\", "
                                           "fillcolor = \"#00FFFF\"]", (pos->Info).name);
            break;

        case MODE_OPERATORR: fprintf(dot_out, "[label = \"operator\", shape = \"egg\", "
                                           "color=\"#000000\", style=\"filled\", "
                                           "fillcolor = \"#FFFFFF\"]");
            break;

        case MODE_LOOP:     fprintf(dot_out, "[label = \"loop\", shape = \"house\", "
                                           "color=\"#000000\", style=\"filled\", "
                                           "fillcolor = \"#D2691E\"]");
            break;

        case MODE_IF:     fprintf(dot_out, "[label = \"if\", shape = \"house\", "
                                           "color=\"#000000\", style=\"filled\", "
                                           "fillcolor = \"#800000\"]");
            break;

        case MODE_OUT:     fprintf(dot_out, "[label = \"out\", shape = \"box3d\", "
                                           "color=\"#000000\", style=\"filled\", "
                                           "fillcolor = \"#32CD32\"]");
            break;

        case MODE_IN:     fprintf(dot_out, "[label = \"in\", shape = \"box3d\", "
                                           "color=\"#000000\", style=\"filled\", "
                                           "fillcolor = \"#FFDEAD\"]");
            break;

        case MODE_ASSIGN:     fprintf(dot_out, "[label = \"=\", shape = \"box3d\", "
                                           "color=\"#000000\", style=\"filled\", "
                                           "fillcolor = \"#708090\"]");
            break;

        case MODE_BORN:     fprintf(dot_out, "[label = \"born\", shape = \"box3d\", "
                                               "color=\"#000000\", style=\"filled\", "
                                               "fillcolor = \"#EE82EE\"]");
            break;

        case MODE_BIGGER:     fprintf(dot_out, "[label = \">\", shape = \"parallelogram\", "
                                             "color=\"#000000\", style=\"filled\", "
                                             "fillcolor = \"#006400\"]");
            break;

        case MODE_EQUAL:     fprintf(dot_out, "[label = \"==\", shape = \"parallelogram\", "
                                               "color=\"#000000\", style=\"filled\", "
                                               "fillcolor = \"#FF7F50\"]");
            break;

        case MODE_LESS:     fprintf(dot_out, "[label = \"<\", shape = \"parallelogram\", "
                                               "color=\"#000000\", style=\"filled\", "
                                               "fillcolor = \"#FFE4B5\"]");
            break;

        case MODE_NOT_EQUAL:     fprintf(dot_out, "[label = \"!=\", shape = \"parallelogram\", "
                                               "color=\"#000000\", style=\"filled\", "
                                               "fillcolor = \"#FF4500\"]");
            break;

        default:          fprintf(dot_out, "\"error\"");
            break;
    }

    assert(pos);
    assert(dot_out);
}


