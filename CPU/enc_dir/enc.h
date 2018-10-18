#ifndef ENC_ENC_H
#define ENC_ENC_H


#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cstdlib>

#ifdef Meow
#define PRINTF printf
#else
#define PRINTF
#endif

//----------------------------------------------------------------------------------------------------------------------
//! This structure created for our text. Here we have addresses of strings and their length.
//----------------------------------------------------------------------------------------------------------------------

struct str {
    char*         String;
    unsigned long Length;
};


void Sorter(const char* nameInput, const char* nameOutput);

str* Fill_the_Addresses(const char* nameInput);

char* Fill_the_Buffer(const char* nameInput, unsigned int* NumStrings);

long int Size(FILE* InputFile);

unsigned int numberSymbol(const char* Buffer, char Symbol);

void Sort_the_Addresses(str* Addresses);

void Sort_the_Addresses_from_the_end(str* Addresses);

int Comparator(const void* string1, const void* string2);

void Fill_the_OutputFile(str* Addresses, const char* nameOutput);

void cleanMemory(str* Addresses, char** CP_Addresses_of_Strings);


#endif //ENC_ENC_H