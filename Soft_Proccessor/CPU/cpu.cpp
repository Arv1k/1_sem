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

    while (bytecode[pc] != CMD_END) {
        switch (bytecode[pc]) {
            case CMD_PUSH:
                pc += sizeof(char);

                switch (bytecode[pc]) {
                    case MD_PUSH_REG:
                        pc += sizeof(char);

                        StackPush(&processor->stProc,
                                  processor->registers[ ((int *) (bytecode + pc)) [0] - 97 ]);

                        pc += sizeof(int);

                        break;

                    case MD_PUSH_INT:
                        pc += sizeof(char);

                        StackPush(&processor->stProc,
                                  ((int *) (bytecode + pc))[0]);

                        pc += sizeof(int);

                        break;

                    case MD_PUSH_FROM_RAM:
                        pc += sizeof(char);

                        StackPush(&processor->stProc,
                                  processor->operation_mem[ ((int *) (bytecode + pc)) [0] ]);

                        pc += sizeof(int);

                        sleep(1);

                        break;

                    case MD_PUSH_FROM_RAM_REG:
                        pc += sizeof(char);

                        StackPush(&processor->stProc,
                                  processor->operation_mem
                                  [ processor->registers[ ((int *) (bytecode + pc)) [0] - 97 ] ]);

                        pc += sizeof(int);

                        sleep(1);

                        break;
                }

                break;

            case CMD_POP:
                pc += sizeof(char);

                switch (bytecode[pc]) {
                    case MD_POP_FROM:
                        pc += sizeof(char);

                        StackPop(&processor->stProc);

                        pc += sizeof(char);

                        break;

                    case MD_POP_IN_REG:
                        pc += sizeof(char);

                        processor->registers[ ((int *) (bytecode + pc)) [0] - 97 ] = StackPop(&processor->stProc);

                        pc += sizeof(int);

                        break;

                    case MD_POP_IN_RAM:
                        pc += sizeof(char);

                        processor->operation_mem[ ((int *) (bytecode + pc)) [0] ] = StackPop(&processor->stProc);

                        pc += sizeof(int);

                        sleep(1);

                        break;

                    case MD_POP_IN_RAM_REG:
                        pc += sizeof(char);

                        processor->operation_mem[ processor->registers[ ((int *) (bytecode + pc)) [0] - 97 ] ]
                        = StackPop(&processor->stProc);

                        pc += sizeof(int);

                        sleep(1);

                        break;
                }

                break;

            case CMD_MUL:
                StackPush(&processor->stProc, StackPop(&processor->stProc) * StackPop(&processor->stProc));

                pc += sizeof(char);

                break;

            case CMD_ADD:
                StackPush(&processor->stProc, StackPop(&processor->stProc) + StackPop(&processor->stProc));

                pc += sizeof(char);

                break;

            case CMD_DIV:
                prom = StackPop(&processor->stProc);
                StackPush(&processor->stProc, StackPop(&processor->stProc) / prom);

                pc += sizeof(char);

                break;

            case CMD_SUB:
                prom = StackPop(&processor->stProc);
                StackPush(&processor->stProc, StackPop(&processor->stProc) - prom);

                pc += sizeof(char);

                break;

            case CMD_OUT:
                printf("%d\n", StackPop(&processor->stProc));

                pc += sizeof(char);

                break;

            case CMD_IN:
                printf("Please, enter the number:\n");

                scanf("%d", &prom);
                StackPush(&processor->stProc, prom);

                pc += sizeof(char);

                break;

            case CMD_SQRT:
                StackPush(&processor->stProc, ( (int) sqrt(StackPop(&processor->stProc)) ) );

                pc += sizeof(char);

                break;

            case CMD_CAT:
                printf("                   /\\             /\\\n"
                       "                  |`\\\\_,--=\"=--,_//`|  \n"
                       "                  \\ .\"  :'. .':  \". /\n"
                       "                 ==)  _ :  '  : _  (==\n"
                       "                   |>/O\\   _   /O\\<|\n"
                       "                   | \\-\"~` _ `~\"-/ |\n"
                       "                  >|`===. \\_/ .===`|<\n"
                       "        Ded .-\"-.   \\==='  |  '===/   .-\"-.\n"
                       "     .-----{'. '`}---\\,  .-'-.  ,/---{.'. '}-----.\n"
                       "     |     `\"---\"`     `~-===-~`     `\"---\"`     |\n"
                       "     |     .-------------------------------.     |\n"
                       "     |     |                               |     |\n"
                       "     |     |                               |     |\n"
                       "     |     |                    .--.       |     |\n"
                       "     |     |                  .\"  o \\__    |     |\n"
                       "     |     |               _.-\"    ,(  `   |     |\n"
                       "     |     |           _.-\"      ,;;|      |     |\n"
                       "     |     |      _.-=\" _,\"    ,,;;;'      |     |\\  \n"
                       "     |     |  .-\"`_.-\"``-..,,;;;;:'        |     |'\\\n"
                       "     |     |  `\"'`          `\\`\\           |     |.'`\\\n"
                       "     |     |                 /^\\\\\\         |     |'.'`}\n"
                       "     |     |                               |     } '. }\n"
                       "     |     |                               |    /.'`./\n"
                       "     |     '-------------------------------'   /. './\n"
                       "    _|  _                                     /.`'./\n"
                       "   (.\\-/.)--------.__________________.-------{.'. {\n"
                       "    \\0 0/         /                  \\       `\\.'`\\\n"
                       "(   =\\ /=  ______/....................\\______  \\.'.\\\n"
                       " \\   /o\\  |                                  |  }'.'}\n"
                       "  ) /   \\ | [[[[[[[[[[ ===       ()  ()  ()  | {'.'/\n"
                       " (  U   U |                       ________   |  `~`\n"
                       "  \\(|   |)| [[[[[[[[[[ ===       [________]  |\n"
                       "   _w___w_:----------------------------------:_______\n"
                       "  |  []  [][][][] [][][][] [][][][] [][][]  == ===== |\n"
                       "  |                                                  |\n"
                       "  |   [][][][][][][][][][][][][][]_ [][][] [][][][]  |\n"
                       "  |   [_][][][][][][][][][][][][]| |[][][] [][][]||  |\n"
                       "  |   []  [][][][][][][][][][][][__|       [][][]||  |\n"
                       "  |   [__] [][][][][][][][][][][___]  []   [][][]||  |\n"
                       "  |   [_]  [_][_____________][_] [_][][][] [__][]||  |\n"
                       "  '--------------------------------------------------'\n");

                pc += sizeof(char);

                break;

            case CMD_JMP:
                pc += sizeof(char);

                pc = ((int*) (bytecode + pc)) [0];

                break;

            case CMD_JA:
                prom = StackPop(&processor->stProc);
                pc += sizeof(char);

                if (prom > StackPop(&processor->stProc)) {
                    pc = ((int*) (bytecode + pc)) [0];

                    break;
                }

                pc += sizeof(int);

                break;

            case CMD_JC:
                prom = StackPop(&processor->stProc);
                pc += sizeof(char);

                if (prom == StackPop(&processor->stProc)) {
                    pc = ((int*) (bytecode + pc)) [0];

                    break;
                }

                pc += sizeof(int);

                break;

            case CMD_JB:
                prom = StackPop(&processor->stProc);
                pc += sizeof(char);

                if (prom < StackPop(&processor->stProc)) {
                    pc = ((int*) (bytecode + pc)) [0];

                    break;
                }

                pc += sizeof(int);

                break;

            case CMD_JAC:
                prom = StackPop(&processor->stProc);
                pc += sizeof(char);

                if (prom >= StackPop(&processor->stProc)) {
                    pc = ((int*) (bytecode + pc)) [0];

                    break;
                }

                pc += sizeof(int);

                break;

            case CMD_JBC:
                prom = StackPop(&processor->stProc);
                pc += sizeof(char);

                if (prom <= StackPop(&processor->stProc)) {
                    pc = ((int*) (bytecode + pc)) [0];

                    break;
                }

                pc += sizeof(int);

                break;

            case CMD_JRC:
                prom = StackPop(&processor->stProc);
                pc += sizeof(char);

                if (prom != StackPop(&processor->stProc)) {
                    pc = ((int*) (bytecode + pc)) [0];

                    break;
                }

                pc += sizeof(int);

                break;

            case CMD_CALL:
                pc += sizeof(char);

                pc = ((int*) (bytecode + pc)) [0];

                break;

            case CMD_RET:
                pc += sizeof(char);

                pc = ((int*) (bytecode + pc)) [0];

                break;
        }
    }
}

