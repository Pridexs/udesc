// Alexandre Maros
// UDESC - CCT - 2015/1 & 2016/2
//
// gcc gauss_threads.c -o gauss_threads -pthread
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
#include <pthread.h>

typedef struct {
      int tid;
      int nthreads;
      int *L;
      int k;
      double *s;
      double **matriz;
      int n;
} param_t;

//Retornar o maior dos dois doubles
double dmax(double a, double b);

// Funcao executada por uma Thread
// Inicializa o vetor L e tambem acha o maior valor de cada linha
void *findMax_worker(void *arg);
void findMax(int tid, int nthreads, int n, int *L, double *s, double **matriz);

//
//
void *zerarColuna_worker(void *arg);
void zerarColuna(int tid, const int nthreads, int n, int *L, double **matriz, const int k);

int main(int argc, char* argv[])
{
    int tam, i, j, k = 0, n, nthreads = 0;
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

    pthread_t *threads  = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
    param_t *args       = (param_t *)   malloc(nthreads * sizeof(param_t));

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

    for (i = 0; i < nthreads; i++) {
        args[i].tid = i;
        args[i].nthreads = nthreads;
        args[i].L = L;
        args[i].s = s;
        args[i].matriz = matriz;
        args[i].k = k;
        args[i].n = n;
        pthread_create(&threads[i], NULL, findMax_worker, (void *) (args+i));
    }

    for (i = 0; i < nthreads; i++) {
        pthread_join(threads[i], NULL);
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

        for (i = 0; i < nthreads; i++) {
            args[i].tid = i;
            args[i].nthreads = nthreads;
            args[i].L = L;
            args[i].s = s;
            args[i].matriz = matriz;
            args[i].k = k;
            args[i].n = n;
            pthread_create(&threads[i], NULL, zerarColuna_worker, (void *) (args+i));
        }

        for (i = 0; i < nthreads; i++) {
            pthread_join(threads[i], NULL);
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
    //printf("%.5lf\n", timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000);
    
    // Impressao dos resultados
    for (i = 0; i < tam; i++) {
         printf("x%d = %.5f\n", i, x[i]);
    }
    
    //Libera memoria
    free(x); free(L); free(s);
    for (i = 0; i < tam; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}

//Retornar o maior dos dois doubles
double dmax(double a, double b) {
    if (a > b)
        return a;
    return b;
}

void *findMax_worker(void *arg) {
    param_t *p = (param_t *) arg;
    findMax(p->tid, p->nthreads, p->n, p->L, p->s, p->matriz);
    pthread_exit((void*) arg);
}

void findMax(int tid, int nthreads, int n, int *L, double *s, double **matriz) {
    int i,j,k;
    int initPos, limit, aditional = 0, remainder;
    int smax;

    remainder = n % nthreads;
    if (remainder) {
        if (tid > remainder)
            aditional = remainder ;
        else 
            aditional = tid;
    }

    initPos = (tid * (n/nthreads)) + aditional; 
    limit = initPos + (n/nthreads);

    if (tid < remainder) {
        limit++;
    }
    
    for(i = initPos; i < limit; i++) {
        L[i] = i;
        smax = 0;
        for (j = 0; j < n; j++) {
            smax = dmax(smax, abs(matriz[i][j]));
        }
        s[i] = smax;
    }
}

void *zerarColuna_worker(void *arg) {
    param_t *p = (param_t *) arg;
    zerarColuna(p->tid, p->nthreads, p->n, p->L, p->matriz, p->k);
    pthread_exit((void*) arg);
}

void zerarColuna(int tid, const int nthreads, int n, int *L, double **matriz, const int k) {
    const int qtdElementos = n - (k+1);
    int threadsAtivas = nthreads;
    int remainder, aditional = 0, limit, initPos;
    int i, j;
    double m;

    // Se tiver mais threads do que trabalho
    if (qtdElementos < nthreads ) {
        printf("%d %d\n", qtdElementos, nthreads);
        if (tid >= qtdElementos ) {
            printf("quitei\n");
            return;
        }
        threadsAtivas = qtdElementos;
    }

    remainder = qtdElementos % threadsAtivas;
    if (remainder) {
        if (tid > remainder)
            aditional = remainder;
        else 
            aditional = tid;
    }

    initPos = (tid * (qtdElementos/threadsAtivas)) + (k + 1) + aditional;
    limit = initPos + (qtdElementos/threadsAtivas);
    
    if (tid < remainder) {
        limit++;
    }

    for (i = initPos; i < limit; i++) {
        m = matriz[L[i]][k] / matriz[L[k]][k];
        matriz[L[i]][k] = 0;
        for (j = k+1; j < n+1; j++) {
            matriz[L[i]][j] = matriz[L[i]][j] - (m * matriz[L[k]][j]);
        }
    }
}