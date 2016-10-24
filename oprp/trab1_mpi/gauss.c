#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MASTER 0        // id do mestre
#define MSG_TAG 0       // tag das mensagens

//Retornar o maior dos dois doubles
double dmax(double a, double b) {
    if (a > b)
        return a;
    return b;
}

int main(int argc, char* argv[])
{
    int tam, i, j, k, z, n, count, linhasEnviadas;
    int rank, size, position;
    int *L;
    double **matriz, *x,*s;
    double m, soma, temp, smax, r, rmax;
    MPI_Status status;
    MPI_Request *requests;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    requests = (MPI_Request*) malloc(sizeof(MPI_Request) * size);

    // Se o rank for 0, inicialize e mande para todas os processos
    if (rank == 0) {
        int nLinhas;
        int qtdBlocos;

        scanf("%d", &tam);

        matriz = (double **) malloc(sizeof(double*) * tam);
        for (i = 0; i < tam; i++) {
            matriz[i] = (double *) malloc(sizeof(double) * (tam+1));
        }
        for (i = 0; i < tam; i++) {
            for (j = 0; j < tam; j++) {
                scanf("%lf", &matriz[i][j]);
            }
        }
        for (i = 0; i < tam; i++) {
            scanf("%lf", &matriz[i][tam]);
        }
        
        n = tam;
        L = (int*) calloc(n, sizeof(int));
        s = (double*) calloc(n, sizeof(double));
        
        // #pragma omp aqui?
        for (i = 0; i < n; i++) {
            L[i] = i;
            smax = 0;
            for (j = 0; j < n; j++) {
                smax = dmax(smax, abs(matriz[i][j]));
            }
            s[i] = smax;
        }

        // send n, matriz, s, 
        position = 0;
        size_t tBuffer = sizeof(int) + (sizeof(double) * tam * (tam+1)) 
            + (sizeof(double) * tam);

        void *output = (void*) malloc(tBuffer);

        MPI_Pack(&tam, 1, MPI_INT, output, tBuffer, &position, MPI_COMM_WORLD);
        for (i = 0; i < tam; i++) {
            MPI_Pack(&matriz[i][0], tam+1, MPI_DOUBLE, output, tBuffer, &position, MPI_COMM_WORLD);
        }
        MPI_Pack(&s[0], tam, MPI_DOUBLE, output, tBuffer, &position, MPI_COMM_WORLD);

        // Envio para todos assincronamente e so checo se todos receberam
        // apois a primeira troca de linhas
        for (i = 1; i < size; i++) {
            MPI_Isend(output, position, MPI_PACKED, i, MSG_TAG, MPI_COMM_WORLD, &requests[i-1]);
        }

        for (k = 0; k < n-1; k++) {
            rmax = 0;
            for (i = k; i < n; i++) {
                r = abs(matriz[L[i]][k]) / s[L[i]];
                if (r > rmax) {
                    rmax = r;
                    j = i;
                }
            }
            // Troca de L[j] por L[k]
            temp = L[j];
            L[j] = L[k];
            L[k] = temp;

            // Espera todos receberem e libera buffer
            for (i = 1; i < size; i++) {
                MPI_Wait(&requests[i-1], &status);
            }
            free(output);

            nLinhas = n - k+1;
            

            // O que eu preciso enviar
            // j, k (para cada processo trocar seu proprio L)
            // nLinhasEnviadas 
            // matriz m

            if (nLinhas < size-1) {

            } else {
                // Quanto vamos mandar para cada processos 
                // Eh necesasrio mandar + as que faltaram se a divisao nao for perfeita
                int qtdLinhas = ((int) (nLinhas / (size-1)));
                int linhasAdicionais = 0;

                size_t tBuffer = (sizeof(int)*3) + (sizeof(double) * qtdLinhas * (tam+1));
                output = (void*) malloc(tBuffer);
                z = 0;
                for (z = 1; z < size; z++) {
                    if (z == size-1) {
                        // O ultimo processo recebe mais linhas (o restante da divisao)
                        linhasAdicionais = nLinhas % (size-1);
                    }
                    int pInicial = k+1 + ((z-1)*qtdLinhas);

                    printf("k=%d\nqtdLinhas=%d\npInicial=%d\n", k, qtdLinhas, pInicial)

                    position = 0;
                    MPI_Pack(&j, 1, MPI_INT, output, tBuffer, &position, MPI_COMM_WORLD);
                    MPI_Pack(&k, 1, MPI_INT, output, tBuffer, &position, MPI_COMM_WORLD);
                    MPI_Pack(&qtdLinhas, 1, MPI_INT, output, tBuffer, &position, MPI_COMM_WORLD);
                    for (count = 0; i < qtdLinhas+linhasAdicionais; i++) {
                        MPI_Pack(&matriz[pInicial+count][0], tam+1, MPI_DOUBLE, output,
                            tBuffer, &position, MPI_COMM_WORLD);
                    }
                }                
                
            }

            // //#pragma omp parallel for private(i,j, m) shared(k, matriz) num_threads(nthreads)
            // for (i = k+1; i < n; i++) {
            //     m = matriz[L[i]][k] / matriz[L[k]][k];
            //     matriz[L[i]][k] = 0;
            //     for (j = k+1; j < n+1; j++) {
            //         matriz[L[i]][j] = matriz[L[i]][j] - (m * matriz[L[k]][j]);
            //     }
            // }
        }


    } else {
        // preciso pegar tam de algum outro lugar (linha de comanod, etc)
        tam = 1000;

        // receber matriz
        position = 0;
        size_t tBuffer = sizeof(int) + (sizeof(double) * tam * (tam+1)) 
            + (sizeof(double) * tam);
        
        void *input = (void*) malloc(tBuffer); 
        //printf("[%d]: Esperando receber\n", rank);
        MPI_Recv(input, tBuffer, MPI_PACKED, 0, MSG_TAG, MPI_COMM_WORLD, &status);
        //printf("[%d]: Recebi\n", rank);
        MPI_Unpack(input, tBuffer, &position, &tam, 1, MPI_INT, MPI_COMM_WORLD);
        n = tam;

        //printf("[%d]: n: %d\n", rank, n);
        matriz = (double **) malloc(sizeof(double*) * tam);
        for (i = 0; i < tam; i++) {
            matriz[i] = (double *) malloc(sizeof(double) * (tam+1));
        }
        L = (int*) calloc(n, sizeof(int));
        s = (double*) calloc(n, sizeof(double));

        for (i = 0; i < tam; i++) {
            MPI_Unpack(input, tBuffer, &position, &matriz[i][0], tam+1,
                 MPI_DOUBLE, MPI_COMM_WORLD);
        }
        MPI_Unpack(input, tBuffer, &position, &s[0], tam,
                 MPI_DOUBLE, MPI_COMM_WORLD);
        
        // inicializar L
        for (int i = 0; i < n; i++) {
            L[i] = i;
        }

        free(input);
        tBuffer = (sizeof(int)*3) + (sizeof(double) * tam * (tam+1));
        input = (void*) malloc(tBuffer);

        int nLinhas;

        while(true)
        {
            MPI_Recv(input, tBuffer, MPI_PACKED, 0, MSG_TAG, MPI_COMM_WORLD, &status);
            MPI_Unpack(input, tBuffer, &j, &tam, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(input, tBuffer, &k, &tam, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(input, tBuffer, &nLinhas, &tam, 1, MPI_INT, MPI_COMM_WORLD);
            
            // Se o mestre enviar j = 0, k = 0 e nLinhas = 0
            // e por que o programa terminou.
            if (!j && !k && !nLinhas) {
                break;
            }

            // Se nao tem nenhuma linha para calcular, continue.
            // provavelmente se um processo nao recebeu a linha ele 
            // nunca mais vai receber. rever isso daqui depois.
            if ( !nLinhas ) {
                continue;
            }

            for (z = 0; z < nLinhas; z++) {
                MPI_Unpack(input, tBuffer, &position, &matriz[k+1+z][0], tam+1,
                 MPI_DOUBLE, MPI_COMM_WORLD);
            }

        }
        
        



    }
    
    
    // for (k = 0; k < n-1; k++) {
    //     rmax = 0;
    //     for (i = k; i < n; i++) {
    //         r = abs(matriz[L[i]][k]) / s[L[i]];
    //         if (r > rmax) {
    //             rmax = r;
    //             j = i;
    //         }
    //     }
    //     // Troca de L[j] por L[k]
    //     temp = L[j];
    //     L[j] = L[k];
    //     L[k] = temp;

    //     //#pragma omp parallel for private(i,j, m) shared(k, matriz) num_threads(nthreads)
    //     for (i = k+1; i < n; i++) {
    //         m = matriz[L[i]][k] / matriz[L[k]][k];
    //         matriz[L[i]][k] = 0;
    //         for (j = k+1; j < n+1; j++) {
    //             matriz[L[i]][j] = matriz[L[i]][j] - (m * matriz[L[k]][j]);
    //         }
    //     }
    // }

    // /*                          *
    //  * FIM Eliminacao Gaussiana *
    //  *                          */
    
    // /*                          *
    //  * COMECO retrosubstituicao *
    //  *                          */

    // x = (double *) malloc(sizeof(double) * tam); // Alocacao matriz dos resultados
    // x[n-1] = matriz[L[n-1]][n] / matriz[L[n-1]][n-1];
    // for (i = n-2; i >= 0; i--) {
    //     //printf("L[%d]: %d\n", i, L[i]);
    //     soma = matriz[L[i]][n];
    //     for (j = i+1; j < tam; j++) {
    //         soma -= (matriz[L[i]][j] * x[j]);
    //     }
    //     x[i] = soma / matriz[L[i]][i];
    // }

    // /*                          *
    //  * FIM retrosubstituicao    *
    //  *                          */
    
    // // Impressao dos resultados
    // // for (i = 0; i < tam; i++) {
    // //      printf("x%d = %.5f\n", i, x[i]);
    // // }
    
    //Libera memoria
    //free(x);
    free(L); free(s);
    for (i = 0; i < tam; i++) {
        free(matriz[i]);
    }
    free(matriz);

    MPI_Finalize();

    return 0;
}