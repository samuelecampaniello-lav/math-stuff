/*******************************************************************************
*
* File money.c
*
* Stuff I'm curious about regarding finance
*
* Author: Samuele Campaniello
*
*******************************************************************************/

#define MONEY_C

#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "start.h"
#include "random.h"
#include "global.h"
#include "types.h"

// Generates random double numbers with given mean and standard deviation
double next_gauss(double mean, double stdv)
{
   double ud[2];
   double x1,x2,rho,y1,y2;  
    
      ranlxd(ud,2);
      x1=ud[0];
      x2=ud[1];

      rho=-2*log(1.0-x1);
      rho=sqrt(rho);
      x2*=2.0*PI;
      y1=rho*sin(x2);
      y2=rho*cos(x2);
      
      if (rand()%2==1)
      { return mean+y1*stdv; }
      else
      { return mean+y2*stdv; }
}


// Similar to the previous one, used for t-student below
double next_gauss_raw()
{
    double ud[2];
    ranlxd(ud, 2);
    double rho = sqrt(-2.0 * log(1.0 - ud[0]));
    double theta = 2.0 * PI * ud[1];
    return rho * sin(theta);
}


// t-student normalized of variance 1, with T_STUDENT_DOF degrees of freedom
double next_t_student()
{
    double z = next_gauss_raw();
    double chi2 = 0.0;
    for (int i = 0; i < T_STUDENT_DOF; i++) {
        double g = next_gauss_raw();
        chi2 += g * g;
    }
    return z / sqrt(chi2 / (double)T_STUDENT_DOF) * sqrt((T_STUDENT_DOF - 2.0) / (double)T_STUDENT_DOF);
}


// Garch stuff - to be understood
void garch_init(GarchState* g, double sigma2_long_run)
{
    g->alpha    = GARCH_A;
    g->beta     = GARCH_B;
    g->omega    = sigma2_long_run * (1.0 - GARCH_A - GARCH_B);
    g->sigma2   = sigma2_long_run;
    g->eps_prev = 0.0;
}
double garch_next_sigma(GarchState* g)
{
    g->sigma2 = g->omega
              + g->alpha * g->eps_prev * g->eps_prev
              + g->beta  * g->sigma2;
    return sqrt(g->sigma2);
}
void garch_update_eps(GarchState* g, double eps)
{
    g->eps_prev = eps;
}


// Generates next market day (ADVANCED)
double next_day(double today, double growth_y, GarchState* g)
{
    double mu_d = pow(1.0 + growth_y, 1.0 / 365.0) - 1.0;
    double sigma = garch_next_sigma(g);
    double eps   = sigma * next_t_student(T_STUDENT_DOF);
    garch_update_eps(g, eps);
    return today * (1.0 + mu_d + eps);
}


// Generates market time evolution (ADVANCED)
double* generate_market(int years, double growth_y, double volatility_y)
{
    int days = years*365;
    double* stock = (double*)malloc((days + 1) * sizeof(double));
    stock[0] = 1.0;

    double vol_d = volatility_y / sqrt(365.0);
    GarchState g;
    garch_init(&g, vol_d * vol_d);

    for (int i = 1; i <= days; i++)
    { stock[i] = next_day(stock[i-1], growth_y, &g); }

    return stock;
}

// Copies a market but with leverage
double* leverage_market(int years, double* source, double L)
{
    int days = years*365;
    double* stock = (double*)malloc((days + 1) * sizeof(double));
    stock[0] = 1.0;

    for(int i=1; i<=days; i++)
    { stock[i]=stock[i-1]*(1+L*(source[i]/source[i-1]-1.0)); }

    return stock;
}


// Generates next day's stock value (BASIC)
double next_day_blackscholes(double today, double growth_y, double volatility_y)
{
    double growth_d = pow(growth_y+1.0,1.0/(365.0))-1.0;
    double volatility_d = volatility_y/pow(365.0, 0.5);
    return today*(1+next_gauss(growth_d,volatility_d));
}


// Given a time length, an expected yearly growth and volatility, generates a random market evolution (BASIC)
double* generate_market_blackscholes (int years, double growth, double volatility)
{
    int days = years*365;
    double* stock = (double*)malloc(days*sizeof(double));
    stock[0]=1.0;   
    for (int i=1; i<=days; i++)
    {
        stock[i]=next_day_blackscholes( stock[i-1], growth, volatility );
    }
    return stock;
}


// Creates empty investment struct
investment* invest(int years) 
{
    investment* my_plan = malloc(sizeof(investment));
    if (my_plan == NULL) {
        perror("malloc failed");
        exit(1);
    }
    my_plan->years = years;
    my_plan->tot = 0.;
    my_plan->invested = 0.;
    my_plan->gain = 0.;
    my_plan->data = malloc(sizeof(double) * (365*years));
    if (my_plan->data == NULL) 
    {
        perror("malloc failed");
        free(my_plan);
        exit(1);
    }
    else 
    { 
        for (int i=0; i<365*my_plan->years; i++) 
        { my_plan->data[i] = 0.0; } 
    } 
    return my_plan;
}


// Empties investment struct
void clean_investment(investment* my_plan) 
{
    my_plan->tot = 0.;
    my_plan->invested = 0.;
    my_plan->gain = 0.;
    for (int i=0; i<365*my_plan->years; i++)
    { my_plan->data[i] = 0.0; }   
}


// Frees investment struct
void destroy_investment(investment* P) 
{
    free(P->data);
    free(P);
}

// Invest everything at once
void plan_PIC(double* market, investment* my_plan, double invested_once)
{
    my_plan->invested += invested_once;
    for (int i=0; i<365*my_plan->years; i++)
    { my_plan->data[i] += invested_once*market[i]; }
    my_plan->tot += invested_once*market[365*my_plan->years-1];
    my_plan->gain += my_plan->tot - my_plan->invested;
}

// Invest the same amount once every 30 days
void plan_PAC_DCA(double* market, investment* my_plan, double invested_monthly)
{
    double titles = 0.0;

    for(int i=0; i<365*my_plan->years; i++)
    {
        if (i%30==0) 
        {
            my_plan->invested += invested_monthly;
            titles += invested_monthly/market[i];
        }
        my_plan->data[i] += titles*market[i];
    }

    my_plan->tot += titles*market[365*my_plan->years-1];
    my_plan->gain += my_plan->tot - my_plan->invested;
}


// Invest once every 30 days according to pure value average
void plan_PAC_VA(double* market, investment* my_plan, double objective, double* excess)
{
    double titles = objective;
    my_plan->data[0]=objective;
    
    for(int i=1; i<365*my_plan->years; i++)
    {
        if (i%30==0) 
        {
            // Objective not reached - buy
            if (titles*market[i] <= titles*market[i-29]+objective)
            {
                my_plan->invested += titles*(market[i-29]-market[i])+objective;
                titles += (titles*(market[i-29]-market[i])+objective)/market[i];
            }
            
            // Objective passed - sell
            else
            {
                excess[0] += titles*(-market[i-29]+market[i])-objective;
                titles -= (titles*(-market[i-29]+market[i])-objective)/market[i];
            }
        }

        // Normal day
        my_plan->data[i] += titles*market[i];
    }

    my_plan->tot += titles*market[365*my_plan->years-1];
    my_plan->gain += my_plan->tot - my_plan->invested;
}


// Invest once every 30 days according to value average without ever selling
void plan_PAC_VANS(double* market, investment* my_plan, double objective)
{
    double titles = objective;
    my_plan->data[0]=objective;
    
    for(int i=1; i<365*my_plan->years; i++)
    {
        if (i%30==0) 
        {
            // Objective not reached - buy
            if (titles*market[i] <= titles*market[i-29]+objective)
            {
                my_plan->invested += titles*(market[i-29]-market[i])+objective;
                titles += (titles*(market[i-29]-market[i])+objective)/market[i];
            }
            // Objective passed - do nothing
        }

        // Normal day
        my_plan->data[i] += titles*market[i];
    }

    my_plan->tot += titles*market[365*my_plan->years-1];
    my_plan->gain += my_plan->tot - my_plan->invested;
}





