/*******************************************************************************
*
* File 04_Leverage.c
*
* Creates a set of leveraged markets, calculates the average total
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
    int years=15, N=10000, LMAX=100;
    double growth_y=0.95, volatility_y=0.16; 
    double lev_tot[LMAX], lev_yearly[LMAX];     
    double* Sp500;
    double* Leveraged;

    // Inizialize random and vectors
    rlxd_init(1,1358);
    for(int i=0; i<LMAX; i++) { lev_tot[i]=0.0; lev_yearly[i]=0.0; }

    // Leverage simulations
    for(int i=0; i<N; i++) 
    {
        // Generate new market
        Sp500 = generate_market(years, growth_y, volatility_y);      

        // Calculate leveraged result
        for (double j=1; j<=LMAX; j++)
        {
            Leveraged = leverage_market(years, Sp500, j/10.0);
            lev_tot[(int)j-1] += Leveraged[years*365-1]/N;
            free(Leveraged);
        }
        
        // Free the market
        free(Sp500);
    }

    // Calculate the yearly growth
    for(int i=0; i<LMAX; i++) { lev_yearly[i]= pow(lev_tot[i], 1.0/years)-1; }

    // Print the results
    printer(lev_yearly, LMAX, "Leverage_yearly.txt");

    exit(0);

}






