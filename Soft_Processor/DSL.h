#ifndef ASSEMBLER_DSL_H
#define ASSEMBLER_DSL_H


#define REC(what, mode) {\
    if (mode == 'c') {\
        bytecode[*pc] = what;\
        *pc += sizeof(char);\
    }\
    else if (mode == 'i') {\
        ((int *) (bytecode + *pc))[0] = what;\
        *pc += sizeof(int);\
    }\
}

#define WHICH_REG(mode) {\
    reg_num = which_reg(reg);\
    if (reg_num == yad) {\
        printf("Invalid register!\n");\
        abort();\
    }\
    REC(mode, 'c');\
    REC(reg_num, 'i');\
}

#define ASM_FORMAT(format, ...) sscanf (str, (format), __VA_ARGS__)

#define PUUSH(what) StackPush(&processor->stProc, what);

#define POOP() StackPop(&processor->stProc)

#define CUR_SHIFT ((int *) (bytecode + pc))[0]

#define REEG processor->registers[CUR_SHIFT - 97]

#define RAAAM(what) processor->operation_mem[what]

#define PC(what) {\
    if (what == 'c')      pc += sizeof(char);\
    else if (what == 'i') pc += sizeof(int);\
    else                  pc = what;\
}

#define SqRt(what) (int) sqrt(what)

#define CALL() callLabels.push(pc + sizeof(int))

#define REET() {\
    pc = callLabels.top();\
    callLabels.pop();\
}


#endif //ASSEMBLER_DSL_H