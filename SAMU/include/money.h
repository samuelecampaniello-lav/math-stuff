#ifndef MONEY_H
#define MONEY_H
#include "types.h"

#ifndef MONEY_C
// Basic market generation
extern double next_gauss(double mean, double stdv);
extern double next_day_blackscholes(double today, double growth_y, double volatility_y);
extern double* generate_market_blackscholes (int years, double growth, double volatility);

// Advanced market generation
extern double next_gauss_raw();
extern double next_t_student();
extern void garch_init(GarchState* g, double sigma2_long_run);
extern double garch_next_sigma(GarchState* g);
extern void garch_update_eps(GarchState* g, double eps);
extern double next_day(double today, double growth_y, GarchState* g);
extern double* generate_market(int years, double growth_y, double volatility_y);

// Leverage
extern double* leverage_market(int years, double* source, double L);

// Investment management
extern investment* invest(int years);
extern void clean_investment(investment* my_plan);
extern void destroy_investment(investment* P);

// Investment plans (allow combination)
extern void plan_PIC(double* market, investment* my_plan, double invested_once);
extern void plan_PAC_DCA(double* market, investment* my_plan, double invested_monthly);
extern void plan_PAC_VA(double* market, investment* my_plan, double objective, double* excess);
extern void plan_PAC_VANS(double* market, investment* my_plan, double objective);

#endif

#endif
