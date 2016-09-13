#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int tid, nthreads;
    
    #pragma omp parallel private(tid, nthreads)
    {
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);
        
        #pragma omp master
        {
           nthreads = omp_get_num_threads();
           printf("Number of threads: %d\n", nthreads);
        }
    }
    
    return 0;
}
