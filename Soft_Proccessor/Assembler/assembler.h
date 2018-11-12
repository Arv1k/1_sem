#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H


#include <cstdio>
#include <cstring>
#include "enc_dir/enc.h"

const int yad = -111;

const char yad_label = -1;

const int numLabels = 20;

enum commands {
    #define DEF_CMD(name, num) CMD_##name = num,
    #define DEF_MD(name, num) MD_##name = num,
    #define DEF_REG(name, num) REG_##name = num,

    #include "../commands.h"

    #undef DEF_REG
    #undef DEF_CMD
    #undef DEF_MD
};


int assembler(const char* inputFile, char* bytecode);

void delComments(str* text);

int parser(const str* text, char* bytecode, int* Ded32);

int ASM(char* str, char* bytecode, int* pc, int* Ded32);

char which_command(char* com);

int which_reg(char* reg);


#endif //ASSEMBLER_ASSEMBLER_H
