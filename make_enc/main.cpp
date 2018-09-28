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

#define Meow
#ifdef Meow
#define PRINTF printf
#else
#define PRINTF
#endif

void Sorter(const char* nameInput, const char* nameOutput);

char** Fill_the_Addresses(const char* nameInput);

char* Fill_the_Buffer(const char* nameInput, unsigned int* NumStrings);

long int Size(FILE* InputFile);

unsigned int numberSymbol(const char* Buffer, char Symbol);

void Sort_the_Addresses(char** Addresses_of_Strings);

void Sort_the_Addresses_from_the_end(char** Addresses_of_Strings);

int Comparator(const void* string1, const void* string2);

void Fill_the_OutputFile(char** Addresses_of_Strings, const char* nameOutput);

void cleanMemory(char** Addresses_of_Strings, char** CP_Addresses_of_Strings);

//----------------------------------------------------------------------------------------------------------------------
//! main\n\n
//! Maine gets file names and starts working if all was correctly.
//----------------------------------------------------------------------------------------------------------------------

int main(int argc, const char* argv[]) {
    if ((argc > 2) && (argc < 4))  Sorter(argv[1], argv[2]);
    else                           printf("Wrong names of files!\n");
}

//----------------------------------------------------------------------------------------------------------------------
//! Sorter\n\n
//! Since the function only read from InputFile and write in OutputFile, its type is void.\n
//! In this variation, we have the buffer (Buffer) with all the text and an array with pointers (Addresses_of_Strings) to the beginning of the strings in this buffer.
//! Also we have here another functions, so read their descriptions below.
//!
//! @param [num] NumStrings - number of strings in InputFile (used for Addresses_of_Strings)
//! @param [arr] Buffer - buffer with the text
//! @param [arr] Addresses_of_Strings - here there are addresses of strings in buffer
//----------------------------------------------------------------------------------------------------------------------

void Sorter(const char* nameInput, const char* nameOutput) {
    char** Addresses_of_Strings = Fill_the_Addresses(nameInput);

    char** CP_Addresses_of_Strings = Addresses_of_Strings;

    Sort_the_Addresses_from_the_end(Addresses_of_Strings);
    Fill_the_OutputFile(Addresses_of_Strings, nameOutput);

    Sort_the_Addresses(Addresses_of_Strings);
    Fill_the_OutputFile(Addresses_of_Strings, nameOutput);

    //Fill_the_OutputFile(CP_Addresses_of_Strings, nameOutput);

    cleanMemory(Addresses_of_Strings, CP_Addresses_of_Strings);
}

//----------------------------------------------------------------------------------------------------------------------
//! Addresses_of_Strings\n\n
//! In this function we looking for strings' addresses and put it in the Addresses_of_Strings.
//----------------------------------------------------------------------------------------------------------------------

char** Fill_the_Addresses(const char* nameInput) {
    PRINTF("# Entered in Fill_the_Addresses func\n");

    unsigned int NumStrings = 0;
    char* Buffer = Fill_the_Buffer(nameInput, &NumStrings);
    
    char** Addresses_of_Strings = (char**) calloc(NumStrings + 1, sizeof(*Addresses_of_Strings));

    int i = 0, j = 0;
    Addresses_of_Strings[j] = &Buffer[i];

    while (Buffer[i] != '\0') {
        if (Buffer[i] == '\n') {
	    Buffer[i] = '\0';	
            Addresses_of_Strings[++j] = &Buffer[i + 1];
	}
        i++;
    }

    Addresses_of_Strings[j] = nullptr;

    PRINTF("# Exit from Fill_the_Addresses\n");

    return Addresses_of_Strings;
}

//----------------------------------------------------------------------------------------------------------------------
//! Buffer\n\n
//! Here we just fill the Buffer.
//----------------------------------------------------------------------------------------------------------------------

char* Fill_the_Buffer(const char* nameInput, unsigned int* NumStrings) {

    PRINTF("# Entered in Fill_the_Buffer func\n");

    FILE* InputFile = fopen(nameInput, "r");
    if (InputFile == nullptr){
        printf("InputFile is not declared in this scope!");
        exit(0);
    }

    unsigned int NumSymbols = Size(InputFile);

    char* Buffer = (char*) calloc(NumSymbols + 1, sizeof(*Buffer));
    fread(Buffer, sizeof(*Buffer), NumSymbols, InputFile);
    fclose(InputFile);

    Buffer[NumSymbols] = '\0';

    *NumStrings = numberSymbol(Buffer, '\n');

    PRINTF("# Exit from Fill_the_Buffer\n");

    return Buffer;
}

//----------------------------------------------------------------------------------------------------------------------
//! Size\n\n
//! Before we will create the Buffer, we need to know his size.
//! Buffer size - file size.
//----------------------------------------------------------------------------------------------------------------------

long int Size(FILE* InputFile) {

    PRINTF("# Entered in Size func\n");

    long Position = ftell (InputFile);

    fseek(InputFile, 0, SEEK_END);
    long int NumSymbols = ftell(InputFile);
    fseek(InputFile, Position, SEEK_SET);

    PRINTF("# Exit from Size\n");

    return NumSymbols;
}

//----------------------------------------------------------------------------------------------------------------------
//! numberSymbol\n\n
//! Mini-function for counting any symbol in the text.
//----------------------------------------------------------------------------------------------------------------------

unsigned int numberSymbol(const char* Buffer, char Symbol) {

    PRINTF("# Entered in numberSymbol func\n");

    unsigned int number_of_symbol = 0;

    int i = 0;
    while (Buffer[i] != '\0') {
        if (Buffer[i] == Symbol) {
            number_of_symbol++;
        }
        i++;
    }

    PRINTF("# Exit from numberSymbol\n");

    return number_of_symbol;
}

//----------------------------------------------------------------------------------------------------------------------
//! Sort_the_Addresses\n\n
//! Here we sort our text.
//! Version 2.0
//! I implement quick sort, so it's working better.
//----------------------------------------------------------------------------------------------------------------------

void Sort_the_Addresses(char** Addresses_of_Strings) {

    PRINTF("# Entered in Sort_the_Addresses func\n");

    unsigned int NumStrings = 0;
    while (Addresses_of_Strings[NumStrings] != nullptr) NumStrings++;

    qsort(&Addresses_of_Strings[0], NumStrings, sizeof(*Addresses_of_Strings), /*Comparator*/[] (const void* string1, const void* string2) {
                                                                                                    return strcmp(*(char* const*) string1, *(char* const*) string2);
                                                                                                });

    PRINTF("# Exit from Sort_the_Addresses\n");
}

//----------------------------------------------------------------------------------------------------------------------
//!
//----------------------------------------------------------------------------------------------------------------------

void Sort_the_Addresses_from_the_end(char** Addresses_of_Strings) {

    PRINTF("# Entered in Sort_the_Addresses_from_the_end func\n");

    unsigned int NumStrings = 0;
    while (Addresses_of_Strings[NumStrings] != nullptr) NumStrings++;

    qsort(&Addresses_of_Strings[0], NumStrings, sizeof(*Addresses_of_Strings), Comparator);

    PRINTF("# Exit from Sort_the_Addresses_from_the_end\n");
}

//----------------------------------------------------------------------------------------------------------------------
//! Comparator\n\n
//! I use in Comparator standard function strcmp().
//! This is done for further improving the program and for rewriting this function into a more successful version.
//!
//! @param [str] string1 - first string for compare
//! @param [str] string2 - second string for compare
//----------------------------------------------------------------------------------------------------------------------

int Comparator(const void* string1, const void* string2) { //if string1 is less than string2, returns > 0
    long int len1 = strlen(*(char* const*) string1);
    long int len2 = strlen(*(char* const*) string2);

    if (len1 > len2) {
        for(long int i = (len2 - 1); i > 0; i--) {
            if ((*(char* const*) string2)[i] == (*(char* const*) string1)[i + len1 - len2])     continue;
            else if ((*(char* const*) string2)[i] < (*(char* const*) string1)[i + len1 - len2]) return 1;
            else                                                                                return -1;
        }
        return 1;
    }

    else {
        for(long int i = (len1 - 1); i > 0; i--) {
            if ((*(char* const*) string1)[i] == (*(char* const*) string2)[i + len2 - len1])     continue;
            else if ((*(char* const*) string1)[i] < (*(char* const*) string2)[i + len2 - len1]) return -1;
            else                                                                                return 1;
        }
        if (len1 == len2) return 0;
        else              return -1;
    }
}

//----------------------------------------------------------------------------------------------------------------------
//! Filler_the_OutputFile\n\n
//! Simple function for putting sorted text into OutputFile.
//----------------------------------------------------------------------------------------------------------------------


void Fill_the_OutputFile(char** Addresses_of_Strings, const char* nameOutput) {

    PRINTF("# Entered in Fill_the_OutputFile func\n");

    FILE* OutputFile = fopen(nameOutput, "a+");
    if (OutputFile == nullptr){
        printf("OutputFile is not declared in this scope!");
        exit(0);
    }

    int i = 0;
    while(Addresses_of_Strings[i] != nullptr) {
        if (*Addresses_of_Strings[i] != '\0') {
            fputs(Addresses_of_Strings[i], OutputFile);
            fputc('\n', OutputFile);
        }
	    i++;
    }
    fprintf(OutputFile, "\n\n\n\n");

    PRINTF("# Exit from Fill_the_OutputFile\n");
}

//----------------------------------------------------------------------------------------------------------------------
//! cleanMemory\n\n
//! Mini-function for function to clear memory.
//----------------------------------------------------------------------------------------------------------------------

void cleanMemory(char** Addresses_of_Strings, char** CP_Addresses_of_Strings) {

    PRINTF("# Entered in cleanMemory function\n");

    //memset(Addresses_of_Strings, 0, func);
    //memset(CP_Addresses_of_Strings, 0, func);

    free(Addresses_of_Strings);
    free(CP_Addresses_of_Strings);

    PRINTF("# Exit from cleanMemory\n");
}


