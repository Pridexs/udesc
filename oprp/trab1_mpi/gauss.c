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
    MPI_Request *sendRequests, *recvRequests;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Se o rank for 0, inicialize e mande para todas os processos
    if (rank == 0) {
        
        sendRequests = (MPI_Request*) malloc(sizeof(MPI_Request) * size);
        recvRequests = (MPI_Request*) malloc(sizeof(MPI_Request) * size);

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
        
        for (i = 1; i < size; i++) {
            MPI_Send(&tam, 1, MPI_INT, i, MSG_TAG, MPI_COMM_WORLD);
        }

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

        int *jaCalculado = (int*) malloc(sizeof(int) * (size-1));
        
        // Eu preciso enviar/receber size-1 buffers diferentes pois estamos
        // usando isend e irecv
        void **input = (void**) malloc(sizeof(void*) * (size-1));
        for (i = 0; i < size-1; i++) {
            input[i] = (void*) malloc(s_inBuffer);
        }

        void **output = (void**) malloc(sizeof(void*) * (size-1));
        for (i = 0; i < size-1; i++) {
            output[i] = (void*) malloc(tBuffer);
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
                int qtdLinhas = (size_t) (nLinhas / (size-1));
                int linhasAdicionais = 0;
                int pInicial = 0;

                z = 0;
                for (z = 1; z < size; z++) {
                    if (z == size-1) {
                        // O ultimo processo recebe mais linhas (o restante da divisao)
                        linhasAdicionais = nLinhas % (size-1);
                    }
                    pInicial = k+1 + ((z-1)*qtdLinhas);

                    int nLinhasEnviadas = qtdLinhas + linhasAdicionais;

                    position = 0;
                    MPI_Pack(&nLinhasEnviadas, 1, MPI_INT, &output[z-1][0], tBuffer, &position, MPI_COMM_WORLD);
                    MPI_Pack(&k, 1, MPI_INT, &output[z-1][0], tBuffer, &position, MPI_COMM_WORLD);
                    MPI_Pack(&matriz[L[k]][0], tam+1, MPI_DOUBLE, &output[z-1][0], tBuffer, &position, MPI_COMM_WORLD);

                    for (count = 0; count < qtdLinhas+linhasAdicionais; count++) {
                        MPI_Pack(&matriz[L[pInicial+count]][0], tam+1, MPI_DOUBLE, &output[z-1][0],
                            tBuffer, &position, MPI_COMM_WORLD);
                    }

                    //MPI_Send(output, position, MPI_PACKED, z, MSG_TAG, MPI_COMM_WORLD);
                    MPI_Isend(&output[z-1][0], position, MPI_PACKED, z, MSG_TAG, MPI_COMM_WORLD, &sendRequests[z-1]);
                }
                
                int flag = 0;
                int countSize = size-1;

                for (z = 1; z < size; z++) {
                    MPI_Irecv(&input[z-1][0], s_inBuffer, MPI_PACKED, z, MSG_TAG, MPI_COMM_WORLD, &recvRequests[z-1]);
                }

                memset(jaCalculado, 0, sizeof(int) * (size-1));    
                while (countSize) {
                    for (z = 1; z < size; z++) {
                        if (!jaCalculado[z-1]) {
                            // Eu nao testo sendRequets, pois se eu ja recebi ele tambem ja enviou
                            MPI_Test(&recvRequests[z-1], &flag, &status);
                            linhasAdicionais = 0;
                            if (flag) {
                                if (z == size-1) {
                                    linhasAdicionais = nLinhas % (size-1);
                                }
                                pInicial = k+1 + ((z-1)*qtdLinhas);
                                
                                // colocar as linhas nos lugares originais
                                position = 0;
                                for (count = 0; count < qtdLinhas+linhasAdicionais; count++) {
                                    MPI_Unpack(&input[z-1][0], s_inBuffer, &position, &matriz[L[pInicial+count]][0],
                                        tam+1, MPI_DOUBLE, MPI_COMM_WORLD);
                                        int kkk = 0;
                                }
                                
                                jaCalculado[z-1] = 1;
                                countSize--;
                            }
                        }
                    }
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
        
        //Impressao dos resultados
        for (i = 0; i < tam; i++) {
             printf("x%d = %.5f\n", i, x[i]);
        }
        
        // Libera memoria
        free(x);
        free(L); free(s);


    } else {
        MPI_Recv(&tam, 1, MPI_INT, 0, MSG_TAG, MPI_COMM_WORLD, &status);
        n = tam;

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
        int countaleatorio = 0;
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

            for (i = 1; i <= nLinhas; i++) {
                m = matriz[i][k] / matriz[0][k];
                matriz[i][k] = 0;
                for (j = k+1; j < n+1; j++) {
                    matriz[i][j] = matriz[i][j] - (m * matriz[0][j]);
                }                
            }

            // Enviar resultados p/ mestre
            position = 0;
            
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