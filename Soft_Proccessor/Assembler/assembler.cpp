#include "assembler.h"

int assembler(const char* inputFile, char* bytecode) {
    assert(inputFile);
    assert(bytecode);

    str *text = Fill_the_Addresses(inputFile);
    delComments(text);

    int Ded32[numLabels] = {};
    memset(Ded32, yad_label, numLabels * sizeof(int));

    int callLabels[numLabels] = {};
    memset(callLabels, yad_label, numLabels * sizeof(int));

    parser(text, bytecode, Ded32, callLabels);
    int pc = parser(text, bytecode, Ded32, callLabels);

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

int parser(const str* text, char* bytecode, int* Ded32, int* callLabels) {
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

        ASM(text[i].String, bytecode, &pc, Ded32, callLabels);

        i++;
    }

    assert(text);
    assert(bytecode);
    assert(Ded32);

    return pc;
}

int ASM(char* str, char* bytecode, int* pc, int* Ded32, int* callLabels) {
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
        case CMD_PUSH:
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            sscanf(str, "%s %s", com, reg);

            if (reg[0] == '[') {
                if (reg[1] >= '0' && reg[1] <= '9') {
                    bytecode[*pc] = MD_PUSH_FROM_RAM;
                    *pc += sizeof(char);

                    sscanf(str, "%s [%d]", com, &var);

                    ((int *) (bytecode + *pc))[0] = var;
                    *pc += sizeof(int);

                    break;
                }

                sscanf(str, "%s [%s]", com, reg);

                reg_num = which_reg(reg);
                if (reg_num == yad) {
                    printf("Invalid register!\n");
                    abort(); //change to assert
                }

                bytecode[*pc] = MD_PUSH_FROM_RAM;
                *pc += sizeof(char);

                ((int *) (bytecode + *pc))[0] = reg_num;
                *pc += sizeof(int);

                break;
            }

            if (reg[0] == 'r') {
                reg_num = which_reg(reg);
                if (reg_num == yad) {
                    printf("Invalid register!\n");
                    abort(); //change to assert
                }

                bytecode[*pc] = MD_PUSH_REG;
                *pc += sizeof(char);

                ((int *) (bytecode + *pc))[0] = reg_num;
                *pc += sizeof(int);

                break;
            }

            if (reg[0] >= '0' && reg[0] <= '9') {
                sscanf(str, "%s %d", com, &var);

                bytecode[*pc] = MD_PUSH_INT;
                *pc += sizeof(char);

                ((int *) (bytecode + *pc))[0] = var;
                *pc += sizeof(int);

                break;
            }

            printf("Invalid line!\n");
            break;

        case CMD_POP:
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            if (sscanf(str, "%s %s", com, reg) == 1) {
                bytecode[*pc] = MD_POP_FROM;
                *pc += sizeof(char);

                break;
            }

            if (reg[0] == '[') {
                if (reg[1] >= '0' && reg[1] <= '9') {
                    bytecode[*pc] = MD_POP_IN_RAM;
                    *pc += sizeof(char);

                    sscanf(str, "%s [%d]", com, &var);

                    ((int *) (bytecode + *pc))[0] = var;
                    *pc += sizeof(int);

                    break;
                }

                sscanf(str, "%s [%s]", com, reg);

                reg_num = which_reg(reg);
                if (reg_num == yad) {
                    printf("Invalid register!\n");
                    abort(); //change to assert
                }

                bytecode[*pc] = MD_POP_IN_RAM_REG;
                *pc += sizeof(char);

                ((int *) (bytecode + *pc))[0] = reg_num;
                *pc += sizeof(int);

                break;
            }

            if (reg[0] == 'r') {
                reg_num = which_reg(reg);
                if (reg_num == yad) {
                    printf("Invalid register!\n");
                    abort(); //change to assert
                }

                bytecode[*pc] = MD_POP_IN_REG;
                *pc += sizeof(char);

                ((int *) (bytecode + *pc))[0] = reg_num;
                *pc += sizeof(int);

                break;
            }

            printf("Invalid line!\n");
            break;

        case CMD_MUL:
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            break;

        case CMD_IN:
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            break;

        case CMD_ADD:
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            break;

        case CMD_DIV:
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            break;

        case CMD_SUB:
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            break;

        case CMD_OUT:
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            break;

        case CMD_END:
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            break;

        case CMD_SQRT:
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            break;

        case CMD_CAT:
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            break;

        case CMD_JMP:
            sscanf(str, "%s :%d", com, &var);
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            ((int*) (bytecode + *pc)) [0] = Ded32[var];
            *pc += sizeof(int);

            break;

        case CMD_JA:
            sscanf(str, "%s :%d", com, &var);
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            ((int*) (bytecode + *pc)) [0] = Ded32[var];
            *pc += sizeof(int);

            break;

        case CMD_JB:
            sscanf(str, "%s :%d", com, &var);
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            ((int*) (bytecode + *pc)) [0] = Ded32[var];
            *pc += sizeof(int);

            break;

        case CMD_JC:
            sscanf(str, "%s :%d", com, &var);
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            ((int*) (bytecode + *pc)) [0] = Ded32[var];
            *pc += sizeof(int);

            break;

        case CMD_JAC:
            sscanf(str, "%s :%d", com, &var);
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            ((int*) (bytecode + *pc)) [0] = Ded32[var];
            *pc += sizeof(int);

            break;

        case CMD_JBC:
            sscanf(str, "%s :%d", com, &var);
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            ((int*) (bytecode + *pc)) [0] = Ded32[var];
            *pc += sizeof(int);

            break;

        case CMD_JRC:
            sscanf(str, "%s :%d", com, &var);
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            ((int*) (bytecode + *pc)) [0] = Ded32[var];
            *pc += sizeof(int);

            break;

        case CMD_CALL:
            sscanf(str, "%s :%d", com, &var);
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            ((int*) (bytecode + *pc)) [0] = Ded32[var];

            *pc += sizeof(int);

            callLabels[var] = *pc;

            break;

        case CMD_RET:
            sscanf(str, "%s :%d", com, &var);
            bytecode[*pc] = numCom;
            *pc += sizeof(char);

            ((int*) (bytecode + *pc)) [0] = callLabels[var];
            *pc += sizeof(int);

            break;

        default:
            printf("Wrong text!!!\n");

            break;
    }

    assert(str);
    assert(bytecode);
    assert(Ded32);

    return 1;
}

char which_command(char* com) {
    int check = 0;
    #define DEF_CMD(name, num) check = strcasecmp(com, #name);\
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

    #define DEF_CMD(name, num)  ;

    #define DEF_MD(name, num)  ;

    #include "../commands.h"

    #undef DEF_REG
    #undef DEF_CMD
    #undef DEF_MD

    assert(reg);

    return yad;
}




