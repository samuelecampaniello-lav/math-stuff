/*******************************************************************************
*
* File 02_TryPIC.c
*
* Tests the plan_PIC function, prints the result on a .txt
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
    double invested = 100.0, growth_y=0.1, volatility_y=0.15;
    
    // Inizialize random, market and plan
    rlxd_init(1,1358);
    double* Sp500 = generate_market(years, growth_y, volatility_y);
    investment* Portfolio = invest(years);
    
    // Simulate PIC
    plan_PIC(Sp500, Portfolio, invested);

    // Show results
    printf("Indice iniziale: %f \n", Sp500[0]);
    printf("Indice finale: %f \n", Sp500[365*years-1]);
    printf("Investimento iniziale: %f \n", Portfolio->data[0]);
    printf("Portafogli finale: %f \n", Portfolio->tot);

    // Print a data file for GNUPLOT
    printer(Portfolio->data,years*365, "PIC.txt");

    // Free mallocs
    destroy_investment(Portfolio);
    free(Sp500);

    exit(0);

}

