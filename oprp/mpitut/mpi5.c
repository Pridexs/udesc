#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int rank, size,i, count = 0;
    int tag = 0, flag;
    MPI_Status status;
    char msg[20];
    MPI_Request *requests;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    requests = (MPI_Request *) malloc(sizeof(MPI_Request) * size);

    if (rank == 0) {
        while (scanf("%d", &i) != EOF) {
            printf("%d\n", i);
        }
    } else {
        printf("Hello\n");
        while (scanf("%d", &i) != EOF) {
            printf("%d\n", i);
        }
    }

    MPI_Finalize();

    return 0;
}
