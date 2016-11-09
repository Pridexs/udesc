#include <stdio.h>

#define NLINHAS 4096
#define NCOLUNAS 4096
#define THREADS_PER_BLOCK 1024
#define

__global__ void vector_mul(int *a, int *b, int *c) {
    int i, j, z, soma = 0;

    int coluna = blockIdx.x * blockDim.x + threadIdx.x;
    int linha =  blockIdx.y * blockDim.y + threadIdx.y;

	// nColunasPerBlock should be equal to nLinhasPerBlock
	// for now at least
	int nColunasPerBlock = (NCOLUNAS/blockDim.x);
	int nLinhasPerBlock = (NLINHAS/blockDim.y);

    __shared__ int s_a[nLinhasPerBlock][nColunasPerBlock];
    __shared__ int s_b[nLinhasPerBlock][nColunasPerBlock];

    // carregar pra memoria compartilhada da GPU

	// blockDim.x DEVEM SER IGUAIS blockDim.y
    // Copia Matriz
	int nColunasPerBlock = (NCOLUNAS/blockDim.x);
	for (z = 0; z < blockDim.x; z++) {
		for (i = 0; i < nColunasPerBlock; i++) {
			s_a[ blockIdx.y * nLinhasPerBlock  ][ z * nColunasPerBlock + i ] = a
		}

		// cudaMemcpy(&d_a[0], s_a,
	    // 	(NLINHAS/blockDim.y) * NCOLUNAS * sizeof(int), cudaMemcpyDeviceToDevice);
		//
	    // // Copia Matriz B
	    // for(i = 0; i < NLINHAS; i++) {
	    //     cudaMemcpy(&d_b[ (i * NCOLUNAS * sizeof(int)) + (blockDim.x * sizeof(int) * (NCOLUNAS/blockDim.x)) ],
	    //     s_b, sizeof(int) * (NCOLUNAS/blockDim.x), cudaMemcpyDeviceToDevice);
	    // }


	    __syncthreads();

		for (i = 0; i < nLinhasPerBlock; i++) {
	    	soma += s_a[i] * s_b[i];
	    }
	}

    c[(NLINHAS * linha) + coluna] = soma;
}

int main(){
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;
    int size = NLINHAS * NCOLUNAS * sizeof(int);

    cudaMalloc((void **) &d_a, size);
    cudaMalloc((void **) &d_b, size);
    cudaMalloc((void **) &d_c, size);

    a = (int *)malloc(size);
    b = (int *)malloc(size);
    c = (int *)malloc(size);

    for(int i = 0; i < NLINHAS*NCOLUNAS; i++){
        a[i] = b[i] = i;
        c[i] = 0;
    }

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    dim3 tthreads = dim3(32, 32, 1);
    dim3 tbloco = dim3(1,1,1);
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
