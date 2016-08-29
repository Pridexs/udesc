/***********************************************************************
* Alexandre Maros & Aurelio Grott                                      *
* 2015/1 - UDESC                                                       *
*                                                                      *
* Compilar: gcc main.c -o main                                         *
* Centro da Arvore: Algoritmo desenvolvido como exercicio              *
* para a aula de Teoria dos Grafos.                                    *
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamMax 200

void criaMatAdjacente(int **matAdj, int *nVerticesTot, FILE *arquivo);
void dfs(int i, int **matAdj, int nVerticesTot, int *visitados, int *path, int *maxPath);
void achaCentro();

int main()
{
    int opcao;

    do
    {
        printf("> TEG\n");
        printf("1. Achar centro.\n"
            "0. Sair.\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            achaCentro();
            break;

        default:
            break;
        }
    } while (opcao != 0);

    return 0;
}

void achaCentro()
{
    int **matAdj;
    /*variáveis para armazenar o comprimento dos caminhos a partir de cada vertice*/
    int path=0, maxPath=0;
    int visitados[tamMax];
    memset(visitados, 0, sizeof(visitados));
    int i, j, nVertices;
    /*variável para armazenar o menor caminho máximo percorrido por algum vertice do grafo*/
    int menorCaminhoMaximo = tamMax;

    /*for para alocar a matriz adjacente, a qual será usada para prática do DFS*/
    matAdj = (int**)calloc(tamMax, sizeof(int*));
    for (i = 0; i < tamMax; i++)
    {
        for (j = 0; j < tamMax; j++)
        {
            matAdj[i] = (int*)calloc(tamMax, sizeof(int));
        }
    }

    FILE *fp = fopen("grafo.txt", "r");

    criaMatAdjacente(matAdj, &nVertices, fp);

    /* Impressao matriz.
    // COMECO IMPRESSAO MATRIZ
    for (i = 0; i < nVertices; i++){
        for (j = 0; j < nVertices; j++){
            printf("%d ", matAdj[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    // FIM IMPRESSAO MATRIZ
    */
    /*vetor para guardar os caminhos maximos de cada vertice*/
    int osCaminhoTudo[nVertices];
    memset(osCaminhoTudo, 0, sizeof(osCaminhoTudo));
    for(i=0;i<nVertices;i++)
    {
        /*ALTERAÇÃO NO DFS: para a medição dos caminhos, passamos os ponteiros das variáveis globais path e maxPath*/
        dfs(i,matAdj,nVertices,visitados,&path, &maxPath);
        /*atribuição do caminho maximo do vertice i ao vetor*/
        osCaminhoTudo[i]=maxPath;

        /*printf para verificação de todos os caminhos maximos*/
        printf("excentricidade do vertice %d = %d\n", i, osCaminhoTudo[i]);

        /*comparação clássica de menor - maior para saber qual a menor excentricidade do grafo*/
        if(maxPath < menorCaminhoMaximo)
            menorCaminhoMaximo = maxPath;
        /*redefinição das variáveis para uma outra sequencia de funções que definirão o valor da excentricidade do proximo
        vertice a ser analisado*/
        path=0;
        maxPath=0;
        memset(visitados, 0, sizeof(visitados));
    }
    /* IMPRESSÃO DOS RESULTADOS*/
    printf("\n\nCentro do grafo eh dado pelo(s) vertice(s):\n");
    for(i=0;i<nVertices;i++)
    {
        if(osCaminhoTudo[i] == menorCaminhoMaximo)
        {
                printf(" %d", i);
        }
    }
    printf("\n com excentricidade %d\n", menorCaminhoMaximo);

}


void criaMatAdjacente(int **matAdj, int *nVerticesTot, FILE *arquivo)
{
    // Essa string eh usada para guardar temporarimente as ligacoes de um determinado vertice
    char buffer[200];
    // Guardar o vertice atual
    int vertAtual;
    //int que recebera o valor do vertice que vertAtual esta sendo ligado
    int num;
    int nVertices = 0;

    // Temp e usada para guardar a ligacao temporaria, offset e usado na hora do sscanf para controlar a leitura
    int temp, offset, i, j;

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
            if(sscanf(pBuffer, "%d:%n", &vertAtual, &offset) == 1)
            {
                pBuffer += offset;
                // Le numero por numero ate chegar ao final da linha
                while (sscanf(pBuffer, " %d%n", &num, &offset) == 1)
                {
                    // Aponta o ponteiro para o proximo numero
                    pBuffer += offset;

                    // Adiciona na posicao [verticeAtual][numeroLido] +1, indicando que ha uma aresta ali
                    matAdj[vertAtual][num]++;
                }
                //aumenta o numero de vertice
                nVertices++;
            }

        }
        *nVerticesTot = nVertices;
    }
}



void dfs(int i, int **matAdj, int nVerticesTot, int *visitados, int *path, int *maxPath)
{
    int j;
    // Marca que visitou o vertice
    visitados[i] = 1;
    // De 0 ate o numero de vertices total do grafico
    for (j = 0; j < nVerticesTot; j++)
    {
        // Se ele nao visitou o vertice j e ah uma ligcao entre o vertice i e o vertice j execute a recursao
        if (!visitados[j] && matAdj[i][j] == 1)
        {
            /*para cada vertice que é possivel alcançar a partir do vertice i (enviado na funçao achaCentro())
            a variável global path é somada +1, funcionando a principio como um contador de arestas*/
            *path += 1;
            dfs(j, matAdj, nVerticesTot, visitados, path, maxPath);
        }
    }
    /*cada vértice possui vários caminhos, porém a para garantir a excentricidade precisamos da comparação abaixo*/
    if((*path)>(*maxPath))
        *maxPath = *path;
    /*quando chegamos em um nó folha, e o voltamos para uma outra possibilidade, devemos subtrair 1 aresta de nossa contagem,
    caso contrario estaríamos passando duas vezes na mesma aresta */
    *path -=1;
}
