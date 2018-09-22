//! @file main.cpp
//----------------------------------------------------------------------------------------------------------------------
//! Version 3.0
//! This program creates the Encyclopedia of any Poem.
//! I want to add some things later, so will be in touch =)
//----------------------------------------------------------------------------------------------------------------------
//! @mainpage
//! - main.cpp

#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cstdlib>

void Sorter(FILE* InputFile, FILE* OutputFile);
unsigned int Counter_of_Symbols(FILE* InputFile, unsigned int* NumSymbols, unsigned int* NumStrings);
void Fill_the_Buffer(FILE* InputFile, char* Buffer, int NumSymbols);
void Fill_the_Addresses(char* Buffer, char** Addresses_of_Strings, int NumSymbols);
void Sort_the_Addresses(char** Addresses_of_Strings, unsigned int NumStrings);
int Comparator(const void* string1, const void* string2);
void Fill_the_OutputFile(FILE* OutputFile, char** Addresses_of_Strings, int NumStrings);

//----------------------------------------------------------------------------------------------------------------------
//! main function\n
//! In this function only two parameters, both of them - files.
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
//! Since the function only read from InputFile and write in OutputFile, its type is void.
//! In this variation, we have the buffer (Buffer) with all the text and an array with pointers (Addresses_of_Strings) to the beginning of the strings in this buffer.
//! Also we have here another functions, so read their descriptions below.
//! @param [num] NumSymbols - number of symbols in InputFile (used for Buffer)
//! @param [num] NumStrings - number of strings in InputFile (used for Addresses_of_Strings)
//! @param [arr] Buffer - buffer with the text
//! @param [arr] Addresses_of_Strings - here there are addresses of strings in buffer
//----------------------------------------------------------------------------------------------------------------------

void Sorter(FILE* InputFile, FILE* OutputFile) {
    InputFile = fopen("InputFile.txt", "r");
    assert(InputFile != nullptr);

    unsigned int NumSymbols = 0;
    unsigned int NumStrings = 0;
    if (Counter_of_Symbols(InputFile, &NumSymbols, &NumStrings) == 0) {
        printf("Something wrong!\n");
        exit(0);
    }

    char* Buffer = (char* ) calloc(NumSymbols, sizeof(*Buffer));
    Fill_the_Buffer(InputFile, Buffer, NumSymbols);
    fclose(InputFile);

    char** Addresses_of_Strings = (char**) calloc(NumStrings, sizeof(*Addresses_of_Strings));
    Fill_the_Addresses(Buffer, Addresses_of_Strings, NumSymbols);

    Sort_the_Addresses(Addresses_of_Strings, NumStrings);

    OutputFile = fopen("OutputFile.txt", "w");
    assert(OutputFile != nullptr);

    Fill_the_OutputFile(OutputFile, Addresses_of_Strings, NumStrings);
    free(Addresses_of_Strings);
    free(Buffer);
    fclose(OutputFile);

}

//----------------------------------------------------------------------------------------------------------------------
//! Counter_of_Symbols\n
//! Before we will create the Buffer, we need to know his size.
//! Also we count number of strings for Addresses_of_Strings.
//! Before we count the NumSymbols and the NumStrings, we can allocate memory for both of the arrays.
//! Here we check the count of characters and strings:
//! if everything is fine and their values are greater than 0, the function returns 1, else returns 0 and exit from program.
//----------------------------------------------------------------------------------------------------------------------

unsigned int Counter_of_Symbols(FILE* InputFile, unsigned int* NumSymbols, unsigned int* NumStrings) {
    int c = 0;
    while ((c = fgetc(InputFile)) != EOF) {
        (*NumSymbols)++;

        if (c == '\n' || c == '\0')
            (*NumStrings)++;
    }
    (*NumSymbols)++;
    (*NumStrings)++;

    fseek(InputFile, 0, SEEK_SET);
    return (*NumSymbols <= 0 || *NumStrings <= 0) ? 0 : 1;
}

//----------------------------------------------------------------------------------------------------------------------
//! Buffer\n
//! Here we just fill the Buffer.
//----------------------------------------------------------------------------------------------------------------------

void Fill_the_Buffer(FILE* InputFile, char* Buffer, int NumSymbols) {
    for (int i = 0; i < NumSymbols - 1; i++) {
        Buffer[i] = fgetc(InputFile);
    }
    Buffer[NumSymbols - 1] = '\0';
}

//----------------------------------------------------------------------------------------------------------------------
//! Addresses_of_Strings\n
//! In this function we looking for strings' addresses and put it in the Addresses_of_Strings
//----------------------------------------------------------------------------------------------------------------------

void Fill_the_Addresses(char* Buffer, char** Addresses_of_Strings, int NumSymbols) {
    int i = 0;
    int j = 0;
    Addresses_of_Strings[j] = &Buffer[0];

    for (i = 0; i < NumSymbols - 1; i++) {
        if (Buffer[i] == '\n') {
            Buffer[i] = '\0';
            Addresses_of_Strings[++j] = &Buffer[i] + 1;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
//! Sort_the_Addresses\n
//! Here the sort our text.
//! V2. I implement quick sort, so it's working better
//----------------------------------------------------------------------------------------------------------------------

void Sort_the_Addresses(char** Addresses_of_Strings, unsigned int NumStrings) {
    qsort(&Addresses_of_Strings[0], NumStrings, sizeof(*Addresses_of_Strings), Comparator);
}

//----------------------------------------------------------------------------------------------------------------------
//! Comparator\n
//! I use in Comparator standard function strcmp().
//! This is done for further improving the program and for rewriting this function into a more successful version.
//! @param [str] string1 - first string for compare
//! @param [str] string2 - second string for compare
//----------------------------------------------------------------------------------------------------------------------

int Comparator(const void* string1, const void* string2) { //if string1 is less than string2, returns >0
    return strcmp(*(char* const*) string1, *(char* const*) string2);
}

//----------------------------------------------------------------------------------------------------------------------
//! Filler_the_OutputFile\n
//! Simple function for putting sorted text into OutputFile
//----------------------------------------------------------------------------------------------------------------------

void Fill_the_OutputFile(FILE* OutputFile, char** Addresses_of_Strings, int NumStrings){
    for(int i = 0; i < NumStrings; i++) {
        if(strcmp(Addresses_of_Strings[i], "\0") != 0) {
            fputs(Addresses_of_Strings[i], OutputFile);
            fputc('\n', OutputFile);
        }
    }
}

