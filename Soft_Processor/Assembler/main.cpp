#include "assembler.h"

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("Wrong names of files!\n");
        return -1;
    }

    FILE* inFile = fopen(argv[1], "rb");
    char* bytecode = (char*) calloc(Size(inFile), sizeof(char));
    fclose(inFile);

    int pc = assembler(argv[1], bytecode);

    FILE* outFile = fopen(argv[2], "wb");
    fwrite(bytecode, sizeof(char), pc, outFile);
    fclose(outFile);

    free(bytecode);
}