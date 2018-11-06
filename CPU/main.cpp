 #include "CPU.h"

int main () {
    char enter[] = "../enter.txt";

    assembler(enter);

    char asmtext[] = "../asm.txt";

    cpu(asmtext);
}
