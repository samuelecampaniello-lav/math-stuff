/*******************************************************************************
*
* File global.h
*
* Global parameters and arrays
*
*******************************************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#define PI 3.141592653589793
#define GARCH_A 0.08
#define GARCH_B 0.88
#define T_STUDENT_DOF 5

#if defined MAIN_PROGRAM
  #define EXTERN
#else
  #define EXTERN extern
#endif

EXTERN double xx[100];

#undef EXTERN

#endif

