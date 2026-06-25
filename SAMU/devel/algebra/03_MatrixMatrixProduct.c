/*******************************************************************************
*
* File 03_MatrixMatrixProduct.c
*
* Calculates the product of two non square matrices, failing in the wrong direction
*
* Author: Samuele Campaniello
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "random.h"
#include "global.h"
#include "money.h"
#include "algebra.h"
#include "types.h"
#include "start.h"

int main () 
{
    // Declare variables    
    matrix* A=matrix_init(3,2);
    matrix* B=matrix_init(2,4);

    // Fill matrices
    for(int i=0; i<A->rows*A->columns; i++) { A->data[i]=i; }
    B->data[0]=1;   B->data[1]=2;
    B->data[2]=10;  B->data[3]=20;
    B->data[4]=100; B->data[5]=200;
    B->data[6]=1000;B->data[7]=2000;

    // Calculate the product   
    matrix* C = matmat_prod1(A,B);

    // Print product vectors
    printf("C=AB: \n");
    for(int i=0; i<12; i++) { printf("%f \n", C->data[i]); }

    // Free memory
    matrix_free(A); matrix_free(B); matrix_free(C);  

    exit(0);

}

