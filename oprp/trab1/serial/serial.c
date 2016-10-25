/*
// Alexandre Maros
// UDESC - CCT - 2015/1
//
// Para compilar no Linux: gcc gauss2.c -o gauss2 -lm
// Algoritmo de Eliminacao de Gauss com escala sem troca fisica de linhas.

// Primeiro entre com a matriz A com as instrucoes impressas na tela
// E em seguida entre com a matriz B.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

//Retornar o maior dos dois doubles
double dmax(double a, double b) {
    if (a > b)
        return a;
    return b;
}

int main()
{
    int tam, i, j, k, n;
    int *L;
    double **matriz, *x,*s;
    double m, soma, temp, smax, r, rmax;
    clock_t inicio, fim;

    struct timeval timevalA;
	struct timeval timevalB;

    //printf("Entre o tamanho da matriz: ");
    scanf("%d", &tam);

    // Alocacao da matriz;
    matriz = (double **) malloc(sizeof(double*) * tam);
    for (i = 0; i < tam; i++) {
        // Alocar tam+1 colunas.
        matriz[i] = (double *) malloc(sizeof(double) * (tam+1));
    }
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            //printf("Matriz[%d][%d]: ", i, j);
            scanf("%lf", &matriz[i][j]);
        }
    }
    //printf("Entre com a matriz b\n");
    for (i = 0; i < tam; i++) {
        //printf("b[%d]: ", i);
        scanf("%lf", &matriz[i][tam]);
    }

    inicio = clock();
    gettimeofday(&timevalA,NULL);
    /* Comeco Eliminacao Gaussiana */
    n = tam;
    L = (int*) calloc(n, sizeof(int));
    s = (double*) calloc(n, sizeof(double));
    
    for (i = 0; i < n; i++) {
        L[i] = i;
        smax = 0;
        for (j = 0; j < n; j++) {
            smax = dmax(smax, abs(matriz[i][j]));
        }
        s[i] = smax;
    }
    
    for (k = 0; k < n-1; k++) {
	int aaa = 0;
        for ( aaa =0; aaa < tam+1; aaa++) {
            printf("%lf ", matriz[39][aaa]);
        }
        printf("\n\n");

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

        //#pragma omp parallel for private(i,j, m) shared(k, matriz)
        for (i = k+1; i < n; i++) {
            m = matriz[L[i]][k] / matriz[L[k]][k];
            matriz[L[i]][k] = 0;
            for (j = k+1; j < n+1; j++) {
                matriz[L[i]][j] = matriz[L[i]][j] - (m * matriz[L[k]][j]);
            }
        }
    }
    /* Fim Eliminacao Gaussiana */

    /* Comeco impressao Matrizes */
    // printf("\n\nA:\n");
    // for (i = 0; i < n; i++) {
    //     for (j = 0; j < n; j++)
    //         printf("%.3f ", matriz[i][j]);
    //     printf("\n");
    // }
    // printf("\nB: ");
    // for (i = 0; i < n; i++)
    //     printf("%.3f ", matriz[i][n]);
    // printf("\nL: ");
    // for (i = 0; i < n; i++)
    //     printf("%d ", L[i]);
    // printf("\n");
    /* Fim impressao Matrizes */
    
    /* Comeco retrosubstituicao */
    x = (double *) malloc(sizeof(double) * tam); // Alocacao matriz dos resultados
    x[n-1] = matriz[L[n-1]][n] / matriz[L[n-1]][n-1];
    for (i = n-2; i >= 0; i--)
    {
        //printf("L[%d]: %d\n", i, L[i]);
        soma = matriz[L[i]][n];
        for (j = i+1; j < tam; j++) {
            soma -= (matriz[L[i]][j] * x[j]);
        }
        x[i] = soma / matriz[L[i]][i];
    }
    /* Fim retrosubstituicao */

    gettimeofday(&timevalB,NULL);
    printf("%.5lf\n", timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000);
    
    // Impressao dos resultados
    for (i = 0; i < tam; i++) {
         printf("x%d = %.5f\n", i, x[i]);
    }
    
    // Impressao dos ticks de clock
    fim = clock();
    //printf("A operacao demorou %.5f segundos e demorou %d ticks de clock\n", ( (double) fim-inicio)/CLOCKS_PER_SEC , fim-inicio);

    //Libera memoria
    free(x); free(L); free(s);
    for (i = 0; i < tam; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}

