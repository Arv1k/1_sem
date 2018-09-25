//! @file main.cpp
//----------------------------------------------------------------------------------------------------------------------
//! Version 4.0
//!
//! This program creates the Encyclopedia of any Poem.
//!
//! In version 4.0 improved some things
//!
//! Thanks to Vlad Aleinik for the great help!
//----------------------------------------------------------------------------------------------------------------------
//! @mainpage
//! - main.cpp

#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cstdlib>

void Sorter(FILE* InputFile, FILE* OutputFile);
unsigned int Counter_of_Symbols(FILE* InputFile);
char* Fill_the_Buffer(FILE* InputFile, unsigned int* NumStrings);
char** Fill_the_Addresses(char* Buffer, unsigned int NumStrings);
void Sort_the_Addresses(char** Addresses_of_Strings, unsigned int NumStrings);
int Comparator(const void* string1, const void* string2);
void Fill_the_OutputFile(FILE* OutputFile, char** Addresses_of_Strings, unsigned int NumStrings);

//----------------------------------------------------------------------------------------------------------------------
//! main function\n\n
//! In this function only two parameters, both of them - files.\n
//! We use only one function in main - Sorter.
//! @param [in] InputFile - from here we take the text
//! @param [out] OutputFile - here we put sorted text
//----------------------------------------------------------------------------------------------------------------------

int main() {
    FILE* InputFile = nullptr;
    FILE* OutputFile = nullptr;

    Sorter(InputFile, OutputFile);
}

//----------------------------------------------------------------------------------------------------------------------
//! Sorter\n
//! Since the function only read from InputFile and write in OutputFile, its type is void.\n
//! In this variation, we have the buffer (Buffer) with all the text and an array with pointers (Addresses_of_Strings) to the beginning of the strings in this buffer.
//! Also we have here another functions, so read their descriptions below.
//!
//! @param [num] NumStrings - number of strings in InputFile (used for Addresses_of_Strings)
//! @param [arr] Buffer - buffer with the text
//! @param [arr] Addresses_of_Strings - here there are addresses of strings in buffer
//----------------------------------------------------------------------------------------------------------------------

void Sorter(FILE* InputFile, FILE* OutputFile) {
    unsigned int NumStrings = 0;

    char* Buffer = Fill_the_Buffer(InputFile, &NumStrings);

    char** Addresses_of_Strings = Fill_the_Addresses(Buffer, NumStrings);

    Sort_the_Addresses(Addresses_of_Strings, NumStrings);

    Fill_the_OutputFile(OutputFile, Addresses_of_Strings, NumStrings);

    free(Addresses_of_Strings);
    free(Buffer);
}

//----------------------------------------------------------------------------------------------------------------------
//! Counter_of_Symbols\n
//! Before we will create the Buffer, we need to know his size.
//! After we know the NumSymbols, we can allocate memory for array.
//----------------------------------------------------------------------------------------------------------------------

unsigned int Counter_of_Symbols(FILE* InputFile) {
    fseek(InputFile, 0, SEEK_END);
    unsigned int NumSymbols = ftell(InputFile);
    rewind(InputFile);

    return NumSymbols;
}

//----------------------------------------------------------------------------------------------------------------------
//! Buffer\n
//! Here we just fill the Buffer.
//----------------------------------------------------------------------------------------------------------------------

char* Fill_the_Buffer(FILE* InputFile, unsigned int* NumStrings) {
    InputFile = fopen("InputFile.txt", "r");
    assert(InputFile != nullptr);

    unsigned int NumSymbols = Counter_of_Symbols(InputFile);
    if (NumSymbols <= 0) {
        printf("Something wrong with the InputFile.txt!\n");
        exit(0);
    }

    char* Buffer = (char*) calloc(NumSymbols + 1, sizeof(*Buffer));
    fread(Buffer, sizeof(*Buffer), NumSymbols, InputFile);
    fclose(InputFile);

    for (int i = 0; i < NumSymbols; i++)
        if (Buffer[i] == '\n') {
            (*NumStrings)++;
            Buffer[i] = '\0';
        }

    Buffer[NumSymbols] = EOF;
    return Buffer;
}


//----------------------------------------------------------------------------------------------------------------------
//! Addresses_of_Strings\n
//! In this function we looking for strings' addresses and put it in the Addresses_of_Strings.
//----------------------------------------------------------------------------------------------------------------------

char** Fill_the_Addresses(char* Buffer, unsigned int NumStrings) {
    char** Addresses_of_Strings = (char**) calloc(NumStrings + 1, sizeof(*Addresses_of_Strings));

    Addresses_of_Strings[0] = &Buffer[0];

    int i = 0, j = 0;
    while (Buffer[i] != EOF) {
        if (Buffer[i] == '\0')
            Addresses_of_Strings[++j] = &Buffer[i] + 1;
        i++;
    }

    Addresses_of_Strings[j] = nullptr;
    Buffer[i] = '\0';
    return Addresses_of_Strings;
}

//----------------------------------------------------------------------------------------------------------------------
//! Sort_the_Addresses\n
//! Here we sort our text.
//! Version 2.0
//! I implement quick sort, so it's working better.
//----------------------------------------------------------------------------------------------------------------------

void Sort_the_Addresses(char** Addresses_of_Strings, unsigned int NumStrings) {
    qsort(&Addresses_of_Strings[0], NumStrings, sizeof(*Addresses_of_Strings), Comparator);
}

//----------------------------------------------------------------------------------------------------------------------
//! Comparator\n
//! I use in Comparator standard function strcmp().
//! This is done for further improving the program and for rewriting this function into a more successful version.
//!
//! @param [str] string1 - first string for compare
//! @param [str] string2 - second string for compare
//----------------------------------------------------------------------------------------------------------------------

int Comparator(const void* string1, const void* string2) { //if string1 is less than string2, returns > 0
    return strcmp(*(char* const*) string1, *(char* const*) string2);
}

//----------------------------------------------------------------------------------------------------------------------
//! Filler_the_OutputFile\n
//! Simple function for putting sorted text into OutputFile.
//----------------------------------------------------------------------------------------------------------------------

void Fill_the_OutputFile(FILE* OutputFile, char** Addresses_of_Strings, unsigned int NumStrings) {
    OutputFile = fopen("OutputFile.txt", "w");
    assert(OutputFile != nullptr);

    for (int i = 0; i < NumStrings; i++) {
        if (strcmp(Addresses_of_Strings[i], "\0") != 0) {
            fputs(Addresses_of_Strings[i], OutputFile);
            fputc('\n', OutputFile);
        }
    }
}


