/*******************************************************************************
*
* File 03_PICandPAC.c
*
* Combines the effects of a PIC and a PAC, then gives an average
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
    int years=25, N=1000;
    double begin=300.0 ,monthly=0.0, growth_y=0.1, volatility_y=0.15;
    double TOT=0.0, INV=0.0;    
    double* Sp500;

    // Inizialize random and investment
    rlxd_init(1,1358);
    investment* Portfolio = invest(years);
    
    for(int i=0; i<N; i++) 
    {
        // Generate new market
        Sp500 = generate_market(years, growth_y, volatility_y);        

        // Simulate PIC and PAC
        plan_PIC(Sp500, Portfolio, begin);
        plan_PAC_DCA(Sp500, Portfolio, monthly);
    
        // Save the total
        TOT += Portfolio->tot/N;

        // Clean the portfolio, free the market
        clean_investment(Portfolio);
        free(Sp500);
    }
    INV= years*12*monthly+begin;

    // Show results
    printf("Investimento combinato: %f \n", INV);
    printf("Risultante medio: %f \n", TOT);
    printf("Crescita media annua: %f% \n", (pow(TOT/INV, 1.0/years)-1)*100.0 );

    // Print a data file for GNUPLOT
    printer(Portfolio->data,years*365, "Example_PICPAC.txt");

    // Free mallocs
    destroy_investment(Portfolio);
    free(Sp500);

    exit(0);

}






