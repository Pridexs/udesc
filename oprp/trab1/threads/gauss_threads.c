// Alexandre Maros
// UDESC - CCT - 2015/1 & 2016/2
//
// gcc gauss_omp.c -o gauss_omp -fopenmp
//
// Eliminacao Gaussiana sem troca fisica de linhas implementado
// com openmp
//

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

int main(int argc, char* argv[])
{
    int tam, i, j, k, n, nthreads = 0;
    int *L;
    double **matriz, *x,*s;
    double m, soma, temp, smax, r, rmax;
    
    struct timeval timevalA;
	struct timeval timevalB;

    if (argc > 1) {
		nthreads = atoi(argv[1]);
	} else {
		printf("Especifique o numero de threads\n");
		return -1;
	}

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

    gettimeofday(&timevalA,NULL);

    /*                             *
     * INICIO Eliminacoa Gaussiana *
     *                             */
     
    n = tam;
    L = (int*) calloc(n, sizeof(int));
    s = (double*) calloc(n, sizeof(double));
    
    #pragma omp paralel for private(i,j,smax) shared(L, s) num_threads(nthreads)
    for (i = 0; i < n; i++) {
        L[i] = i;
        smax = 0;
        for (j = 0; j < n; j++) {
            smax = dmax(smax, abs(matriz[i][j]));
        }
        s[i] = smax;
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

        #pragma omp parallel for private(i,j, m) shared(k, matriz) num_threads(nthreads)
        for (i = k+1; i < n; i++) {
            m = matriz[L[i]][k] / matriz[L[k]][k];
            matriz[L[i]][k] = 0;
            for (j = k+1; j < n+1; j++) {
                matriz[L[i]][j] = matriz[L[i]][j] - (m * matriz[L[k]][j]);
            }
        }
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

    gettimeofday(&timevalB,NULL);
    printf("%.5lf\n", timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000);
    
    // Impressao dos resultados
    //for (i = 0; i < tam; i++) {
    //     printf("x%d = %.5f\n", i, x[i]);
    //}
    
    //Libera memoria
    free(x); free(L); free(s);
    for (i = 0; i < tam; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}

