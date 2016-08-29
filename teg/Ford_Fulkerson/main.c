/***********************************************************************
* Alexandre Maros & Aurelio Grott                                      *
* 2015/1 - UDESC                                                       *
*                                                                      *
* Compilar: gcc main.c -o main                                         *
* Algoritmo de Ford-Fulkerson                                          *
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fords();
void criaMatAdjacenteComPeso(int **matAdj, FILE *arquivo);
int dfs(int i, int v_pai, int vFinal, int **matAdj, int nVerticesTot, int *visitados, int *pai);
int contaNumeroVertices(FILE *arq);
int min(int a, int b);

#define INF 2000000

int main()
{
    int opcao;

    do
    {
        printf("> TEG\n");
        printf("1. Ford-Fulkerson.\n"
            "0. Sair.\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            fords();
            break;

        default:
            break;
        }
    } while (opcao != 0);

    return 0;
}

void fords()
{
    int k, i, j; //Contadores
    int nVertices;
    int **matAdj;


    //Abre arquivo
    FILE *fp = fopen("grafo.txt", "r");

    //Conta numero de vertices
    nVertices = contaNumeroVertices(fp);

    //Alocacao da matriz
    matAdj = (int**)calloc(nVertices, sizeof(int*));
    for (i = 0; i < nVertices; i++)
    {
        for (j = 0; j < nVertices; j++)
        {
            matAdj[i] = (int*)calloc(nVertices, sizeof(int));
        }
    }

    criaMatAdjacenteComPeso(matAdj, fp);
    fclose(fp);

    printf("Matriz Inicial:\n");
    for (i = 0; i < nVertices; i++)
    {
        printf("%d:  ", i);
        for (j = 0; j < nVertices; j++)
        {
            printf("%3d ", matAdj[i][j]);
        }
        printf("\n");
    }

    
    // Obs: Da pra ver qual vertice tem apenas arestas saindo dele
    // e dar assign como vertice inicial.
    // E achar vertice que nao tem nenhum vertice saindo e dar assign
    // como vertice final.

    int vert_inicial, vert_final;
    printf("Entre com o vertice inicial e final: ");
    scanf("%d %d", &vert_inicial, &vert_final);

    int *visitados = (int*) calloc(nVertices, sizeof(int));
    int *pai = (int*) calloc(nVertices, sizeof(int));

    int fluxo_maximo = 0;

    // Enquanto tiver um caminho entre o vertice inicial e o final.
    while(dfs(vert_inicial, 0, vert_final, matAdj, nVertices, visitados, pai))
    {
        int fluxo_caminho = INF;
        int v, u; // contador

        // Faz o caminho contrario, buscando o menor fluxo maximo para o caminho
        for (v = vert_final; v != vert_inicial; v = pai[v])
        {
            u = pai[v];
            fluxo_caminho = min(fluxo_caminho, matAdj[u][v]);
        }

        // Atualiza o grafo com o fluxo encontrado
        for (v = vert_final; v != vert_inicial; v = pai[v])
        {
            u = pai[v];
            matAdj[u][v] -= fluxo_caminho;
            matAdj[v][u] += fluxo_caminho;
        }

        fluxo_maximo += fluxo_caminho;

        // Zera vetor visitados, e pai.
        memset(visitados, 0, sizeof(int)*nVertices);
        memset(pai, 0, sizeof(int)*nVertices);
    }

    // Imprime a matriz de residuos.
    printf("Matriz Residual:\n");
    for (i = 0; i < nVertices; i++)
    {
        printf("%d:  ", i);
        for (j = 0; j < nVertices; j++)
        {
            printf("%3d ", matAdj[i][j]);
        }
        printf("\n");
    }
    //Imprime o fluxo maximo
    printf("Fluxo maximo: %d\n\n", fluxo_maximo);

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

void criaMatAdjacenteComPeso(int **matAdj, FILE *arquivo)
{
    //Retorna o ponteiro para o comeco do arquivo
    fseek(arquivo, 0, SEEK_SET);
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

                    //Caso aja arestar paralelas, some seus pesos.
                    //Se a aresta for = 0, quer dizer que nao a nenhuma aresta ainda
                    //entao basta apenas substituir
                    if (matAdj[vertAtual][num] == 0)
                    {
                        matAdj[vertAtual][num] = peso;
                    }
                    else
                    {
                        // Caso aja uma aresta paralela, adicione seu peso a aresta ja adicionada.
                        matAdj[vertAtual][num] += peso;
                    }

                }
                //aumenta o numero de vertice
                nVertices++;
            }

        }
    }
}

int contaNumeroVertices(FILE *arquivo)
{

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return 0;
    }

    int nVertices = 0, vertAtual;
    char buffer[200];
    while (fgets(buffer, sizeof(buffer), arquivo))
    {
        // Ponteiro para o buffer, para poder mover o ponteiro na hora de converter para inteiros
        char *pBuffer = buffer;

        // Se ele conseguiu ler 'X:' entao adicione um no contador de vertices.
        if (sscanf(pBuffer, "%d:", &vertAtual) == 1)
        {
            nVertices++;
        }
    }
    return nVertices;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}