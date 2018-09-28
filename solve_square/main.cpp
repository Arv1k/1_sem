//! @file main.cpp
//---------------------------------------------------------------------------------
//! This program was create for solving the square equations: a*x^2 + b*x + c = 0.
//! Thanks for using =)
//---------------------------------------------------------------------------------
//! @mainpage
//! - main.cpp

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <cassert>
#include <ctype.h>

#define MEOW
#ifdef MEOW
#define PRINTF printf
#else
#define PRINTF
#endif

const int InfRoots = -1;

int SolveSquare (double a, double b, double c, double* x1, double* x2);

int Linear (double b, double c, double* x1);

int Quadratic (double a, double b, double c, double* x1, double* x2);

//-----------------------------------------------------------------------------------------------
//! In main function we have conditions because of number of roots can be different.
//! In fact, SolveSquare solves how many roots we have
//-----------------------------------------------------------------------------------------------

int main() {
    PRINTF("# This program solve square equations.\n");
    PRINTF("# Enter a, b and c coefficients:\n");

    double a = 0;
    double b = 0;
    double c = 0;
    int check = 0;
    if ((check = scanf("%lg %lg %lg", &a, &b, &c)) != 3) {
        PRINTF("# One of the coefficients is not a number!\n");
        exit(0);
    }


    double x1 = 0;
    double x2 = 0;
    int nRoots = SolveSquare(a, b, c, &x1, &x2); // nRoots - number of roots
    switch (nRoots) {

        case 0:
            PRINTF("# There aren't any roots!\n");
            break;

        case 1:
            PRINTF("# There is only one root:\n");
            printf("%lg\n", x1);
            break;

        case 2:
            PRINTF("# There are two different roots:\n");
            PRINTF("# First  ");
            printf("%lg\n", x1);
            PRINTF("# Second  ");
            printf("%lg\n", x2);
            break;

        case InfRoots:
            PRINTF("# There are an infinite number of roots!"); // InfRoots used when the equation has an infinite number of roots
            break;

        default:
            PRINTF("# ERROR_001! Something wrong with coefficients!\n");
    }
}

//-----------------------------------------------------------------------------------------------
//! SolveSquare - function for solving the equation
//! @param [in] a - coefficient.
//! @param [in] b - coefficient.
//! @param [in] c - coefficient.
//! @param [out] x1 - one of the root.
//! @param [out] x2 - one of the root.
//-----------------------------------------------------------------------------------------------

int SolveSquare (double a, double b, double c, double* x1, double* x2) {
    if (a == 0) return Linear(b, c, x1);
    else        return Quadratic(a, b, c, x1, x2);
}

//-----------------------------------------------------------------------------------------------
//! Linear - auxiliary function if a = 0 (b*x + c = 0)
//! @param [in] b - coefficient.
//! @param [in] c - coefficient.
//! @param [out] x1 - the root.
//-----------------------------------------------------------------------------------------------

int Linear (double b, double c, double* x1) {
    if (b == 0)
        return (c == 0) ? InfRoots : 0;
    else {
        *x1 = -c / b;
        return 1;
    }
}

//-----------------------------------------------------------------------------------------------
//! Quadratic - auxiliary function if a != 0 (a*x^2 + b*x + c = 0)
//! @param [in] a - coefficient.
//! @param [in] b - coefficient.
//! @param [in] c - coefficient.
//! @param [out] x1 - one of the root.
//! @param [out] x2 - one of the root.
//-----------------------------------------------------------------------------------------------

int Quadratic (double a, double b, double c, double* x1, double* x2) {
    double Dis = b * b - 4 * a * c;
    if (Dis >= 0) {
        double SqDis = sqrt(b * b - 4 * a * c);
        *x1 = (-b + SqDis) / (2 * a);
        *x2 = (-b - SqDis) / (2 * a);

        if (*x1 == *x2) return 1;
        else            return 2;
    } 
    else return 0;
}

