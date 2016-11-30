#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <mpi.h>

#define NUM_THREADS 8

///////////////////////////////////////

const int maxdim = 32;

///////////////////////////////////////
inline uint64_t now() 
{
    struct timeval tv;
    gettimeofday(&tv,0);
    return tv.tv_sec*1000000ull+tv.tv_usec;
}

///////////////////////////////////////
inline bool test(int k, int j,
                 uint64_t diag45,
                 uint64_t diag135,
                 uint64_t cols)  
{
    return ( (cols    & (1ull << j))
            + (diag135 & (1ull << (j+k))) 
            + (diag45  & (1ull << (32+j-k))) )==0;
}

///////////////////////////////////////
uint64_t solve( int niv, int dx, 
                uint64_t diag45,
                uint64_t diag135,
                uint64_t cols)
{
    uint64_t solutions=0;
    if (niv)
    {
        for (int i=0; i<dx; i++)
            if (test(niv,i, diag45, diag135, cols))
                solutions+=solve ( niv-1, dx, 
                                diag45 | (1ull << (32+i-niv)), 
                                diag135 | (1ull << (niv+i)), 
                                cols | (1ull << i ));
    }
    else
    {
        for (int i=0; i<dx; i++)
            solutions += test(0,i, diag45, diag135, cols);
    }
    return solutions;
}


uint64_t meta_solve( int dx, int rank, int size )
{
    uint64_t solutions=0;

    int niv=dx-1;

    int comeco = NUM_THREADS * rank;
    
    if (comeco > dx) 
        return 0;    

    int fim = comeco + NUM_THREADS ;

    if (fim > dx)
        fim = dx;

    #pragma omp parallel for reduction(+:solutions) schedule(guided) num_threads(NUM_THREADS)
    for (int i=comeco;i<fim;i++)
        solutions+=solve(niv-1,dx,
                    (1ull << (32+i-niv)),  // diag45
                    (1ull << (niv+i)),     // diag135
                    (1ull << i )           // cols
                    );
    
    std::cout << "Rank " << rank << " found " << solutions << " solutions." << std::endl;

    return solutions;
}

///////////////////////////////////////
int main(int argc, char* argv[])
{
    MPI_Status status;
    MPI_Request *sendRequests, *recvRequests;
    int rank, size;

    if (argc >= 2 )
    {
        MPI_Init(&argc, &argv);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        int dx = std::max(1,std::min(maxdim,std::atoi(argv[1])));

        uint64_t start = now();

        uint64_t solutions = meta_solve(dx, rank, size);
        uint64_t sol = 0;
        MPI_Reduce(&solutions, &sol, size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 

        uint64_t stop = now();

        if (rank == 0) {
            std::cout << dx << ' '
                  << sol << ' ' 
                  << std::setiosflags(std::ios::fixed)
                  << std::setprecision(6)
                  << (stop-start)/(double)1000000.0 
                  << std::endl;
        }
        
        MPI_Finalize();

        return 0;
    }
    else 
    {
        std::cerr << "./nq <num> " << std::endl;
        return 1;
    }
 }

