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
        void *input;

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

        size_t tBuffer = (sizeof(int) * 2) + (sizeof(double) * (tam+1)) + (sizeof(double) * tam * (tam+1));
        size_t s_inBuffer = (sizeof(double) * tam * (tam+1));
        input = (void*) malloc(s_inBuffer);
        void *output = (void*) malloc(tBuffer);

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

            nLinhas = n - (k+1);

            // O que eu preciso enviar
            // nLinhasEnviadas 
            // k
            // matriz linha L[k]
            // matriz m

            if (nLinhas < size-1) {

                // Uma ideia p/ rapida implementacao: Se tem menos linhas do que processos
                // para enviar, deixe o mestre calcular e terminar
                for (i = k+1; i < n; i++) {
                    m = matriz[L[i]][k] / matriz[L[k]][k];
                    matriz[L[i]][k] = 0;
                    for (j = k+1; j < n+1; j++) {
                        matriz[L[i]][j] = matriz[L[i]][j] - (m * matriz[L[k]][j]);
                    }
                }

            } else {
                // Quanto vamos mandar para cada processos 
                // Eh necesasrio mandar + as que faltaram se a divisao nao for perfeita
                int qtdLinhas = (size_t) floor(nLinhas / (size-1));
                int linhasAdicionais = 0;
                int pInicial = 0;

                printf("qtdLinhas: %d\n", qtdLinhas);

                z = 0;
                for (z = 1; z < size; z++) {
                    if (z == size-1) {
                        // O ultimo processo recebe mais linhas (o restante da divisao)
                        linhasAdicionais = nLinhas % (size-1);
                    }
                    pInicial = k+1 + ((z-1)*qtdLinhas);

                    printf("[0]: Enviando. k=%d qtdLinhas=%d pInicial=%d\n", k, qtdLinhas+linhasAdicionais, pInicial);

                    position = 0;
                    MPI_Pack(&qtdLinhas, 1, MPI_INT, output, tBuffer, &position, MPI_COMM_WORLD);
                    MPI_Pack(&k, 1, MPI_INT, output, tBuffer, &position, MPI_COMM_WORLD);

                    MPI_Pack(&matriz[L[k]][0], tam+1, MPI_DOUBLE, output, tBuffer, &position, MPI_COMM_WORLD);

                    for (count = 0; count < qtdLinhas+linhasAdicionais; count++) {
                        MPI_Pack(&matriz[L[pInicial+count]][0], tam+1, MPI_DOUBLE, output,
                            tBuffer, &position, MPI_COMM_WORLD);
                    }

                    // Mudar pra ISend depois
                    MPI_Send(output, position, MPI_PACKED, z, MSG_TAG, MPI_COMM_WORLD);
                }

                // Mudar para IReceive depois
                linhasAdicionais = 0;
                for (z = 1; z < size; z++) {
                    if (z == size-1) {
                        linhasAdicionais = nLinhas % (size-1);
                    }
                    pInicial = k+1 + ((z-1)*qtdLinhas);
                    
                    printf("[0]: Recebendo. k=%d qtdLinhas=%d pInicial=%d\n", k, qtdLinhas+linhasAdicionais, pInicial);

                    MPI_Recv(input, s_inBuffer, MPI_PACKED, z, MSG_TAG, MPI_COMM_WORLD, &status);

                    // colocar as linhas nos lugares originais
                    position = 0;
                    for (count = 0; count < qtdLinhas+linhasAdicionais; count++) {
                        MPI_Unpack(input, s_inBuffer, &position, &matriz[L[pInicial+count]][0],
                             tam+1, MPI_DOUBLE, MPI_COMM_WORLD);
                    }
                }
            }

            // E necessario enviar nLinhas = 0 para os outros processos terminarem
            position = 0;
            int qtdLinhas = 0;
            k = 0;
            MPI_Pack(&qtdLinhas, 1, MPI_INT, output, tBuffer, &position, MPI_COMM_WORLD);
            MPI_Pack(&k, 1, MPI_INT, output, tBuffer, &position, MPI_COMM_WORLD);

            for ( z = 1; z < size; z++) {
                MPI_Send(output, position, MPI_PACKED, z, MSG_TAG, MPI_COMM_WORLD);
            }

            /*                          *
             * FIM Eliminacao Gaussiana *
             *                          */
            
            /*                          *
             * COMECO retrosubstituicao *
             *                          */

            x = (double *) malloc(sizeof(double) * tam); // Alocacao matriz dos resultados
            x[n-1] = matriz[L[n-1]][n] / matriz[L[n-1]][n-1];
            for (i = n-2; i >= 0; i--) {
                //printf("L[%d]: %d\n", i, L[i]);
                soma = matriz[L[i]][n];
                for (j = i+1; j < tam; j++) {
                    soma -= (matriz[L[i]][j] * x[j]);
                }
                x[i] = soma / matriz[L[i]][i];
            }

            /*                          *
             * FIM retrosubstituicao    *
             *                          */
            
            // Impressao dos resultados
            // for (i = 0; i < tam; i++) {
            //      printf("x%d = %.5f\n", i, x[i]);
            // }
            
            // Libera memoria
            free(x);
            free(L); free(s);
        }


    } else {
        // preciso pegar tam de algum outro lugar (linha de comanod, etc)
        n = tam = 1000;

        // Inicializa matriz
        matriz = (double **) malloc(sizeof(double*) * tam);
        for (i = 0; i < tam; i++) {
            matriz[i] = (double *) malloc(sizeof(double) * (tam+1));
        }

        size_t tBuffer = (sizeof(int)*2) + (sizeof(double) * tam * (tam+1));
        void *input = (void*) malloc(tBuffer);
        int nLinhas;

        // Alocar espaco para toda a matriz.
        // Nunca um processo vai enviar mais a matriz inteira.

        // size output buffer
        size_t s_outBuff = (sizeof(double) * tam * (tam+1));
        void *output = (void*) malloc(s_outBuff);

        while(1)
        {
            position = 0;
            MPI_Recv(input, tBuffer, MPI_PACKED, 0, MSG_TAG, MPI_COMM_WORLD, &status);
            MPI_Unpack(input, tBuffer, &position,  &nLinhas, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(input, tBuffer, &position, &k, 1, MPI_INT, MPI_COMM_WORLD);
            
            // Se nao tem nenhuma linha para calcular, termine a execucao.
            if ( !nLinhas ) {
                break;
            }

            MPI_Unpack(input, tBuffer, &position, &matriz[0][0], tam+1,
                MPI_DOUBLE, MPI_COMM_WORLD);

            for (z = 1; z <= nLinhas; z++) {
                MPI_Unpack(input, tBuffer, &position, &matriz[z][0], tam+1,
                    MPI_DOUBLE, MPI_COMM_WORLD);
            }

            for (i = 0; i < nLinhas; i++) {
                m = matriz[i][k] / matriz[0][k];
                matriz[i][k] = 0;
                for (j = k+1; j < n+1; j++) {
                    matriz[i][j] = matriz[i][j] - (m * matriz[0][j]);
                }
            }

            // Enviar resultados p/ mestre
            position = 0;
            //MPI_Pack(&nLinhas, 1, MPI_INT, output, t_outBuff, &position, MPI_COMM_WORLD);
            for (z = 1; z <= nLinhas; z++) {
                MPI_Pack(&matriz[z][0], tam+1, MPI_DOUBLE, output, s_outBuff, &position, MPI_COMM_WORLD);
            }
            MPI_Send(output, position, MPI_PACKED, 0, MSG_TAG, MPI_COMM_WORLD);
        }
    }
    
    for (i = 0; i < tam; i++) {
        free(matriz[i]);
    }
    free(matriz);

    MPI_Finalize();

    return 0;
}


// PARTES EXPERIMENTAIS QUE FORAM TIRADAS DO CODIGO

// RECEBER MATRIZ INTEIRA DO MESTRE
/*
    * (eu acho) que essa parte e inutil.
    * nao e necessario enviar a matriz inteira
    * os processos nao precisam saber da matriz.
    */
// // receber matriz
// position = 0;
// size_t tBuffer = sizeof(int) + (sizeof(double) * tam * (tam+1)) 
//     + (sizeof(double) * tam);

// void *input = (void*) malloc(tBuffer); 
// //printf("[%d]: Esperando receber\n", rank);
// MPI_Recv(input, tBuffer, MPI_PACKED, 0, MSG_TAG, MPI_COMM_WORLD, &status);
// //printf("[%d]: Recebi\n", rank);
// MPI_Unpack(input, tBuffer, &position, &tam, 1, MPI_INT, MPI_COMM_WORLD);
// n = tam;

// //printf("[%d]: n: %d\n", rank, n);
// matriz = (double **) malloc(sizeof(double*) * tam);
// for (i = 0; i < tam; i++) {
//     matriz[i] = (double *) malloc(sizeof(double) * (tam+1));
// }
// L = (int*) calloc(n, sizeof(int));
// s = (double*) calloc(n, sizeof(double));

// for (i = 0; i < tam; i++) {
//     MPI_Unpack(input, tBuffer, &position, &matriz[i][0], tam+1,
//          MPI_DOUBLE, MPI_COMM_WORLD);
// }
// MPI_Unpack(input, tBuffer, &position, &s[0], tam,
//          MPI_DOUBLE, MPI_COMM_WORLD);

// // inicializar L
// for (int i = 0; i < n; i++) {
//     L[i] = i;
// }
//free(input);


// ==========================================



// EVNIAR MATRIZ INTEIRA PARA TODOS OS PROCESSOS
/*
    * (eu acho) que essa parte e inutil.
    * nao e necessario enviar a matriz inteira
    * os processos nao precisam saber da matriz.
    */
// // send n, matriz, s, 
// position = 0;
// size_t tBuffer = sizeof(int) + (sizeof(double) * tam * (tam+1)) 
//     + (sizeof(double) * tam);

// void *output = (void*) malloc(tBuffer);

// MPI_Pack(&tam, 1, MPI_INT, output, tBuffer, &position, MPI_COMM_WORLD);
// for (i = 0; i < tam; i++) {
//     MPI_Pack(&matriz[i][0], tam+1, MPI_DOUBLE, output, tBuffer, &position, MPI_COMM_WORLD);
// }
// MPI_Pack(&s[0], tam, MPI_DOUBLE, output, tBuffer, &position, MPI_COMM_WORLD);

// // Envio para todos assincronamente e so checo se todos receberam
// // apois a primeira troca de linhas
// for (i = 1; i < size; i++) {
//     MPI_Isend(output, position, MPI_PACKED, i, MSG_TAG, MPI_COMM_WORLD, &requests[i-1]);
// }
// Espera todos receberem e libera buffer
// for (i = 1; i < size; i++) {
//     MPI_Wait(&requests[i-1], &status);
// }
// free(output);