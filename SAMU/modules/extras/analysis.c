/*******************************************************************************
*
* File analisys.c
*
* Useful linear analisys tools for stuff that's actually interesting
*
* Author: Samuele Campaniello
*
*******************************************************************************/

#define ALGEBRA_C

#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "start.h"
#include "random.h"
#include "global.h"
#include "types.h"

// Calculates the factorial of a natural number
double factorial(int n)
{
    if (n==0 || n==1){ return 1; }
    else 
    {
        int F=1;
        for (int i=2; i<=n; i++) { F*=i; }
        return F;
    }
}

// Calculates the log of the factorial of a natural number
double logfactorial(int n)
{
    if (n==0 || n==1){ return 0; }
    else 
    {
        double LF=0;
        for (int i=2; i<=n; i++) { LF+=log((double)i); }
        return LF;
    }
}

// Calculates the inverse of the argument
double inverse(double x) { return 1.0/x; }


// Integrate a 1D function with simpson's method, using 8 points
double integral_simp8(function_1D f, double a, double b)
{
    if (a>b)
    { 
        printf("Error: wrong order of extremes in integral \n");
        exit(1); 
    }    

    // Declare variables
    double h=(b-a)/8.0, S=0.0;

    // Sum evaluations
    for (int i=0; i<=8; i++)
    {
        if(i==0 || i==8) { S+= h/3*f(a+i*h); }
        else if(i%2) { S+= 4*h/3*f(a+i*h); }
        else { S+= 2*h/3*f(a+i*h); }
    }

    return S;

}

// Integrate a 1D function with simpson's method, using 64 points
double integral_simp64(function_1D f, double a, double b)
{
    if (a>b)
    { 
        printf("Error: wrong order of extremes in integral \n");
        exit(1); 
    }    

    // Declare variables
    double h=(b-a)/64.0, S=0.0;

    // Sum evaluations
    for (int i=0; i<=64; i++)
    {
        if(i==0 || i==64) { S+= h/3*f(a+i*h); }
        else if(i%2) { S+= 4*h/3*f(a+i*h); }
        else { S+= 2*h/3*f(a+i*h); }
    }

    return S;

}


// Integrate a 1D function with simpson's method, using 64 points
double integral_simp512(function_1D f, double a, double b)
{
    if (a>b)
    { 
        printf("Error: wrong order of extremes in integral \n");
        exit(1); 
    }    

    // Declare variables
    double h=(b-a)/512.0, S=0.0;

    // Sum evaluations
    for (int i=0; i<=512; i++)
    {
        if(i==0 || i==512) { S+= h/3*f(a+i*h); }
        else if(i%2) { S+= 4*h/3*f(a+i*h); }
        else { S+= 2*h/3*f(a+i*h); }
    }

    return S;

}




















