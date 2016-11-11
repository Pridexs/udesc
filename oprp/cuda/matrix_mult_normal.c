#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define NLINHAS 2048

int main()
{
    int n, i, j, z;
    size_t size = NLINHAS * NLINHAS * sizeof(int);
    
    int *a, *b, *c;

    a = (int *)malloc(size);
    b = (int *)malloc(size);
    c = (int *)malloc(size);

    struct timeval timevalA;
	struct timeval timevalB;
    
    scanf("%d", &n);

    for (int i = 0; i < NLINHAS; i++) {
        for (j = 0; j < NLINHAS; j++) {
            scanf("%d", &a[i * NLINHAS + j]);
        }
    }

    for (int i = 0; i < NLINHAS; i++) {
        for (j = 0; j < NLINHAS; j++) {
            scanf("%d", &b[i * NLINHAS + j]);
        }
    }

    gettimeofday(&timevalA,NULL);

    int soma = 0;
    for (i = 0; i < NLINHAS; i++) {
        for (j = 0; j < NLINHAS; j++) {
            for (z = 0; z < NLINHAS; z++) {
                soma += a[i * NLINHAS + z] * b[z * NLINHAS + j];
            }
            c[i * NLINHAS + j] = soma;
            soma = 0;
        }        
    }

    gettimeofday(&timevalB,NULL);

    // imprimir primeira coluna
    // for (i = 0; i < NLINHAS; i++) {
    //     for (j = 0; j < NLINHAS; j++) {
    //         printf("%d ", c[i * NLINHAS + j]);
    //     }
    //     printf("\n");
    // }
    //printf("\n");

    printf("%.5lf\n", timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000);

    return 0;
}