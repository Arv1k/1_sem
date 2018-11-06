#include "CPU.h"

const char Push[] = "push";
const char Pop[] = "pop";
const char Mul[] = "mul";
const char Out[] = "out";
const char Add[] = "add";
const char End[] = "end";

enum {
    pushCom = 65,
    push_regCom = 650,
    popCom = 66,
    pop_regCom = 660,
    mulCom = 67,
    addCom = 68,
    outCom = 69,
    endCom = 70,
};


void assembler(char* inputFile) {
    str* text = Fill_the_Addresses(inputFile);

    int i = 0;

    while (text[i].String != nullptr) {
        ASM(text[i].String);

        i++;
    }

    free(text[0].String);
    free(text);
}

void ASM(char* str) {
    FILE* outputFile = fopen("../asm.txt", "ab");

    int var = 0;
    char com[6] = "";
    com[5] = '\0';

    int arguments = sscanf(str, "%s %d", com, &var);
    int numCom = 0;

    switch (arguments) {
        case 1:
            numCom = which_command(com);

            fwrite(&numCom, sizeof(int), 1, outputFile);
            break;

        case 2:
            numCom = which_command(com);

            fwrite(&numCom, sizeof(int), 1, outputFile);

            fwrite(&var, sizeof(int), 1, outputFile);
            break;

        default:
            printf("Wrong text!!!\n");
    }

    fclose(outputFile);
}

int which_command(char* com){
    int check = strcmp(com, Push);
    if (check == 0) return pushCom;

    check = strcmp(com, Pop);
    if (check == 0) return popCom;

    check = strcmp(com, Mul);
    if (check == 0) return mulCom;

    check = strcmp(com, Out);
    if (check == 0) return outCom;

    check = strcmp(com, Add);
    if (check == 0) return addCom;

    check = strcmp(com, End);
    if (check == 0) return endCom;
}

void cpu(char* outputFile) {
    FILE* asmtext = fopen(outputFile, "rb");

    long int iskan = Size(asmtext) / 4;
    int* bytecode = (int*) calloc(iskan, sizeof(int));

    fread(bytecode, sizeof(int), iskan, asmtext);


    Stack st1 = {};
    StackCtor(&st1);

    int ip = 0;
    int i = 0;
    while (bytecode[i] != endCom) {
        printf("%d\n", bytecode[i]);

        switch (which_command_cpu(bytecode[i])) {
            case pushCom:
                ip = 1;
                StackPush(&st1, bytecode[i + ip]);
                break;

            case mulCom:
                ip = 0;
                StackPush(&st1, StackPop(&st1) * StackPop(&st1));
                break;

            case outCom:
                printf("%d\n", StackPop(&st1));
                break;
        }
        i += (1 + ip);
    }

    StackDtor(&st1);
    free(bytecode);
    fclose(asmtext);
}

int which_command_cpu(int var) {
    if (var == pushCom) return pushCom;

    if (var == popCom) return popCom;

    if (var == mulCom) return mulCom;

    if (var == outCom) return outCom;

    if (var == addCom) return addCom;

    if (var == endCom) return endCom;
}