#include <stdio.h>
#include <stdlib.h>


int main(){
    int *vetor;
    int tam, qual, qtd = 0, i, atual;

    printf("Informe a quantidade de inteiros: ");
    scanf("%d", &tam);

    vetor = calloc(sizeof(int), tam);

    printf("Informe quais sao os %d inteiros:\n", tam);

    for(i = 0; i < tam; i++){
        scanf("%d", &atual);
        vetor[atual]++;
    }

    printf("Informe o inteiro a ser contado: ");
    scanf("%d", &qual);

    printf(" O inteiro %d foi encontrado %d vezes!\n", qual, vetor[qual]);

    return 0;
}