#include <unistd.h>
#include "cpu.h"

int CPUCtor(CPU* processor) {
    assert(processor);

    Stack procSt = {};
    StackCtor(&procSt);
    processor->stProc = procSt;

    processor->registers = (int*) calloc(numRegistesrs, sizeof(int));

    processor->operation_mem = (int*) calloc(operationMem, sizeof(int));

    assert(processor);

    return 1;
}

void CPUDtor(CPU* processor) {
    assert(processor);

    StackDtor(&processor->stProc);

    memset(processor->registers, yad_cpu, numRegistesrs * sizeof(int));
    free(processor->registers);

    memset(processor->operation_mem, yad_cpu, operationMem * sizeof(int));
    free(processor->operation_mem);

    assert(processor);
}

void cpu(char* bytecode, CPU* processor) {
    int pc = 0;
    int prom = 0;

    std::stack <int> callLabels;

    while (bytecode[pc] != CMD_END) {
        switch (bytecode[pc]) {
            #define DEF_CMD(name, num, assembler, processor) case num:{processor break;}

            #define DEF_MD(name, num) ;

            #define DEF_REG(name, num) ;

            #include "../commands.h"

            #undef DEF_CMD
            #undef DEF_MD
            #undef DEF_REG
        }
    }
}

