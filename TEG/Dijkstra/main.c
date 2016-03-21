/***********************************************************************
* Alexandre Maros & Aurelio Grott                                      *
* 2015/1 - UDESC                                                       *
*                                                                      *
* Compilar: gcc main.c -o main Lista.c                                 *
* Algoritmo de Dijkstra                                                *
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lista.h"

#define tamMax 200
#define INF 1000000000

void mostra_inteiro(void *info);
void criaMatAdjacenteComPeso(int **matAdj, int *nVerticesTot, FILE *arquivo);
void dijkstra();
int extrairMin(int **matAdj, int *dist, int *visitados, int nVertices);

int main()
{
	int opcao;

	do
	{
		printf("> TEG\n");
		printf("1. Dijkstra.\n"
			"0. Sair.\n");
		scanf("%d", &opcao);
		switch (opcao)
		{
		case 1:
			dijkstra();
			break;

		default:
			break;
		}
	} while (opcao != 0);

	return 0;
}

void dijkstra()
{
	int **matAdj;
	int *dist, *visitados;
	int i, j, nVertices;
    int vertInicial;

    printf("Digite o vertice inicial: ");
    scanf("%d", &vertInicial);

	//Lista de Precendentes
	Lista precedentes;
    inicializa_lista(&precedentes, sizeof(Lista));

	// Alocacao para a matAdj[tamMax][tamMax]
	matAdj = (int**)calloc(tamMax, sizeof(int*));
	for (i = 0; i < tamMax; i++)
	{
		for (j = 0; j < tamMax; j++)
		{
			matAdj[i] = (int*)calloc(tamMax, sizeof(int));
		}
	}

	// Inicia a matriz com -1
	for (i = 0; i < tamMax; i++)
	{
		for (j = 0; j < tamMax; j++)
		{
			if (i != j)
                matAdj[i][j] = -1;
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
	criaMatAdjacenteComPeso(matAdj, &nVertices, fp);

	//Alocacao da matriz que guarda as distancias
	dist = (int*)malloc(sizeof(int) * nVertices);
	for (i = 0; i < nVertices; i++)
		dist[i] = INF;

    //Alocacao visitados
    visitados = (int*)calloc(nVertices, sizeof(int));

	//Insere nListas para marcar os precedentes.
	for (i = 0; i < nVertices; i++)
	{
		Lista l;
		inicializa_lista(&l, sizeof(int));
		insereNoFim(&precedentes, &l);
	}

    // Distancia do proprio vertice inicial e sempre 0
    dist[vertInicial] = 0;

    for (i = 0; i < nVertices; i++)
    {	
		//Extrai o vertice com a menor distancia e que ainda nao foi visitado
        int u = extrairMin(matAdj, dist, visitados, nVertices);

		//Marca como visitado
        visitados[u] = 1;

		//For de 0 at[e nVertices (Numero maximo que dijkstra roda)
        for (j = 0; j < nVertices; j++)
        {
            if (!visitados[j] && matAdj[u][j] != -1 && dist[u] != INF && dist[u]+matAdj[u][j] <= dist[j])
            {
				//Se a distancia do no inicial, ate o no atual + ate o no de menor distancia 
				//For igual, adicione-o na lista tambem como um no precedente
                if (dist[u]+matAdj[u][j] == dist[j])
                {
                    Lista l;
                    removeNaPosicao(&precedentes, &l, j);
                    insereNoFim(&l, &u);
                    insereNaPosicao(&precedentes, &l, j);
                }
				//Se nao for, retire todos os nos precedentes, e coloque o novo no precedente.
                else
                {
                    Lista l;
                    removeNaPosicao(&precedentes, &l, j);
                    limpa_lista(&l);
                    insereNoFim(&l, &u);
                    insereNaPosicao(&precedentes, &l, j);
                }
				//Atualize a distancia
                dist[j] = dist[u] + matAdj[u][j];
            }
        }

    }
	//Imprime
    printf("VERTICES   : ");
    for (i = 0; i < nVertices; i++)
        printf("%d  ", i);
    printf("\n");
    printf("ESTIMATIVAS: ");
    for (i = 0; i < nVertices; i++)
        printf("%d  ", dist[i]);
    printf("\n");
    printf("PRECEDENTES:\n");
    for (i = 0; i < nVertices; i++)
    {
        printf("Precedente(s) vertice %d: ", i);
        Lista l;
        leNaPosicao(&precedentes, &l, i);
        mostra_lista(l, mostra_inteiro);
        printf("\n");
    }

    printf("\nDistancias:\n");
    for (i = 0; i < nVertices; i++)
    {
        printf("Vertice %d ao vertice %d: %d\n", vertInicial, i, dist[i]);
    }

	printf("\n");

}


// Funcao para extrair o no que tem menor distancia
int extrairMin(int **matAdj, int *dist, int *visitados, int nVertices)
{
    int min = INF;
    int min_index;
    int v;
    for(v = 0; v < nVertices; v++)
    {
        if(!visitados[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}


void criaMatAdjacenteComPeso(int **matAdj, int *nVerticesTot, FILE *arquivo)
{
	// Essa string eh usada para guardar temporarimente as ligacoes de um determinado vertice
	char buffer[200];
	// Guardar o vertice atual
	int vertAtual;
	//int que recebera o valor do vertice que vertAtual esta sendo ligado
	int num;
	int nVertices = 0;

	// Temp e usada para guardar a ligacao temporaria, offset e usado na hora do sscanf para controlar a leitura
	int temp, offset, i, j, peso;

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
					// Aponta o ponteiro para o proximo numero
					pBuffer += offset;

					//Caso um vertice tenha mais de uma aresta saindo dele na mesma direcao
					//Guarde apenas o vertice de menor peso
					//Se a aresta for negativa, quer dizer que nao a nenhuma aresta ainda
					//entao basta apenas substituir,
					if (matAdj[vertAtual][num] < 0)
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
	}
}

void mostra_inteiro(void *info)
{
    int *n = (int*) info;
    printf("%d ", *n);
}
