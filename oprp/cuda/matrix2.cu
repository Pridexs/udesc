#include <stdio.h>

__global__ void vector_mul(int *a, int *b, int *c){
	int i, j, soma = 0;

	
	int coluna = blockIdx.x * blockDim.x + threadIdx.x;
	int linha =  blockIdx.y * blockDim.y + threadIdx.x;
	//int index = blockIdx.x * blockDim.x + threadIdx.x;

	for (i = 0; i < 2048; i++) {
		soma += a[(2048 * linha + i] * b[2048 * i + coluna];		
	}

	// ((sizeof(int)+N) * linha) + (sizeof(int) * coluna)
	c[(2048 * linha) + coluna] = soma;
}

#define N (2048*2048)
#define THREADS_PER_BLOCK 512

int main(){
	int *a, *b, *c;
	int *d_a, *d_b, *d_c;
	int size = N * sizeof(int);

	cudaMalloc((void **) &d_a, size);
	cudaMalloc((void **) &d_b, size);
	cudaMalloc((void **) &d_c, size);

	a = (int *)malloc(size);
	b = (int *)malloc(size);
	c = (int *)malloc(size);

	for(int i = 0; i < N; i++){
		a[i] = b[i] = i;
		c[i] = 0;
	}

	cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);


	dim3 tbloco = dim3(
	vector_mul<<< (N + (THREADS_PER_BLOCK-1)) / THREADS_PER_BLOCK, THREADS_PER_BLOCK >>>(d_a, d_b, d_c);
	cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
	printf("c[0] = %d\n",c[0]);
	printf("c[%d] = %d\n", N-1, c[N-1]);

	free(a); free(b); free(c);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);

	return 0;
}
