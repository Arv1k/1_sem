#include "cpu.h"

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Wrong name of file!\n");
        return -1;
    }

    FILE* inFile = fopen(argv[1], "rb");

    fseek(inFile, 0, SEEK_END);
    unsigned long iskan = ftell(inFile);
    fseek(inFile, 0, SEEK_SET);

    char* bytecode = (char*) calloc(iskan, sizeof(char));
    fread(bytecode, sizeof(char), iskan, inFile);
    fclose(inFile);

    CPU processor = {};
    CPUCtor(&processor);

    cpu(bytecode, &processor);

    CPUDtor(&processor);
    free(bytecode);
}