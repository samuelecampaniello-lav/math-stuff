/*******************************************************************************
*
* File 01_CubeDiagonal.c
*
* Calculates the length of the diagonal of a D-dim cube
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
    int D=4;
    double L=1.0;
    vector* V=vector_init(D);
    vector* W=vector_init(D);

    // Position points in D-dim space
    for (int i=0; i<D; i++) { V->data[i]=0.0; }
    for (int i=0; i<D; i++) { W->data[i]=1.0; }

    // Calculate distance    
    vector* Z = vector_scale1(L, vector_diff1(V,W));

    // Print norm of distance
    printf("Diagonal of a %d-dimensional cube: %f \n", D, pow(vector_scalprod(Z,Z),0.5) );

    // Free memory
    vector_free(V);
    vector_free(W);
    vector_free(Z);

    exit(0);

}
