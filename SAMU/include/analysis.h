#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "types.h"

#ifndef ANALYSIS_C

// Functions
extern double       factorial(int n);
extern double       logfactorial(int n);
extern double       inverse(double x);

// Integrals
extern double       integral_simp8  (function_1D f, double a, double b);
extern double       integral_simp64 (function_1D f, double a, double b);
extern double       integral_simp512(function_1D f, double a, double b);

#endif

#endif
