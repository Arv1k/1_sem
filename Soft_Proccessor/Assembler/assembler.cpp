#include "assembler.h"

int assembler(const char* inputFile, char* bytecode) {
    assert(inputFile);
    assert(bytecode);

    str *text = Fill_the_Addresses(inputFile);
    delComments(text);

    int Ded32[numLabels] = {};
    memset(Ded32, yad_label, numLabels * sizeof(int));

    parser(text, bytecode, Ded32);
    int pc = parser(text, bytecode, Ded32);

    bytecode[pc] = '\0';

    free(text[0].String);
    free(text);

    assert(bytecode);
    assert(inputFile);

    return pc;
}

void delComments(str* text) {
    assert(text);

    int i = 0;
    while (text[i].String != nullptr) {
        char* c = nullptr;
        if ( (c = strchr(text[i].String, ';')) != nullptr ) {
            c[0] = '\0';
        }
        i++;
    }

    assert(text);
}

int parser(const str* text, char* bytecode, int* Ded32) {
    assert(text);
    assert(bytecode);
    assert(Ded32);

    int i = 0;
    int pc = 0;
    while (text[i].String != nullptr) {
        if (text[i].String[0] == '\0') {
            i++;
            continue;
        }

        ASM(text[i].String, bytecode, &pc, Ded32);

        i++;
    }

    assert(text);
    assert(bytecode);
    assert(Ded32);

    return pc;
}

int ASM(char* str, char* bytecode, int* pc, int* Ded32) {
    assert(str);
    assert(bytecode);
    assert(Ded32);

    char com[10] = "";
    int var = 0;

    sscanf(str, "%s", com);

    if (com[0] == ':') {
        sscanf(str, ":%d", &var);

        Ded32[var] = *pc;

        return 1;
    }

    char numCom = which_command(com);
    if (numCom == yad) {
        printf("Invalid text!\n");
        abort(); //change to assert
    }

    char reg[10] = "";
    int reg_num = 0;
    var = 0;

    switch (numCom) {
        #define DEF_CMD(name, num, assembler, processor) case num:{assembler break;}

        #define DEF_MD(name, num) ;

        #define DEF_REG(name, num) ;

        #include "../commands.h"

        #undef DEF_REG
        #undef DEF_CMD
        #undef DEF_MD
    }

    assert(str);
    assert(bytecode);
    assert(Ded32);

    return 1;
}

char which_command(char* com) {
    int check = 0;
    #define DEF_CMD(name, num, asm_body, proc_body) check = strcasecmp(com, #name);\
                                                    if (check == 0) return num;

    #define DEF_MD(name, num)  ;

    #define DEF_REG(name, num) ;

    #include "../commands.h"

    #undef DEF_REG
    #undef DEF_CMD
    #undef DEF_MD

    return yad;
}

int which_reg(char* reg) {
    assert(reg);

    int check = 0;
    #define DEF_REG(name, num) check = strcasecmp(reg, #name);\
                               if (check == 0) return num;

    #define DEF_CMD(name, num, assembler, processor)  ;

    #define DEF_MD(name, num)  ;

    #include "../commands.h"

    #undef DEF_REG
    #undef DEF_CMD
    #undef DEF_MD

    assert(reg);

    return yad;
}




