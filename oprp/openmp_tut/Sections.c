#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N     50

int main (int argc, char *argv[]) 
{
  int i, nthreads, tid;
  float a[N], b[N], c[N], d[N];

 
  

  #pragma omp parallel shared(a,b,c,d,nthreads) private(i,tid) num_threads(8)
  {
    /* Some initializations */
    #pragma omp for
    for (i=0; i<N; i++) {
      a[i] = i * 1.5;
      b[i] = i + 22.35;
      c[i] = d[i] = 0.0;
    }
  
    tid = omp_get_thread_num();
    if (tid == 0) {
      printf("Number of threads: %d\n", omp_get_num_threads());
    }
    
    printf("Thread %d starting...\n",tid);
    #pragma omp sections nowait
    {
      #pragma omp section
      {
        printf("Thread %d doing section 1\n",tid);
        for (i=0; i<N; i++){
          c[i] = a[i] + b[i];
          printf("Thread %d: c[%d]= %f\n",tid,i,c[i]);
        }
      }
      
      #pragma omp section
      {
         printf("Thread %d doing section 2\n",tid);
        for (i=0; i<N; i++){
          d[i] = a[i] * b[i];
          printf("Thread %d: d[%d]= %f\n",tid,i,d[i]);
        }
      } 
    }
    printf("Thread %d done.\n",tid); 
  }

}
