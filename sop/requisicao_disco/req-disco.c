/*
*   Nomes: Alexandre Maros & Tiago Heinrich
*   
*   Primeiramente a requisicao vai ser inserida em ordem na lista de requisicoes.
*   Apos feito a insercao, o algoritmo entrara em um loop para verificar se pode unir
*   duas requisicoes.
*   
*   Algumas das funcoes especiais para o algoritmo estao localizadas em LDE.c
*
*   Compilar: gcc req-disco.c -o req-disco LDE.c
*   Executar: ./req-disco
*   
*   req-disco.c
*       main:
*           Le e monta requisica.
*           Chama insereEmOrdem.
*
*   LDE.c
*       insereEmOrdem:
*           Procura a posicao que deve inserir
*           Caso posicao for igual a 1, chama insereNoInicio
*           Chama insereNaPosicao
*       
*       insereNaPosicao:
*           Insere a requisicao na posicao passada
*           Chama verificaJuncao ate ela retornar NULL (Nao houve nenhuma juncao realizada)
*           Retorna sucesso.
*
*       insereNoInicio:
*           Insere a requisicao no inicio
*           Chama verifiaJuncao ate ela retornar NULL (Nao houve nenhuma juncao realizada)
*           Retorna sucesso.
*   
*/


#include "LDE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcoes para utilizar na Lista Duplamente Encadeada
int compara_requisicao(void *a, void *b);
void mostra_requisicao(void *info);

struct requisicao {
    unsigned int blocoInicial, nBlocos;
    char tipo[2];
};

int main()
{
    int i;
    int bI, nB;
    char tp[2];

    // Inicializacao da Lista
    LDE listaRequisicoes;
    inicializa_lista(&listaRequisicoes, sizeof(struct requisicao));

    while (scanf("%u %u %s", &bI, &nB, tp) != EOF) {
        struct requisicao r;
        strcpy(r.tipo, tp);
        r.blocoInicial = bI;
        r.nBlocos = nB;

        // Chama insereEmOrdem. 
        // Dentro da funcao, ha a verificao se pode ocorrer juncoes com os elementos vizinhos.
        insereEmOrdem(&listaRequisicoes, &r, compara_requisicao);
    }

    printf("Fila:\n");
    mostra_lista(listaRequisicoes, mostra_requisicao);

    return 0;
}

// Funcao para imprimir elementos da Lista
void mostra_requisicao(void *info)
{
    struct requisicao *p = (struct requisicao*)info;
    
    printf("%u %u %s\n", p->blocoInicial, p->nBlocos, p->tipo);
}

// Funcao utilizada para a insercao em ordem
int compara_requisicao(void *a, void *b)
{
    struct requisicao *infoA = (struct requisicao*) a;
    struct requisicao *infoB = (struct requisicao*) b;

    if ( infoA->blocoInicial == infoB->blocoInicial ) 
        return 0;
    else if ( infoA->blocoInicial > infoB->blocoInicial )
        return 1;
    return -1;
}