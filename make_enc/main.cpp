//! @file main.cpp
//----------------------------------------------------------------------------------------------------------------------
//! This program creates the Encyclopedia of any Poem.
//!
//! Thanks to Vlad Aleinik and Ilya Dedinskiy for the great help!
//----------------------------------------------------------------------------------------------------------------------
//! @mainpage
//! - main.cpp

#include "enc.h"

//----------------------------------------------------------------------------------------------------------------------
//! main\n\n
//! Maine gets files' names and starts working if all was correct.
//----------------------------------------------------------------------------------------------------------------------

int main(int argc, const char* argv[]) {
    if ((argc > 2) && (argc < 4)) Sorter(argv[1], argv[2]);
    else                          printf("Wrong names of files!\n");
}



