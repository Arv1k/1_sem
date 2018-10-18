#include "CPU.h"

int main() {
    str* Strings_of_enter = Fill_the_Addresses("/home/victoroff/CLionProjects/CPU/enter.txt");

    char command[4];
    int val;
    sscanf(Strings_of_enter[0].String, "%s %d", command, &val);

    printf("%s %d\n", command, val);
}
