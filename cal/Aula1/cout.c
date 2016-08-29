// Feito por Nadyan S. P.

#include <stdio.h>

int main(){
    int *vetor;
    int tam, qual, qtd = 0, i;

    printf("\n\n    Informe a quantidade de inteiros: ");
    scanf("%d", &tam);

    vetor = malloc(sizeof(int) * tam);

    printf("\n    Informe quais sao os %d inteiros:\n", tam);

    for(i = 0; i < tam; i++){
        scanf("%d", &vetor[i]);
    }

    printf("\n\n    Informe o inteiro a ser contado: ");
    scanf("%d", &qual);

    for(i = 0; i < tam; i++){
        if(vetor[i] == qual){
            qtd++;
        }
    }

    printf("\n\n    O inteiro %d foi encontrado %d vezes!\n\n", qual, qtd);

    return 0;
}