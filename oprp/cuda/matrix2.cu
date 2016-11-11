#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#define NLINHAS 2048
#define NCOLUNAS 2048
#define THREADS_PER_BLOCK 1024
//32x32
#define NTHREADS 32
#define NCOLUNASPERBLOCK 32
#define NLINHASPERBLOCK 32

__global__ void vector_mul(int *a, int *b, int *c) {
    int i, z, soma = 0;

    int coluna = blockIdx.x * blockDim.x + threadIdx.x;
    int linha =  blockIdx.y * blockDim.y + threadIdx.y;

    __shared__ int s_a[NLINHASPERBLOCK][NCOLUNASPERBLOCK];
    __shared__ int s_b[NLINHASPERBLOCK][NCOLUNASPERBLOCK];

	for (z = 0; z < gridDim.x; z++) {
        s_a[threadIdx.y][threadIdx.x] = a[ (NCOLUNAS * (blockIdx.y * NLINHASPERBLOCK + threadIdx.y)) + (z * NCOLUNASPERBLOCK + threadIdx.x) ];
        s_b[threadIdx.y][threadIdx.x] = b[ (NCOLUNAS * (z * NLINHASPERBLOCK + threadIdx.y)) + blockIdx.x * NCOLUNASPERBLOCK + threadIdx.x ];
        
        __syncthreads();

		for (i = 0; i < NLINHASPERBLOCK; i++) {
	    	soma += s_a[threadIdx.y][i] * s_b[i][threadIdx.x];
	    }

        __syncthreads();
	}

    //printf("%d %d\n", linha, coluna);
    c[linha * NLINHAS + coluna] = soma;
}

int main(){
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;
    int size = NLINHAS * NCOLUNAS * sizeof(int);
    int i, j, n;

    struct timeval timevalA;
	struct timeval timevalB;

    cudaMalloc((void **) &d_a, size);
    cudaMalloc((void **) &d_b, size);
    cudaMalloc((void **) &d_c, size);

    a = (int *)malloc(size);
    b = (int *)malloc(size);
    c = (int *)malloc(size);

    for(i = 0; i < NLINHAS*NCOLUNAS; i++){
//        a[i] = b[i] = i % 10;
        c[i] = 0;
    }

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
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    dim3 tbloco = dim3(64, 64,1);
    dim3 tthreads = dim3(32, 32, 1);
    vector_mul<<<tbloco,tthreads>>>(d_a, d_b, d_c);
    
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
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

    free(a); free(b); free(c);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
