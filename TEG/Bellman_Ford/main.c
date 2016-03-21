/***********************************************************************
* Alexandre Maros & Aurelio Grott                                      *
* 2015/1 - UDESC                                                       *
*                                                                      *
* Compilar: gcc main.c -o main Lista.c                                 *
* Algoritmo de Bellman-Ford                                            *
************************************************************************/

#include <stdio.h>
#include "Lista.h"

#define INF 10000
#define tamMax 200

typedef struct {
    int origem, destino, peso;
} Aresta;

void mostra_inteiro(void *info);
int compara_info(void *info1, void*info2);
void printDistancias(int chosenOne, int nVertices, int *distancia);
void criaMatAdjacenteComPeso(int** matAdj, int* nVertices, int *nArestas, FILE *arquivo);
void bellman_ford(int chosenOne, int nVertices, int *distancia, int nArestas);
void bellman();


Aresta *arestas;//vetor de arestas
Lista *precedentes;//vetor de precedentes, uma lista de precedentes para cada nó


int main()
{
	int opcao;

	do
	{
		printf("> TEG\n");
		printf("1. Bellman-Ford.\n"
			"0. Sair.\n");
		scanf("%d", &opcao);
		switch (opcao)
		{
		case 1:
			bellman();
			break;

		default:
			break;
		}
	} while (opcao != 0);

	return 0;
}


void bellman()
{
    int i, j;
    int nArestas;
    int nVertices;
    int **matAdj;
    int *distancia; /* d[i] é a distância mínima do nó escolhido ao nó i */

    // Alocacao para a matAdj[tamMax][tamMax]
	matAdj = (int**)calloc(tamMax, sizeof(int*));
	for (i = 0; i < tamMax; i++)
	{
		for (j = 0; j < tamMax; j++)
		{
			matAdj[i] = (int*)calloc(tamMax, sizeof(int));
		}
	}
	// Inicia a matriz com INF
	for (i = 0; i < tamMax; i++)
	{
		for (j = 0; j < tamMax; j++)
		{
			if (i != j)
                matAdj[i][j] = INF;
            else
                matAdj[i][j] = 0;
		}
	}
	// Fim da alocao para a matriz
	FILE *fp = fopen("grafo.txt", "r");
	if (fp == NULL) {
		printf("ERRO AO ABRIR GRAFO!\n");
		exit(2);
	}
	//Carrega a matriz adjacente
	criaMatAdjacenteComPeso(matAdj, &nVertices, &nArestas, fp);

	//Alocacao da matriz que guarda as distancias
	distancia = (int*)malloc(sizeof(int) * nVertices);
	//alocacao do vetor de arestas


	arestas = (Aresta*)malloc(sizeof(Aresta)*2*nArestas);
    nArestas = 0;

    precedentes = (Lista*)malloc(sizeof(Lista)*nVertices);
/*IMPRESSAO DA MATRIZ
    for(i=0;i<nVertices;i++){
        for(j=0;j<nVertices;j++){
            printf("%d ", matAdj[i][j]);
        }
        printf("\n");
    }
*/
    for (i = 0; i < nVertices; i++)
    {
        inicializa_lista(&precedentes[i], sizeof(int));
        for (j = 0; j < nVertices; j++)
        {
            if (matAdj[i][j] != INF)
            {
                arestas[nArestas].origem = i;
                arestas[nArestas].destino = j;
                arestas[nArestas].peso = matAdj[i][j];
                nArestas++;
            }
        }
    }
    fclose(fp);
    /* print origem -> destino com peso
    for(i=0;i<nArestas;i++){
        printf("%d -%d-> %d\n", arestas[i].origem,arestas[i].peso,arestas[i].destino);
    }
    */
    /* printDist(); */
    int chosenOne;
    printf("Executar Bellman-Ford a partir do vertice: \n");
    scanf("%d", &chosenOne);
    bellman_ford(chosenOne, nVertices, distancia, nArestas);/*chama funcao bellman_ford com parametros*/

    printDistancias(chosenOne,nVertices, distancia);//imprime as distancias e precedentes
}

void bellman_ford(int chosenOne, int nVertices, int* distancia, int nArestas) {
    int i, j;

    for (i = 0; i < nVertices; ++i)
        distancia[i] = INF;//inicializa as distâncias com infinito

    distancia[chosenOne] = 0;//exceto a do vertice escolhido como inicial, que permanece em 0

    for (i = 0; i < nVertices - 1; ++i)//executa laço nVertices-1 vezes
        for (j = 0; j < nArestas; ++j)//analisando todas as arestas
        {
            if (distancia[arestas[j].origem] + arestas[j].peso < distancia[arestas[j].destino] && arestas[j].destino != chosenOne)
            /*caso a distancia do vertice de origem + o peso da aresta em questão seja menor do que a distancia armazenada no
              vertice de destino, ocorre a atualizacao no vetor de distancia E a atualizacao na lista de precedentes deste mesmo nó*/
            {
                distancia[arestas[j].destino] = distancia[arestas[j].origem] + arestas[j].peso;
                limpa_lista(&precedentes[(arestas[j].destino)]);
                insereEmOrdem(&precedentes[(arestas[j].destino)], &arestas[j].origem, compara_info);
            }
            else if(distancia[arestas[j].origem] + arestas[j].peso == distancia[arestas[j].destino])
            {
                insereEmOrdem(&precedentes[(arestas[j].destino)], &arestas[j].origem, compara_info);
            }
        }
}

void criaMatAdjacenteComPeso(int **matAdj, int *nVerticesTot, int *nArestasTot, FILE *arquivo)
{
	// Essa string eh usada para guardar temporarimente as ligacoes de um determinado vertice
	char buffer[200];
	// Guardar o vertice atual
	int vertAtual;
	//int que recebera o valor do vertice que vertAtual esta sendo ligado
	int num;
	int nVertices = 0;
	int nArestas=0;

	// Temp e usada para guardar a ligacao temporaria, offset e usado na hora do sscanf para controlar a leitura
	int offset, peso;

	// Se falhou abrir o arquivo
	if (arquivo == NULL)
	{
		printf("Erro ao abrir arquivo!");
		return;
	}
	else
	{
		// Enquanto nao chegar no final do arquivo
		while (fgets(buffer, sizeof(buffer), arquivo))
		{
			// Ponteiro para o buffer, para poder mover o ponteiro na hora de converter para inteiros
			char *pBuffer = buffer;

			// Le o vertice a ser analisado. Numero antes do ":" no arquivo corresponde a linha da matriz
			// sscanf retorna quantos parametros foram lidos, usamos esse if pra verificar se a linha
			// nao estava vazia.
			if (sscanf(pBuffer, "%d:%n", &vertAtual, &offset) == 1)
			{
				pBuffer += offset;
				// Le numero por numero ate chegar ao final da linha
				while (sscanf(pBuffer, " {%d,%d}%n", &num, &peso, &offset) == 2)
				{
				    nArestas++;
					// Aponta o ponteiro para o proximo numero
					pBuffer += offset;

					//Caso um vertice tenha mais de uma aresta saindo dele na mesma direcao
					//Guarde apenas o vertice de menor peso
					//Se a aresta for infinita, quer dizer que nao a nenhuma aresta ainda
					//entao basta apenas substituir,
					if (matAdj[vertAtual][num] == INF)
					{
						matAdj[vertAtual][num] = peso;

					}
					else
					{
						//Caso haja uma aresta, pegue o menor.
						if (matAdj[vertAtual][num] > peso)
						{
							matAdj[vertAtual][num] = peso;

						}
					}

				}
				//aumenta o numero de vertice
				nVertices++;
			}

		}
		*nVerticesTot = nVertices;
		*nArestasTot = nArestas;
	}
}

void printDistancias(int chosenOne,int nVertices, int *distancia) {
    int i;

    printf("Distancias de %d:\n", chosenOne);

    for (i = 0; i < nVertices; ++i)
        printf("para %d\t", i);
    printf("\n");

    for (i = 0; i < nVertices; ++i)
        printf("%d\t", distancia[i]);

    printf("\nPRECEDENTES:\n");
    for (i = 0; i < nVertices; i++)
    {
        printf("Precedente(s) vertice %d: ", i);
        if(i == chosenOne)
            printf(" \t\n");
        else{
            mostra_lista(precedentes[i], mostra_inteiro);
            printf("\n");
        }
    }
    printf("\n\n");
}

void mostra_inteiro(void *info)
{
    int *n = (int*) info;
    printf("%d ", *n);
}

int compara_info(void *info1, void*info2)
{
    return 0;
    if(*(int*)info2 < *(int*)info1)
        return -1;
    if(*(int*)info2 == *(int*)info1)
        return 0;
    if(*(int*)info2 > *(int*)info1)
        return 1;
}
