/*******************************************************************************
*
* File 01_GenerateMarket.c
*
* Tests the generate_market function, prints the result on a .txt
*
* Author: Samuele Campaniello
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "random.h"
#include "global.h"
#include "money.h"
#include "types.h"

int main () 
{
    // Declare variables
    int years=25;
    
    // Initialize random numbers
    rlxd_init(1,1358);
    
    // Generate market base
    double* Sp500 = generate_market(years, 0.1, 0.15);

    // Show index evolution
    printf("Valore iniziale: %f \n", Sp500[0]);
    printf("Valore finale: %f \n", Sp500[365*years-1]);

    // Print data file for GNUPLOT
    printer(Sp500,365*years, "Market.txt");

    // Free mallocs
    free(Sp500);

    exit(0);
}

