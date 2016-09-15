/******************************************************************************
* FILE: mm.c
* DESCRIPTION:  
*   Matrix Multiply - C Version
*   Modified from Blaise Barney OpenMP code.
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NRA 2000                 /* number of rows in matrix A */
#define NCA 1000                 /* number of columns in matrix A */
#define NCB 1000                  /* number of columns in matrix B */

#define STATIC_CHUNK 200
#define DYNAMIC_CHUNK 200

double a[NRA][NCA],           /* matrix A to be multiplied */
	 b[NCA][NCB],           /* matrix B to be multiplied */
	 c[NRA][NCB];           /* result matrix C */

int main (int argc, char *argv[]) 
{
  int	 i, j, k;
  

  /*** Initialize matrices ***/
  #pragma omp parallel num_threads(7) private(i,j,k) shared(c, a, b)
  {
 
    #pragma omp for nowait
    for (i=0; i<NRA; i++)
      for (j=0; j<NCA; j++)
        a[i][j]= i+j;
    
    #pragma omp for nowait
    for (i=0; i<NCA; i++)
      for (j=0; j<NCB; j++)
        b[i][j]= i*j;
    
    #pragma omp for
    for (i=0; i<NRA; i++)
      for (j=0; j<NCB; j++)
        c[i][j]= 0;

    /*** Do matrix multiply ***/
    //#pragma omp parallel for private(i,j,k) shared(c, a, b) num_threads(7) schedule(static, 1)
    //#pragma omp parallel for private(i,j,k) shared(c, a, b) num_threads(7) schedule(static, STATIC_CHUNK)
    //#pragma omp parallel for private(i,j,k) shared(c, a, b) num_threads(7) schedule(dynamic, 1)
    //#pragma omp parallel for private(i,j,k) shared(c, a, b) num_threads(7) schedule(dynamic, DYNAMIC_CHUNK)
    #pragma omp for schedule(guided)
    for (i=0; i<NRA; i++) {    
      for(j=0; j<NCB; j++) {       
        for (k=0; k<NCA; k++) {
          c[i][j] += a[i][k] * b[k][j];
        }
      }
    }
  }

  /*** Print results ***/
  printf("******************************************************\n");
  printf("Result Matrix:\n");
  //for (i=0; i<NRA; i++)
  //{
  //  for (j=0; j<NCB; j++) 
  //    printf("%6.2f   ", c[i][j]);
  //  printf("\n"); 
  //}
  printf("******************************************************\n");
  printf ("Done.\n");

}
