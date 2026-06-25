/*******************************************************************************
*
* File algebra.c
*
* Useful linear algebra tools for stuff that's actually interesting
*
* Author: Samuele Campaniello
*
*******************************************************************************/

#define ALGEBRA_C

#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "start.h"
#include "random.h"
#include "global.h"
#include "types.h"


// Initialize a vector given its length
vector* vector_init(int L)
{
    vector* V = malloc(sizeof(vector));
    V->length = L;
    V->transposed = false;
    V->data = malloc(sizeof(double)*L);
    for (int i=0; i<L; i++) 
        { V->data[i] = 0.0; }
    return V;
}


// Free allocated memory
void vector_free (vector* V) { free(V->data); free(V); return; }


// Gives the norm of a vector
double vector_norm (vector* V)
{
    double module=0.0;
    for( int i=0;i<V->length;i++ ) { module+=V->data[i]*V->data[i]; }
    return pow( module,0.5 );
}


// Sums two vectors (unless lengths differ) in new vector variable
vector* vecvec_sum1(vector* A, vector* B)
{
    if (A->length != B->length) 
    { 
        printf("Error: sum of vectors with different length \n");
        exit(1); 
    }
    else if (A->transposed != B->transposed) 
    { 
        printf("Error: sum of vectors row & column \n");
        exit(1); 
    }
    else
    {
        vector* C = vector_init(A->length);
        for(int i=0; i<A->length; i++)
        { C->data[i] = A->data[i]+B->data[i]; }
        if (A->transposed) { C->transposed = true; }
        return C;
    }
}


// Sums two vectors (unless lengths differ) in already initialized vector variable
void vecvec_sum2(vector* A, vector* B, vector*C)
{
    if (A->length != B->length || A->length != C->length) 
    { 
        printf("Error: sum of vectors with different length \n");
        exit(1); 
    }
    else if (A->transposed != B->transposed || A->transposed != C->transposed) 
    { 
        printf("Error: sum of vectors row & column \n");
        exit(1); 
    }
    else
    {
        for(int i=0; i<A->length; i++)
        { C->data[i] = A->data[i]+B->data[i]; }
        return;
    }
}


// Subtracts two vectors (unless lengths differ) in new vector variable
vector* vecvec_diff1(vector* A, vector* B)
{
    if (A->length != B->length) 
    { 
        printf("Error: difference of vectors with different length \n");
        exit(1); 
    }
    else if (A->transposed != B->transposed) 
    { 
        printf("Error: difference of vectors row & column \n");
        exit(1); 
    }
    else
    {
        vector* C = vector_init(A->length);
        for(int i=0; i<A->length; i++)
        { C->data[i] = A->data[i]-B->data[i]; }
        if (A->transposed) { C->transposed = true; }        
        return C;
    }
}


// Subtracts two vectors (unless lengths differ) in already initialized vector variable
void vecvec_diff2(vector* A, vector* B, vector*C)
{
    if (A->length != B->length || A->length != C->length) 
    { 
        printf("Error: difference of vectors with different length \n");
        exit(1); 
    }
    else if (A->transposed != B->transposed || A->transposed != C->transposed) 
    { 
        printf("Error: difference of vectors row & column \n");
        exit(1); 
    }
    else
    {
        for(int i=0; i<A->length; i++)
        { C->data[i] = A->data[i]-B->data[i]; }
        return;
    }
}


// Scales a vector in the same variable
void vector_scale(double k, vector* A)
{
    for(int i=0; i<A->length; i++) { A->data[i]=k*A->data[i]; }
    return;
}


// Scales a vector in a new variable
vector* vector_scale1(double k, vector* A)
{
    vector* B = vector_init(A->length);
    for(int i=0; i<A->length; i++) { B->data[i]=k*A->data[i]; }
    return B;
}


// Scales a vector in already initialized variable
void vector_scale2(double k, vector* A, vector* B)
{
    if (A->length != B->length) 
    { 
        printf("Error: scaling vector in one with different length \n");
        exit(1); 
    }

    for(int i=0; i<A->length; i++) { B->data[i]=k*A->data[i]; }
    return;
}


// Normalize a vector in the same variable
void vector_nrmlize (vector* A)
{
    double NA=vector_norm(A);
    for(int i=0; i<A->length; i++) { A->data[i]=A->data[i]/NA; }
    return;
}


// Normalize a vector in a new variable
vector* vector_nrmlize1(vector* A)
{
    vector* B = vector_init(A->length);
    double NA=vector_norm(A);
    for(int i=0; i<A->length; i++) { B->data[i]=A->data[i]/NA; }
    return B;
}


// Normalize a vector in already initialized variable
void vector_nrmlize2(vector* A, vector* B)
{
    if (A->length != B->length) 
    { 
        printf("Error: normalizing vector in one with different length \n");
        exit(1); 
    }
    double NormA= vector_norm(A);
    for(int i=0; i<A->length; i++) { B->data[i]=A->data[i]/NormA; }
    return;
}


// Scalar product of two vectors
double vecvec_scalprod(vector* A, vector* B)
{
    if (A->length != B->length) 
    { 
        printf("Error: scalar prod of vectors with different length \n");
        exit(1); 
    }
    double SP=0.0;
    for( int i=0;i<A->length;i++ ) { SP+=A->data[i]*B->data[i]; }
    return SP;
}


// Initialize a matrix given its sizes
matrix* matrix_init(int R, int C)
{
    matrix* M = malloc(sizeof(matrix));
    M->rows = R;
    M->columns = C;
    M->data = malloc(sizeof(double)*R*C);
    for (int i=0; i<R*C; i++) 
        { M->data[i] = 0.0; }
    return M;
}


// Write a value in a matrix given the position (0 to R-1 and 0 to C-1)
void matrix_write(matrix* M, int R, int C, double value)
{
    if (R>M->rows || C>M->columns)
    { 
        printf("Error: matrix writing out of bounds \n");
        exit(1); 
    }
    else 
    {
        M->data[(R) + (C)*M->rows]=value;
    }
    return;
}


// Read a value in a matrix given the position (0 to R-1 and 0 to C-1)
double matrix_read(matrix* M, int R, int C)
{
    if (R>M->rows || C>M->columns)
    { 
        printf("Error: matrix reading out of bounds \n");
        exit(1); 
    }
    
    return M->data[(R) + (C)*M->rows];
    
}


// Free allocated memory
void matrix_free (matrix* M) { free(M->data); free(M); return; }


// Returns the identity matrix
matrix* matrix_id (int N)
{
    matrix* M = matrix_init(N,N);
    for(int i=0; i<N; i++) { matrix_write(M,i,i,1); }
    return M;
}


// Sums two matrices (unless lengths differ) in new matrix variable
matrix* matmat_sum1(matrix* A, matrix* B)
{
    if (A->rows != B->rows || A->columns != B->columns) 
    { 
        printf("Error: sum of matrices with different size \n");
        exit(1); 
    }
    else
    {
        matrix* C = matrix_init(A->rows, A->columns);
        for(int i=0; i<A->rows*A->columns; i++)
        { C->data[i] = A->data[i]+B->data[i]; }
        return C;
    }
}


// Sums two matrices (unless lengths differ) in already initialized matrix variable
void matmat_sum2(matrix* A, matrix* B, matrix* C)
{
    if (A->rows != B->rows || A->columns != B->columns) 
    { 
        printf("Error: sum of matrices with different size \n");
        exit(1); 
    }
    else if (A->rows != C->rows || A->columns != C->columns) 
    { 
        printf("Error: sum of matrices with different size \n");
        exit(1); 
    }
    else
    {
        for(int i=0; i<A->rows*A->columns; i++)
        { C->data[i] = A->data[i]+B->data[i]; }
        return;
    }
}


// Difference of two matrices (unless lengths differ) in new matrix variable
matrix* matmat_diff1(matrix* A, matrix* B)
{
    if (A->rows != B->rows || A->columns != B->columns) 
    { 
        printf("Error: difference of matrices with different size \n");
        exit(1); 
    }
    else
    {
        matrix* C = matrix_init(A->rows, A->columns);
        for(int i=0; i<A->rows*A->columns; i++)
        { C->data[i] = A->data[i]-B->data[i]; }
        return C;
    }
}


// Difference of two matrices (unless lengths differ) in already initialized matrix variable
void matmat_diff2(matrix* A, matrix* B, matrix* C)
{
    if (A->rows != B->rows || A->columns != B->columns) 
    { 
        printf("Error: difference of matrices with different size \n");
        exit(1); 
    }
    else if (A->rows != C->rows || A->columns != C->columns) 
    { 
        printf("Error: difference of matrices with different size \n");
        exit(1); 
    }
    else
    {
        for(int i=0; i<A->rows*A->columns; i++)
        { C->data[i] = A->data[i]-B->data[i]; }
        return;
    }
}


// Scales a matrix in the same variable
void matrix_scale(double k, matrix* A)
{
    for(int i=0; i<A->rows*A->columns; i++) { A->data[i]=k*A->data[i]; }
    return;
}


// Scales a matrix in a new matrix variable
matrix* matrix_scale1(double k, matrix* A)
{
    matrix* B = matrix_init(A->rows, A->columns);
    for(int i=0; i< A->rows*A->columns; i++) { B->data[i]=k*A->data[i]; }
    return B;
}


// Scales a matrix in already initialized variable
void matrix_scale2(double k, matrix* A, matrix* B)
{
    if (A->rows != B->rows || A->columns != B->columns)
    { 
        printf("Error: scaling in matrix of wrong size \n");
        exit(1); 
    }
    for(int i=0; i< A->rows*A->columns; i++) { B->data[i]=k*A->data[i]; }
    return;
}


// Transposes a matrix in itself
void matrix_transp (matrix* M)
{
    matrix* MT = matrix_init(M->columns, M->rows);
    for(int i=0; i< M->columns; i++){
    for(int j=0; j< M->rows; j++){
        matrix_write(MT, i,j, matrix_read(M,j,i));
    }}
    M = MT; matrix_free(MT);
    return;
}


// Transposes a matrix in a new variable
matrix* matrix_transp1 (matrix* M)
{
    matrix* MT = matrix_init(M->columns, M->rows);
    for(int i=0; i< M->columns; i++){
    for(int j=0; j< M->rows; j++){
        matrix_write(MT, i,j, matrix_read(M,j,i));
    }}
    return MT;
}


// Transposes a matrix in already initialized variable
void matrix_transp2  (matrix* M, matrix* MT)
{
    if (M->rows != MT->columns || MT->rows != M->columns)
    { 
        printf("Error: transposing in matrix of wrong size \n");
        exit(1); 
    }
    for(int i=0; i< M->columns; i++){
    for(int j=0; j< M->rows; j++){
        matrix_write(MT, i,j, matrix_read(M,j,i));
    }}
    return;
}


// Extract a row as a new vector in new variable
vector* matrix_row1(matrix* M, int row_n)
{
    vector* V = vector_init(M->columns);
    for(int i=0; i<M->columns; i++)
    {
        V->data[i] = M->data[row_n + i*M->rows];
    }
    V->transposed = true;
    return V;
}


// Extract a row as a new vector in already initialized variable
void matrix_row2(matrix* M, int row_n, vector* V)
{
    if (V->length != M->columns)
    { 
        printf("Error: row extracted in wrong sized vector  \n");
        exit(1); 
    }

    for(int i=0; i<M->columns; i++)
    {
        V->data[i] = M->data[row_n + i*M->rows];
    }
    V->transposed = true;
    return;
}


// Extract a column as a new vector in new variable
vector* matrix_col1(matrix* M, int col_n)
{
    vector* V = vector_init(M->rows);
    for(int i=0; i<M->rows; i++)
    {
        V->data[i] = M->data[col_n*M->rows + i];
    }
    return V;
}


// Extract a column as a new vector in already initialized variable
void matrix_col2(matrix* M, int col_n, vector* V)
{
    if (V->length != M->rows)
    { 
        printf("Error: column extracted in wrong sized vector  \n");
        exit(1); 
    }

    for(int i=0; i<M->rows; i++)
    {
        V->data[i] = M->data[col_n*M->rows + i];
    }
    return;
}


// Gives the determinant of a square matrix
double matrix_det(matrix* M)
{
    if (M->rows != M->columns)
    { 
        printf("Error: det of non square matrix  \n");
        exit(1); 
    }
    double D=0.0;

    // Easy cases
    if (M->rows == 1) { D= M->data[0]; }
    if (M->rows == 2) { D= M->data[0]*M->data[3] - M->data[1]*M->data[2]; }
    
    // Recursive formula
    if (M->rows >= 3)
    {
        for(int i=0; i<M->rows; i++) 
        {
            // Create the submatrix
            matrix* N = matrix_init(M->rows-1, M->rows-1);
            for(int j=1; j<M->rows; j++){
            for(int I=0; I<M->rows; I++){
                if (I<i) { matrix_write(N, I  ,j-1, matrix_read(M, I, j) ); }
                if (I>i) { matrix_write(N, I-1,j-1, matrix_read(M, I, j) ); }
            }}

            // Sum contributions
            if (i%2) { D-= M->data[i]*matrix_det(N); }
            else { D+= M->data[i]*matrix_det(N); }
            free(N);
        }
    }

    // Return overall determinant
    return D;

}


// Gives the trace of a square matrix
double matrix_tr (matrix* M)
{
    if (M->rows != M->columns)
    { 
        printf("Error: trace of non square matrix  \n");
        exit(1); 
    }

    double T=0.0;
    for(int i=0; i<M->rows; i++) { T+=matrix_read(M,i,i); }
    return T;
}


// Matrix-vector product for column vectors in new variable
vector* matvec_prod1(matrix* M, vector* V) 
{
    if (V->length != M->columns) 
    { 
        printf("Error: matvec product with unmatching sizes \n");
        exit(1); 
    }
    else if (V->transposed)
    { 
        printf("Error: row vectors use vecmat product \n");
        exit(1); 
    }
    else
    {
        vector* W = vector_init(M->rows);
        for (int i=0; i<M->rows; i++)
        {
            for (int j=0; j<M->rows; j++)
            { W->data[i]+=M->data[i+ j*M->rows]*V->data[j]; }
        }
        return W;
    }
}


// Matrix-vector product for column vectors in already initialized variable
void matvec_prod2(matrix* M, vector* V, vector* W) 
{
    if (V->length != M->columns || W->length != M->rows) 
    { 
        printf("Error: matvec product with unmatching sizes \n");
        exit(1); 
    }
    else if (V->transposed || W->transposed)
    { 
        printf("Error: row vectors use vecmat product \n");
        exit(1); 
    }
    else
    {
        for (int i=0; i<M->rows; i++)
        {
            for (int j=0; j<M->rows; j++)
            { W->data[i]+=M->data[i+ j*M->rows]*V->data[j]; }
        }
    }
    return;
}


// Vector-matrix product for row vectors in new variable
vector* vecmat_prod1(vector* V, matrix* M) 
{
    if (V->length != M->rows) 
    { 
        printf("Error: vecmat product with unmatching sizes \n");
        exit(1); 
    }
    else if (V->transposed == false)
    { 
        printf("Error: colums vectors use matvec product \n");
        exit(1); 
    }
    else
    {
        vector* W = vector_init(M->columns);
        for (int i=0; i<M->columns; i++)
        {
            for (int j=0; j<M->rows; j++)
            { W->data[i]+=M->data[j+ i*M->rows]*V->data[j]; }
        }
        return W;
    }
}


// Vector-matrix product for row vectors in already initialized variable
void vecmat_prod2(vector* V, matrix* M, vector* W) 
{
    if (V->length != M->rows || W->length != M->columns) 
    { 
        printf("Error: vecmat product with unmatching sizes \n");
        exit(1); 
    }
    else if (V->transposed==false || W->transposed==false)
    { 
        printf("Error: column vectors use matvec product \n");
        exit(1); 
    }
    else
    {
        for (int i=0; i<M->columns; i++)
        {
            for (int j=0; j<M->rows; j++)
            { W->data[i]+=M->data[j+ i*M->rows]*V->data[j]; }
        }
    }
    return;
}


// Matrix-matrix product in new variable
matrix* matmat_prod1(matrix* A, matrix* B)
{
    if (A->columns != B->rows) 
    { 
        printf("Error: matmat product with unmatching sizes \n");
        exit(1); 
    }
    else
    {
        matrix* C = matrix_init(A->rows, B->columns);
        double RAM = 0.0;
        for(int I=0; I<A->rows; I++){
        for(int J=0; J<B->columns; J++){       
            for(int i=0; i<A->columns; i++){
                RAM += matrix_read(A, I, i)*matrix_read(B, i, J); 
            }
            matrix_write(C, I,J, RAM);
            RAM=0.0;
        }}
        return C;
    }

}


// Matrix-matrix product in already initialized variable
void matmat_prod2(matrix* A, matrix* B, matrix* C)
{
    if (A->columns != B->rows) 
    { 
        printf("Error: matmat product with unmatching sizes \n");
        exit(1); 
    }
    if (B->columns != C->columns || A->rows != C->rows) 
    { 
        printf("Error: matmat product with unmatching result \n");
        exit(1); 
    }
    else
    {
        double RAM = 0.0;
        for(int I=0; I<A->rows; I++){
        for(int J=0; J<B->columns; J++){       
            for(int i=0; i<A->columns; i++){
                RAM += matrix_read(A, I, i)*matrix_read(B, i, J); 
            }
            matrix_write(C, I,J, RAM);
            RAM=0.0;
        }}
        return;
    }

}


// Initialize a set of vectors
vecset* vecset_init(int S, int L)
{
    vecset* VS = malloc(sizeof(vecset));
    VS->number   = S;
    VS->length = L;
    VS->transposed = false;
    VS->element= malloc(S*sizeof(vector));
    for(int i=0; i<S; i++) { VS->element[i]= vector_init(L); }
    return VS;
}

// Free allocated memory
void vecset_free(vecset* VS)
{
    for(int i=0; i<VS->number; i++) { vector_free(VS->element[i]); }
    free(VS->element); free(VS);
    return;
}


// Makes a canonic base vector set
vecset* vecset_canonic (int N)
{
    matrix* ID = matrix_id(N);
    vecset* VS = vecset_init(N,N);
    for(int i=0; i<N; i++) { VS->element[i]=matrix_col1(ID,i); }
    matrix_free(ID);
    return VS;
}


void vecset_makeort (vecset* VS)
{
    vector* RAM = vector_init(VS->length);    

    for(int i=0; i<VS->number; i++)
    {
        if( vector_norm(VS->element[i]) != 0 ) 
        {
            for (int j=0; j<i; j++)
            {  
                vector_scale2( vecvec_scalprod(VS->element[j],VS->element[i])/vecvec_scalprod(VS->element[j], VS->element[j]), VS->element[j], RAM);
                VS->element[i]=vecvec_diff1(VS->element[i],VS->element[j]);
            }
        }
    }
}






