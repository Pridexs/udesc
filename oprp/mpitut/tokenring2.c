#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[])
{
    int rank, size, nchars;
    int MSG_TAG = 0;
	int token = 0, i;
	double start_time, end_time;
	char *arr;
    MPI_Status status;
    //MPI_Request *requests;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

	nchars = pow(2, rank);
	
    if (rank == 0) {
		arr = (char*) malloc(sizeof(char) * pow(2, size-1));
		arr[0] = 'a';
		
		start_time = MPI_Wtime();
        MPI_Send(arr, 1, MPI_CHAR, 1, MSG_TAG, MPI_COMM_WORLD);
		end_time = MPI_Wtime();

		//printf("%d: Demorei %f para enviar %d bytes\n", rank, end_time - start_time, 1);
		printf("%d;%f\n", 1, end_time - start_time);		

		MPI_Recv(arr, pow(2, size-1), MPI_CHAR, size-1, MSG_TAG, MPI_COMM_WORLD, &status);
		
		//printf("%d: Terminando execucao\n", rank);
    } else {
		arr = (char*) malloc(sizeof(char) * nchars);

		int nchars_recv = pow(2, rank-1);
		MPI_Recv(arr, nchars_recv, MPI_CHAR, rank-1, MSG_TAG, MPI_COMM_WORLD, &status);

		memset(arr, 'a', nchars * sizeof(char)); 
		
		//printf("%d: Recebi uma arr de %d bytes, mandando uma de %d\n", rank, nchars_recv, nchars);
		
		start_time = MPI_Wtime();
		if (rank+1 == size)
			MPI_Send(arr, nchars, MPI_CHAR, 0, MSG_TAG, MPI_COMM_WORLD);
		else
			MPI_Send(arr, nchars, MPI_CHAR, rank+1, MSG_TAG, MPI_COMM_WORLD);
		end_time = MPI_Wtime();

		//printf("%d: Demorei %f para enviar %d bytes\n", rank, end_time - start_time, nchars);
		printf("%d;%f\n", nchars, end_time - start_time);
    }

    MPI_Finalize();

    return 0;
}
