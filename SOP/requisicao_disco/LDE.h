#ifndef LISTADUPLAMENTEENCADEADA_H_INCLUDED
#define LISTADUPLAMENTEENCADEADA_H_INCLUDED

#include <stdlib.h>

#define ERRO_ALOCACAO -1
#define ERRO_LISTA_VAZIA -2
#define ERRO_POSICAO_INVALIDA -3

typedef struct elementoDuplo {
    void *info;
    struct elementoDuplo *proximo, *anterior;
} EleDuplo;

typedef struct {
    size_t tamInfo;
    EleDuplo *cabeca;
} LDE;

void inicializa_lista(LDE *l, size_t t);
void mostra_lista(LDE l, void (*mostra_info)(void *));
void mostra_lista_invertida(LDE l, void (*mostra_info)(void *));
int insereNoInicio(LDE *l, void *info);
int insereNoFim(LDE *l, void *info);
int insereNaPosicao(LDE *l, void *info, int pos);
int insereEmOrdem(LDE *l, void *info, int (*compara_info)(void *, void *));
int removeDoInicio(LDE *l, void *info);
int removeNaPosicao(LDE *l, void *info, int pos);
int removeInfo(LDE *l, void *info);
int modificaNaPosicao(LDE *l, void *info, int pos);
int leNaPosicao(LDE *l, void *info, int pos);

EleDuplo *aloca_elemento(size_t t, void *info);

/*
* Funcoes Especiais para o algoritmo de SOP (req-disco)
*/

EleDuplo* verificaJuncao(LDE *l, EleDuplo *atual);
unsigned max(unsigned a, unsigned b);

/*
* Fim Funcoes Especiais
*/

#endif // LISTADUPLAMENTEENCADEADA_H_INCLUDED
