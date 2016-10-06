#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size,i;
    int tag = 0;
    MPI_Status status;
    char msg[20];    

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("(%d) -> Primeiro a escrever!!!!!!!!\n", rank);
        MPI_Barrier(MPI_COMM_WORLD);
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
        printf("(%d) -> Agora posso escrever!!!!!!!!!!!!!!\n", rank);
    }

    MPI_Finalize();

    return 0;
}
