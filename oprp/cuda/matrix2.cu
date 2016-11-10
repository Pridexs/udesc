#include <stdio.h>

#define NLINHAS 1024
#define NCOLUNAS 1024
#define THREADS_PER_BLOCK 1024
//32x32
#define NTHREADS 32
#define NCOLUNASPERBLOCK NCOLUNAS/32
#define NLINHASPERBLOCK NLINHAS/32

__global__ void vector_mul(int *a, int *b, int *c) {
    int i, z, soma = 0;

    int coluna = blockIdx.x * blockDim.x + threadIdx.x;
    int linha =  blockIdx.y * blockDim.y + threadIdx.y;

    __shared__ int s_a[NLINHASPERBLOCK][NCOLUNASPERBLOCK];
    __shared__ int s_b[NLINHASPERBLOCK][NCOLUNASPERBLOCK];

    // Copia Matriz
	for (z = 0; z < blockDim.x; z++) {
        //s_a[threadIdx.x][threadIdx.y] = a[ blockIdx.y * NLINHASPERBLOCK + threadIdx.y ][ z * NCOLUNASPERBLOCK + threadIdx.x ]
        //s_b[threadIdx.x][threadIdx.y] = b[ z * NLINHASPERBLOCK + threadId.x  ][ blockIdx.x * NCOLUNASPERBLOCK + threadIdx.x ]
        
        s_a[threadIdx.x][threadIdx.y] = a[ (NCOLUNAS * (blockIdx.y * NLINHASPERBLOCK + threadIdx.y)) + (z * NCOLUNASPERBLOCK + threadIdx.x) ];
        s_b[threadIdx.x][threadIdx.y] = b[ (NCOLUNAS * (z * NLINHASPERBLOCK + threadIdx.x)) + blockIdx.x * NCOLUNASPERBLOCK + threadIdx.x ];
        
        __syncthreads();
        
		for (i = 0; i < NLINHASPERBLOCK; i++) {
	    	soma += s_a[threadIdx.y][i] * s_b[i][threadIdx.x];
	    }
	}

    c[(NLINHAS * linha) + coluna] = soma;
}

int main(){
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;
    int size = NLINHAS * NCOLUNAS * sizeof(int);
    int i;

    cudaMalloc((void **) &d_a, size);
    cudaMalloc((void **) &d_b, size);
    cudaMalloc((void **) &d_c, size);

    a = (int *)malloc(size);
    b = (int *)malloc(size);
    c = (int *)malloc(size);

    for(i = 0; i < NLINHAS*NCOLUNAS; i++){
        a[i] = b[i] = i;
        c[i] = 0;
    }

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    dim3 tthreads = dim3(32, 32, 1);
    dim3 tbloco = dim3(NLINHAS / NLINHASPERBLOCK, NCOLUNAS / NCOLUNASPERBLOCK,1);
    //vector_mul<<< (N + (THREADS_PER_BLOCK-1)) / THREADS_PER_BLOCK, THREADS_PER_BLOCK >>>(d_a, d_b, d_c);

    vector_mul<<< tbloco, tthreads >>>(d_a, d_b, d_c);

    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    printf("c[0] = %d\n",c[0]);
    printf("c[%d] = %d\n", (NLINHAS*NCOLUNAS)-1, c[(NLINHAS*NCOLUNAS)-1]);

    free(a); free(b); free(c);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
