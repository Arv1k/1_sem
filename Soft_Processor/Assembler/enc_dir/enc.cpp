#include "enc.h"

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

str* Fill_the_Addresses(const char* nameInput) {
    PRINTF("# Entered in Fill_the_Addresses func\n");

    unsigned int NumStrings = 0;
    char* Buffer = Fill_the_Buffer(nameInput, &NumStrings);
    
    str* Addresses = (str*) calloc(NumStrings + 2, sizeof(*Addresses));

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

    Addresses[j].Length = &Buffer[i] - Addresses[j].String + 1;

    Addresses[NumStrings + 1].String = nullptr;
    Addresses[NumStrings + 1].Length = 0;

    PRINTF("# Exit from Fill_the_Addresses\n");

    return Addresses;
}

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

long int Size(FILE* InputFile) {

    PRINTF("# Entered in Size func\n");

    long Position = ftell(InputFile);

    fseek(InputFile, 0, SEEK_END);
    long int NumSymbols = ftell(InputFile);
    fseek(InputFile, Position, SEEK_SET);

    PRINTF("# Exit from Size\n");

    return NumSymbols;
}

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

void Sort_the_Addresses_from_the_end(str* Addresses) {

    PRINTF("# Entered in Sort_the_Addresses_from_the_end func\n");

    unsigned int NumStrings = 0;
    while (Addresses[NumStrings].String != nullptr) NumStrings++;

    qsort(&Addresses[0], NumStrings, sizeof(*Addresses), Comparator);

    PRINTF("# Exit from Sort_the_Addresses_from_the_end\n");
}

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
