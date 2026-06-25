/*******************************************************************************
*
* File 02_MatrixVectorProduct.c
*
* Calculates the product of a vector by a matrix, both LX and RX
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
    vector* V=vector_init(2);
    vector* W=vector_init(3); W->transposed=true;
    matrix* M=matrix_init(3,2);

    // Fill vectors and matrix
    V->data[0]=1.0; V->data[1]=10.0; 
    W->data[0]=1.0; W->data[1]=10.0; W->data[2]=100.0;
    for(int i=0; i<M->rows*M->columns; i++) { M->data[i]=i; }

    // Calculate products    
    vector* MV = matvec_prod1(M,V);
    vector* WM = vecmat_prod1(W,M);

    // Print product vectors
    printf("MV: \n");
    for(int i=0; i<3; i++) { printf("%f \n", MV->data[i]); }
    printf("WM: \n");
    for(int i=0; i<2; i++) { printf("%f \n", WM->data[i]); }

    // Free memory
    vector_free(V);  vector_free(W);
    vector_free(MV); vector_free(WM);
    matrix_free(M);

    exit(0);

}
