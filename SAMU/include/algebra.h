#ifndef ALGEBRA_H
#define ALGEBRA_H
#include "types.h"

#ifndef ALGEBRA_C

// Vectors
extern vector*      vector_init     (int L);
extern void         vector_free     (vector* V);

extern void         vector_scale    (double k, vector* A);
extern vector*      vector_scale1   (double k, vector* A);
extern void         vector_scale2   (double k, vector* A, vector* B);
extern void         vector_nrmlize  (vector* A);
extern vector*      vector_nrmlize1 (vector* A);
extern void         vector_nrmlize2 (vector* A, vector B);

extern double       vector_norm     (vector* V);


// Matrices
extern matrix*      matrix_init     (int R, int C);
extern void         matrix_write    (matrix* M, int R, int C, double value);
extern double       matrix_read     (matrix* M, int R, int C);
extern void         matrix_free     (matrix* M);
extern matrix*      matrix_id       (int N);

extern void         matrix_scale    (double k, matrix* A);
extern matrix*      matrix_scale1   (double k, matrix* A);
extern void         matrix_scale2   (double k, matrix* A, matrix* B);
extern void         matrix_transp   (matrix* M);
extern matrix*      matrix_transp1  (matrix* M);
extern void         matrix_transp2  (matrix* M, matrix* MT);

extern vector*      matrix_row1     (matrix* M, int row_n);
extern void         matrix_row2     (matrix* M, int row_n, vector* V);
extern vector*      matrix_col1     (matrix* M, int col_n);
extern void         matrix_col2     (matrix* M, int col_n, vector* V);

extern double       matrix_det      (matrix* M);
extern double       matrix_tr       (matrix* M);


// V-V functions
extern vector*      vecvec_sum1     (vector* A, vector* B);
extern void         vecvec_sum2     (vector* A, vector* B, vector*C);
extern vector*      vecvec_diff1    (vector* A, vector* B);
extern void         vecvec_diff2    (vector* A, vector* B, vector*C);

extern double       vecvec_scalprod (vector* A, vector* B);


// M-V functions
extern vector*      matvec_prod1    (matrix* M, vector* V);
extern void         matvec_prod2    (matrix* M, vector* V, vector* W);

extern vector*      vecmat_prod1    (vector* V, matrix* M);
extern void         vecmat_prod2    (vector* V, matrix* M, vector* W);


// M-M functions
extern matrix*      matmat_sum1     (matrix* A, matrix* B);
extern void         matmat_sum2     (matrix* A, matrix* B, matrix*C);
extern matrix*      matmat_diff1    (matrix* A, matrix* B);
extern void         matmat_diff2    (matrix* A, matrix* B, matrix*C);
extern matrix*      matmat_prod1    (matrix* A, matrix* B);
extern void         matmat_prod2    (matrix* A, matrix* B, matrix* C);


// Vectors sets
extern vecset*      vecset_init     (int S, int L);
extern void         vecset_free     (vecset* VS);
extern vecset*      vecset_canonic  (int N);


#endif

#endif
