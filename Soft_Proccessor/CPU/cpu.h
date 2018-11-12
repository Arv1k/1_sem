#ifndef CPU_CPU_H
#define CPU_CPU_H


#include <cstdio>
#include <cstring>
#include <cmath>
#include <stack>
#include "stack_dir/stack.h"


enum commands {
    #define DEF_CMD(name, num, assembler, processor) CMD_##name = num,
    #define DEF_MD(name, num) MD_##name = num,
    #define DEF_REG(name, num) REG_##name = num,

    #include "../commands.h"

    #undef DEF_CMD
    #undef DEF_MD
    #undef DEF_REG
};

const int operationMem = 32;

const int numRegistesrs = 5;

const char yad_cpu = -11;

struct CPU {
    Stack stProc = {};
    int* operation_mem = nullptr;
    int* registers = nullptr;
};


void cpu(char* bytecode, CPU* processor);

int CPUCtor(CPU* processor);

void CPUDtor(CPU* processor);


#endif //CPU_CPU_H
