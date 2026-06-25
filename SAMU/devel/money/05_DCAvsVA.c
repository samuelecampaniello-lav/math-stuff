/*******************************************************************************
*
* File 05_DCAvsVA.c
*
* Creates a set of markets, makes a DCA and a VA pure, confronts them
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
    double DCA_monthly=100.0, VA_objective=100.0, growth_y=0.095, volatility_y=0.16;
    double DCAtot=0.0, DCAinv=0.0, VAtot=0.0, VAinv=0.0, VA_excess[1]={0.0};    
    double* Sp500;

    // Inizialize random and investment
    rlxd_init(1,1358);
    investment* Portfolio1 = invest(years);
    investment* Portfolio2 = invest(years);
    
    for(int i=0; i<N; i++) 
    {
        // Generate new market
        Sp500 = generate_market(years, growth_y, volatility_y);        

        // Simulate PIC and PAC
        plan_PAC_DCA(Sp500, Portfolio1, DCA_monthly);
        plan_PAC_VA(Sp500, Portfolio2, VA_objective, VA_excess);
    
        // Save the total
        DCAtot += Portfolio1->tot/N;      
        DCAinv += Portfolio1->invested/N;
        VAtot += Portfolio2->tot/N;  
        VAinv += Portfolio2->invested/N;

        // Clean the portfolio, free the market
        clean_investment(Portfolio1);
        clean_investment(Portfolio2);
        free(Sp500);
    }

    // Show results
    printf("Investimento DCA: %f \n", DCAinv);
    printf("Risultante DCA: %f \n", DCAtot);
    printf("Investimento VA: %f \n", VAinv);
    printf("Risultante VA: %f \n", VAtot);
    printf("Avanzo liquidità VA: %f \n \n", VA_excess[0]/N);
    printf("Crescita media annua DCA: %f%% \n", (pow(DCAtot/DCAinv, 1.0/years)-1)*100.0 );
    printf("Crescita media annua VA: %f%% \n", (pow((VAtot+VA_excess[0]/N) /VAinv, 1.0/years)-1)*100.0 );

    // Free mallocs
    destroy_investment(Portfolio1);
    destroy_investment(Portfolio2);
    free(Sp500);

    exit(0);

}
