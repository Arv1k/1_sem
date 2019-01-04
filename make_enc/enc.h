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

void Sorter(const char* nameInput, const char* nameOutput);

//----------------------------------------------------------------------------------------------------------------------
//! Addresses_of_Strings\n\n
//! In this function we looking for strings' addresses and put it in the Addresses_of_Strings.
//! In the end of Addresses_of_Strings need to be nullptr, because Sorter don't know its size.
//----------------------------------------------------------------------------------------------------------------------

str* Fill_the_Addresses(const char* nameInput);

//----------------------------------------------------------------------------------------------------------------------
//! Buffer\n\n
//! Here we just fill the Buffer.
//! Very imortant to put '\0' in the end of Buffer for working with it.
//----------------------------------------------------------------------------------------------------------------------

char* Fill_the_Buffer(const char* nameInput, unsigned int* NumStrings = nullptr);

//----------------------------------------------------------------------------------------------------------------------
//! Size\n\n
//! Before we will create the Buffer, we need to know his size.
//! Buffer size - file size.
//----------------------------------------------------------------------------------------------------------------------

long int Size(FILE* InputFile);

//----------------------------------------------------------------------------------------------------------------------
//! numberSymbol\n\n
//! Mini-function for counting any symbol in the text.
//----------------------------------------------------------------------------------------------------------------------

unsigned int numberSymbol(const char* Buffer, char Symbol);

//----------------------------------------------------------------------------------------------------------------------
//! Sort_the_Addresses\n\n
//! Here we sort our text.
//! Version 2.0
//! I implement quick sort, so it's working better.
//----------------------------------------------------------------------------------------------------------------------

void Sort_the_Addresses(str* Addresses);

//----------------------------------------------------------------------------------------------------------------------
//! Sort_the_Addresses_from_the_end\n\n
//! Here we sort our text from the end of words.
//! So we will find the rhymes.
//----------------------------------------------------------------------------------------------------------------------

void Sort_the_Addresses_from_the_end(str* Addresses);

//----------------------------------------------------------------------------------------------------------------------
//! Comparator\n\n
//! Comparator compare strings from their ends.
//!
//! @param [str] string1 - first string for compare
//! @param [str] string2 - second string for compare
//----------------------------------------------------------------------------------------------------------------------

int Comparator(const void* string1, const void* string2);

//----------------------------------------------------------------------------------------------------------------------
//! Filler_the_OutputFile\n\n
//! Simple function for putting sorted text into OutputFile.
//----------------------------------------------------------------------------------------------------------------------

void Fill_the_OutputFile(str* Addresses, const char* nameOutput);

//----------------------------------------------------------------------------------------------------------------------
//! cleanMemory\n\n
//! Mini-function to clear memory.
//----------------------------------------------------------------------------------------------------------------------

void cleanMemory(str* Addresses, char** CP_Addresses_of_Strings);


#endif //ENC_ENC_H
