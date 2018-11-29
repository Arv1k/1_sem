#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

const int max_string = 1000;

char* pc = nullptr;

#define dassert(pointer) {\
    if (!pointer) {\
        printf("| !!! Dassertion failed !!!\n");\
        printf("|       what: %s is nullptr\n", #pointer);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        abort();\
    }\
}

#define pc_assert(pc) {\
    if ( !((*pc) == '\n' || (*pc) == '\0') ) {\
        printf("| !!! Pc_assertion failed !!!\n");\
        printf("|       what: expected %d instead 0\n", *pc);\
        printf("|       in: %s,\n", __FILE__);\
        printf("|       function: %s,\n",  __PRETTY_FUNCTION__);\
        printf("|       on: %d line.\n", __LINE__);\
        abort();\
        }\
}

//G ::= E'\0'
int GetG(char* str);

// E ::= T{[+-]T}*
int GetE();

// T ::= P{[*/]P}*
int GetT();

// P :: = (E) | N
int GetP();

// N ::= [0-9]+
int GetN();


int main() {
    printf("Enter the equation:\n");

    char buffer[max_string] = {};
    fgets(buffer, max_string, stdin);

    int ans = GetG(buffer);
    printf("The answer is:\n%d\n", ans);
}


int GetG(char* str) {
    dassert(str);

    pc = str;

    int val = GetE();

    dassert(pc);
    pc_assert(pc);
    return val;
}

int GetE() {
    dassert(pc);

    int val1 = GetT();

    while(*pc == '+' || *pc == '-') {
        char op = (*pc);
        pc++;
        while ((*pc) == ' ') pc++;

        int val2 = GetT();

        if (op == '+') val1 += val2;
        else           val1 -= val2;
    }

    dassert(pc);
    return val1;
}

int GetT() {
    dassert(pc);

    int val1 = GetP();

    while(*pc == '*' || *pc == '/') {
        char op = (*pc);
        pc++;
        while ((*pc) == ' ') pc++;

        int val2 = GetP();

        if (op == '*') val1 *= val2;
        else           val1 /= val2;
    }

    return val1;
}

int GetP() {
    dassert(pc);

    if (*pc == '(') {
        pc++;
        while ((*pc) == ' ') pc++;

        int val = GetE();
        assert(*pc == ')');

        pc++;
        while ((*pc) == ' ') pc++;

        return val;
    }

    else return GetN();
}

int GetN() {
    dassert(pc);

    int val = 0;

    while ('0' <= (*pc) && (*pc) <= '9') {
        val = (val * 10) + (*pc - '0');

        pc++;
    }

    while ((*pc) == ' ') pc++;

    dassert(pc);
    return val;
}

