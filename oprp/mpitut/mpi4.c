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
        strcpy(msg, "Hellow World!\n");
        for (i = 1; i < size; i++) {
            MPI_Isend(msg, 13, MPI_CHAR, i, tag, MPI_COMM_WORLD, &requests[i-1]);
        }

        while (!count)
        {
            count = size-1;
            for (i = 1; i < size; i++) {
                MPI_Test(&requests[i-1], &flag, &status);
                if (flag) 
                    count--;
            }
        }

        //for (i = 1; i < size; i++) {
        //    MPI_Test(&requests[i-1], &flag, &status);
                
            //MPI_Wait(&requests[i-1], &status);
        //}
    } else {
        MPI_Recv(msg, 20, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
        printf("Message received: %s\n", msg);
    }


    MPI_Finalize();

    return 0;
}
