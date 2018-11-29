#include "language.h"

int main(int argc, char* argv[]) {
    char* buffer = nullptr;

    buffer = Fill_the_Buffer(argv[1]);

    free(buffer);
}