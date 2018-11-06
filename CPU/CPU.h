#ifndef CPU_CPU_H
#define CPU_CPU_H


#include "enc_dir/enc.h"
#include "stack_dir/stack.h"

void assembler(char* inputFile);
void ASM(char* str);
int which_command(char* com);
void cpu(char* outputFile);
int which_command_cpu(int var);


#endif //CPU_CPU_H
