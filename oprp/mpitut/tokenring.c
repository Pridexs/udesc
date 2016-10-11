#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int rank, size;
    int MSG_TAG = 0;
	int token = 0;
    MPI_Status status;
    //MPI_Request *requests;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //requests = (MPI_Request *) malloc(sizeof(MPI_Request) * size);

    if (rank == 0) {
        MPI_Send(&token, 1, MPI_INT, 1, MSG_TAG, MPI_COMM_WORLD);
		MPI_Recv(&token, 1, MPI_INT, size-1, MSG_TAG, MPI_COMM_WORLD, &status);
		printf("%d: Recebi token %d. Terminando execucao\n", rank, token);
    } else {
		MPI_Recv(&token, 1, MPI_INT, rank-1, MSG_TAG, MPI_COMM_WORLD,
            &status);
		printf("%d: Recebi token %d. Enviando %d\n", rank, token, token+rank);
		token += rank;		

		if (rank+1 == size)
			MPI_Send(&token, 1, MPI_INT, 0, MSG_TAG, MPI_COMM_WORLD);
		else
			MPI_Send(&token, 1, MPI_INT, rank+1, MSG_TAG, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
