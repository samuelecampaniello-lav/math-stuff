/*******************************************************************************
*
* File 01_CubeDiagonal.c
*
* Estimate of ln(2) with simpson integral, varying in precision
*
* Author: Samuele Campaniello
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "random.h"
#include "global.h"
#include "money.h"
#include "algebra.h"
#include "types.h"
#include "start.h"

int main () 
{

    printf("Integrale tra 1 e 2 di 1/x \n");
    printf("Precisione standard = %.5f \n", integral_simp8  (inverse, 1.0 ,2.0) );
    printf("Più preciso         = %.8f \n", integral_simp64 (inverse, 1.0 ,2.0) );
    printf("Molto più preciso   = %.12f \n",integral_simp512(inverse, 1.0 ,2.0) );

    exit(0);

}
