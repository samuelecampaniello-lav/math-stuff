/*******************************************************************************
*
* File types.h
*
* Type definitions and macros for complex numbers
*
* Author: Leonardo Giusti, Samuele Campaniello
*
*******************************************************************************/

#include <stdbool.h>
#ifndef TYPES_H
#define TYPES_H

// 1D functions for analisys
typedef double (*function_1D)(double);

// 1D successions for analysis
typedef double (*succession_1D) (int);

/******************************/

// Algebraic vector
typedef struct {
    int length;
    bool transposed;
    double *data;  
} vector;

// Algebraic matrix
typedef struct {
    int rows;
    int columns;
    double *data;  
} matrix;

// Vector set
typedef struct {
    int number;
    int length;
    bool transposed;
    vector** element;
}vecset;


/******************************/

// Garch state regarding self correlation of stdev
typedef struct 
{
    double omega;
    double alpha;
    double beta;
    double sigma2;
    double eps_prev;
} GarchState;

// Investment plan space
typedef struct
{
    int years;
    double invested, tot, gain;
    double *data;
} investment;

/******************************/

typedef struct
{
   float re,im;
} complex;

typedef struct
{
   double re,im;
} complex_dble;

/*
* a=b*c (a,b,c complex)
*/

#define _complex_mul(a,b,c) \
   (a).re=((b).re*(c).re-(b).im*(c).im); \
   (a).im=((b).re*(c).im+(b).im*(c).re)


/*
* a=b+c (a,b,c complex)
*/

#define _complex_add(a,b,c) \
   (a).re=((b).re+(c).re); \
   (a).im=((b).im+(c).im)


/*
* a=b-c (a,b,c complex)
*/

#define _complex_sub(a,b,c) \
   (a).re=((b).re-(c).re); \
   (a).im=((b).im-(c).im)


/*
* a=b/c (a,b,c complex)
*/

#define _complex_div(a,b,c) \
   (a).re=(((b).re*(c).re+(b).im*(c).im)/((c).re*(c).re+(c).im*(c).im)); \
   (a).im=(((b).im*(c).re-(b).re*(c).im)/((c).re*(c).re+(c).im*(c).im))


#endif





