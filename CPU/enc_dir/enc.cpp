#include "enc.h"

//----------------------------------------------------------------------------------------------------------------------
//! Sorter\n\n
//! In this variation, we have the buffer (Buffer) with all the text and an array with pointers (Addresses_of_Strings)
//! to the beginning of the strings in this buffer.
//! Also we have here another functions, so read their descriptions below.
//! Also there is CP_Addresses_of_Strings - copy of the 0 element in the Addresses_of_Strings. We need it because we
//! must clean the memory allocated for Buffer. His location is in another function, but Addresses_of_Strings[0] is 
//! his first element's address, so that's why we save it.
//!
//! @param [arr] Addresses_of_Strings - here there are addresses of strings in buffer
//! @param [arr] CP_Addresses_of_Strings - Buffer's address
//----------------------------------------------------------------------------------------------------------------------

void Sorter(const char* nameInput, const char* nameOutput) {
    str* Addresses = Fill_the_Addresses(nameInput);

    char* CP_Addresses_of_Strings = Addresses[0].String;

    Fill_the_OutputFile(Addresses, nameOutput);

    Sort_the_Addresses_from_the_end(Addresses);
    Fill_the_OutputFile(Addresses, nameOutput);

    Sort_the_Addresses(Addresses);
    Fill_the_OutputFile(Addresses, nameOutput);

    cleanMemory(Addresses, &CP_Addresses_of_Strings);
}

//----------------------------------------------------------------------------------------------------------------------
//! Addresses_of_Strings\n\n
//! In this function we looking for strings' addresses and put it in the Addresses_of_Strings.
//! In the end of Addresses_of_Strings need to be nullptr, because Sorter don't know its size.
//----------------------------------------------------------------------------------------------------------------------

str* Fill_the_Addresses(const char* nameInput) {
    PRINTF("# Entered in Fill_the_Addresses func\n");

    unsigned int NumStrings = 0;
    char* Buffer = Fill_the_Buffer(nameInput, &NumStrings);

    str* Addresses = (str*) calloc(NumStrings + 1, sizeof(*Addresses));

    PRINTF("%p second calloc\n", &Addresses[0]);

    int i = 0, j = 0;
    Addresses[j].String = &Buffer[i];

    while (Buffer[i] != '\0') {
        if (Buffer[i] == '\n') {
            Buffer[i] = '\0';
            Addresses[++j].String = &Buffer[i + 1];
            Addresses[j - 1].Length = Addresses[j].String - Addresses[j - 1].String;
        }
        i++;
    }
    Addresses[j].Length = &Buffer[i] - Addresses[j - 1].String + 1;

    Addresses[NumStrings].String = nullptr;

    PRINTF("# Exit from Fill_the_Addresses\n");

    return Addresses;
}

//----------------------------------------------------------------------------------------------------------------------
//! Buffer\n\n
//! Here we just fill the Buffer.
//! Very imortant to put '\0' in the end of Buffer for working with it.
//----------------------------------------------------------------------------------------------------------------------

char* Fill_the_Buffer(const char* nameInput, unsigned int* NumStrings) {

    PRINTF("# Entered in Fill_the_Buffer func\n");

    FILE* InputFile = fopen(nameInput, "r");
    if (InputFile == nullptr) {
        printf("InputFile is not declared in this scope!");
        return nullptr;
    }

    unsigned int NumSymbols = Size(InputFile);

    char* Buffer = (char*) calloc(NumSymbols + 1, sizeof(*Buffer));
    fread(Buffer, sizeof(*Buffer), NumSymbols, InputFile);
    fclose(InputFile);

    PRINTF("%p, first calloc\n", &Buffer[0]);

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

    long Position = ftell(InputFile);

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

void Sort_the_Addresses(str* Addresses) {

    PRINTF("# Entered in Sort_the_Addresses func\n");

    unsigned int NumStrings = 0;
    while (Addresses[NumStrings].String != nullptr) NumStrings++;

    int (*meow)(const void *a, const void *b) = [](const void *string1, const void *string2) {
        return strcmp((*(str const *) string1).String, (*(str const *) string2).String);
    };

    qsort(&Addresses[0], NumStrings, sizeof(*Addresses), meow);

    PRINTF("# Exit from Sort_the_Addresses\n");
}

//----------------------------------------------------------------------------------------------------------------------
//! Sort_the_Addresses_from_the_end\n\n
//! Here we sort our text from the end of words.
//! So we will find the rhymes.
//----------------------------------------------------------------------------------------------------------------------

void Sort_the_Addresses_from_the_end(str* Addresses) {

    PRINTF("# Entered in Sort_the_Addresses_from_the_end func\n");

    unsigned int NumStrings = 0;
    while (Addresses[NumStrings].String != nullptr) NumStrings++;

    qsort(&Addresses[0], NumStrings, sizeof(*Addresses), Comparator);

    PRINTF("# Exit from Sort_the_Addresses_from_the_end\n");
}

//----------------------------------------------------------------------------------------------------------------------
//! Comparator\n\n
//! Comparator compare strings from their ends.
//!
//! @param [str] string1 - first string for compare
//! @param [str] string2 - second string for compare
//----------------------------------------------------------------------------------------------------------------------

int Comparator(const void* string1, const void* string2) { //if string1 is less than string2, returns > 0
    str str1 = *(str const*) string1;
    str str2 = *(str const*) string2;

    if (str1.Length > str2.Length) {
        for (long int i = (str2.Length - 1); i > 0; i--) {
            if (str2.String[i] == str1.String[i + str1.Length - str2.Length])     continue;
            else if (str2.String[i] < str1.String[i + str1.Length - str2.Length]) return 1;
            else                                                                  return -1;
        }
        return 1;
    }

    else {
        for (long int i = (str1.Length - 1); i > 0; i--) {
            if (str1.String[i] == str2.String[i + str2.Length - str1.Length])     continue;
            else if (str1.String[i] < str2.String[i + str2.Length - str1.Length]) return -1;
            else                                                                  return 1;
        }
        if (str1.Length == str2.Length) return 0;
        else                            return -1;
    }
}

//----------------------------------------------------------------------------------------------------------------------
//! Filler_the_OutputFile\n\n
//! Simple function for putting sorted text into OutputFile.
//----------------------------------------------------------------------------------------------------------------------


void Fill_the_OutputFile(str* Addresses, const char* nameOutput) {

    PRINTF("# Entered in Fill_the_OutputFile func\n");

    FILE* OutputFile = fopen(nameOutput, "a+");
    if (OutputFile == nullptr) {
        printf("OutputFile is not declared in this scope!");
        exit(0);
    }

    int i = 0;
    while (Addresses[i].String != nullptr) {
        if (*(Addresses[i].String) != '\0') {
            fputs(Addresses[i].String, OutputFile);
            fputc('\n', OutputFile);
        }
        i++;
    }
    fprintf(OutputFile, "\n\n\n\n");

    PRINTF("# Exit from Fill_the_OutputFile\n");
}

//----------------------------------------------------------------------------------------------------------------------
//! cleanMemory\n\n
//! Mini-function to clear memory.
//----------------------------------------------------------------------------------------------------------------------

void cleanMemory(str* Addresses, char** CP_Addresses_of_Strings) {

    PRINTF("# Entered in cleanMemory function\n");

    //memset(Addresses_of_Strings, 0, func);
    //memset(CP_Addresses_of_Strings, 0, func);

    PRINTF("first calloc %p cleaned\n", CP_Addresses_of_Strings[0]);

    free(CP_Addresses_of_Strings[0]);

    PRINTF("second calloc %p cleaned\n", Addresses);

    free(Addresses);

    PRINTF("# Exit from cleanMemory\n");
}
