/***********************************************************************
* Alexandre Maros & Aurelio Grott                                      *
* 2015/1 - UDESC                                                       *
*                                                                      *
* Compilar: gcc main.c -o main                                         *
* Algoritmo de Floyd-Warshall                                          *
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 9999

int fordFulkerson(int **matAdj, int nVertices, int nArestas, int noFonte, int noDestino);
int **criaMatAdjacenteComPeso(int *nVerticesTot, int *nArestasTot, int *noFonte, int *noDestino, FILE *arquivo);
int dfs(int i, int v_pai, int vFinal, int **matAdj, int nVerticesTot, int *visitados, int *pai);
int min(int a, int b);

int main()
{
    int **matAdj;
    int nVertices, nArestas, noFonte, noDestino;
    int i, j;

    printf("> Trabalho Final\n");


    FILE *arquivo = fopen("grafo.txt", "r");
    matAdj = criaMatAdjacenteComPeso(&nVertices, &nArestas, &noFonte, &noDestino, arquivo);

    /*
    * Impressao Matriz
    */
    printf("Matriz:\n");
    for (i = 0; i < nVertices; i++)
    {
        for (j = 0; j < nVertices; j++)
        {
            printf("%4d", matAdj[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int fluxoMaximo = fordFulkerson(matAdj, nVertices, nArestas, noFonte, noDestino);
    printf("Fluxo Maximo: %d\n", fluxoMaximo);

    return 0;
}

/*
* Retorna Fluxo-Maximo
*/
int fordFulkerson(int **matAdj, int nVertices, int nArestas, int noFonte, int noDestino)
{
    int i,j,k;

    int *visitados = (int*) calloc(nVertices, sizeof(int));
    int *pai = (int*) calloc(nVertices, sizeof(int));

    printf("noFonte %d noDestino %d\n", noFonte, noDestino);

    /*
    * Copia a Matriz de Adjacencia
    */
    int **matRes;
    matRes = (int**)calloc(nVertices, sizeof(int*));
    for (i = 0; i < nVertices; i++)
    {
        matRes[i] = (int*)calloc(nVertices, sizeof(int));
    }
    for (i = 0; i < nVertices; i++)
    {
        for (j = 0; j < nVertices; j++) 
        {
            matRes[i][j] = matAdj[i][j];
        }
    }

    int fluxo_maximo = 0;

    // Enquanto tiver um caminho entre o vertice inicial e o final.
    while(dfs(noFonte, noFonte, noDestino, matRes, nVertices, visitados, pai))
    {
        int fluxo_caminho = INF;
        int v, u; // contador

        // Faz o caminho contrario, buscando o menor fluxo maximo para o caminho
        for (v = noDestino; v != noFonte; v = pai[v])
        {
            u = pai[v];
            fluxo_caminho = min(fluxo_caminho, matRes[u][v]);
        }

        printf("FluxoCamino: %d\n", fluxo_caminho);

        // Atualiza o grafo com o fluxo encontrado
        for (v = noDestino; v != noFonte; v = pai[v])
        {
            u = pai[v];
            matRes[u][v] -= fluxo_caminho;
            matRes[v][u] += fluxo_caminho;
        }

        fluxo_maximo += fluxo_caminho;

        // Zera vetor visitados, e pai.
        memset(visitados, 0, sizeof(int)*nVertices);
        memset(pai, 0, sizeof(int)*nVertices);
    }

    printf("Matriz Residual:\n");
    for (i = 0; i < nVertices; i++)
    {
        printf("%d:  ", i);
        for (j = 0; j < nVertices; j++)
        {
            printf("%3d ", matRes[i][j]);
        }
        printf("\n");
    }

    /*
    * Libera memoria de matRes
    */ 
    for (i = 0; i < nVertices; i++)
    {
        free(matRes[i]);
    }
    free(matRes);

    return fluxo_maximo;

}

int min(int a, int b)
{
    if (a > b)
        return b;
    return a;
}

// Retorna 1 se tiver caminho
// Tambem popula o vetor de pai para guardar o caminho.
int dfs(int i, int v_pai, int vFinal, int **matAdj, int nVerticesTot, int *visitados, int *pai)
{
    int j;
    // Marca que visitou o vertice
    visitados[i] = 1;
    // Pai do vertice i eh o vertice passado. (Passado por parametro)
    pai[i] = v_pai;
    // De 0 ate o numero de vertices total do grafico
    for (j = 0; j < nVerticesTot; j++)
    {
        // Se ele nao visitou o vertice j e ah uma ligcao entre o vertice i e o vertice j execute a recursao
        if (!visitados[j] && matAdj[i][j] > 0)
        {
            dfs(j, i, vFinal, matAdj, nVerticesTot, visitados, pai);
        }
    }

    // Se visitados[vFinal] == 1 ele visitou.
    return visitados[vFinal];
}

int **criaMatAdjacenteComPeso(int *nVerticesTot, int *nArestasTot, int *noFonte, int *noDestino, FILE *arquivo)
{
    // Essa string eh usada para guardar temporarimente as ligacoes de um determinado vertice
    char buffer[200];
    // Guardar o vertice atual
    int vertAtual;
    //int que recebera o valor do vertice que vertAtual esta sendo ligado
    int num;
    int nVertices = 0;
    int nArestas = 0;

    int **matAdj;

    // Temp e usada para guardar a ligacao temporaria
    int temp, i, j, peso;

    // Se falhou abrir o arquivo
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!");
        return NULL;
    }
    else
    {
        // Ponteiro para o buffer
        char *pBuffer = buffer;

        /*
        * Leitura 1a Linha - Número de Vértices
        */
        fgets(buffer, sizeof(buffer), arquivo);
        sscanf(pBuffer, "%d", &nVertices);
        *nVerticesTot = nVertices;

        /*
        * Inicializacao da Matriz
        */
        matAdj = (int**)calloc(nVertices, sizeof(int*));
        for (i = 0; i < nVertices; i++)
        {
            for (j = 0; j < nVertices; j++)
            {
                matAdj[i] = (int*)calloc(nVertices, sizeof(int));
            }
        }

        /*
        * Leitura 2a Linha - NoFonte NoDestino NumeroConxoes
        */
        fgets(buffer, sizeof(buffer), arquivo);
        sscanf(pBuffer, "%d %d %d", &i, &j, &nArestas);
        *nArestasTot = nArestas;
        // Deceremnta os vertice em 1, pois estamos entrando com range [1-10] e C trabalha com [0-9]
        *noFonte = i-1;
        *noDestino = j-1;

        /*
        * Leitura das nArestas
        */
        while (fgets(buffer, sizeof(buffer), arquivo))
        {
            // Le os vertices e o peso e os atribui na matriz de adjacencia.
            if (sscanf(pBuffer, "%d %d %d", &i, &j, &peso) == 3) 
            {
                // Deceremnta os vertice em 1, pois estamos entrando com range [1-10] e C trabalha com [0-9]
                i--;
                j--;
                matAdj[i][j] = peso;
                matAdj[j][i] = peso;
            }
        }
    }

    fclose(arquivo);
    return matAdj;
}
