/*******************************************************************************
*
* File 04_MatrixDetTr.c
*
* Calculates the determinant and trace of a square matrix
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
    matrix* A=matrix_init(3,3);

    // Fill matrix
    A->data[0]=178; A->data[3]=4750; A->data[6]=23050;
    A->data[1]=210; A->data[4]=92; A->data[7]=94252;
    A->data[2]=1290; A->data[5]=169; A->data[8]=10;

    // Transpose
    matrix* B = matrix_transp1(A);
    
    // Print det and tr of matrix
    printf("det[A]= %f \n", matrix_det(B));
    printf("Tr[A] = %f \n", matrix_tr(B));

    // Free memory
    matrix_free(A); matrix_free(B);

    exit(0);

}

