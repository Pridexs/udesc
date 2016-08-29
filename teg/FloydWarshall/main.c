/***********************************************************************
* Alexandre Maros & Aurelio Grott                                      *
* 2015/1 - UDESC                                                       *
*                                                                      *
* Compilar: gcc main.c -o main                                         *
* Algoritmo de Floyd-Warshall                                          *
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void floyds();
void criaMatAdjacenteComPeso(int **matAdj, int *nVerticesTot, FILE *arquivo);
int min(int a, int b);

#define tamMax 200
#define INFINITO 500

int main()
{
    int opcao;

    do
    {
        printf("> TEG\n");
        printf("1. Floyd-Warshall.\n"
            "0. Sair.\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            floyds();
            break;

        default:
            break;
        }
    } while (opcao != 0);

    return 0;
}


void floyds() {
    int k, i, j; //Contadores
    int nVertices;
    int **matAdj;

    matAdj = (int**)calloc(tamMax, sizeof(int*));

    for (i = 0; i < tamMax; i++)
    {
        for (j = 0; j < tamMax; j++)
        {
            matAdj[i] = (int*)calloc(tamMax, sizeof(int));
        }
    }

    //Iniciar como infinito
    // Se nao tiver conexao, adicionar inifinito.
    for (i = 0; i < tamMax; i++)
    {
        for (j = 0; j < tamMax; j++)
        {
            if (i != j)
                matAdj[i][j] = INFINITO;
        }
    }


    FILE *fp = fopen("grafo.txt", "r");
    criaMatAdjacenteComPeso(matAdj, &nVertices, fp);
    
    printf("Matriz 0:\n");
    for (i = 0; i < nVertices; i++)
    {
        for (j = 0; j < nVertices; j++)
        {
            if (matAdj[i][j] >= INFINITO)
                printf("%4s", "INF");
            else 
                printf("%4d", matAdj[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int ***matrizes;
    
    //Alocação nos 3 niveis
    matrizes = (int***) malloc(sizeof(int**) * (nVertices+1));
    for (i = 0; i <= nVertices; i++) 
    {
        matrizes[i] = (int**) calloc(sizeof(int*), nVertices);
    } 

    for (i = 0; i <= nVertices; i++) 
    {
        for (j = 0; j <= nVertices; j++)
        {
            matrizes[i][j] = (int*) calloc(sizeof(int), nVertices);
        }
    }
    
    //Inicializando a primeira matriz
    for (i = 0; i < nVertices; i++) {
        for (j = 0; j < nVertices; j++){
                matrizes[0][i][j] = matAdj[i][j];
            }
    }
    
    //Criando as matrizes
    for (k = 1; k <= nVertices; k++)
    {
        for (i = 0; i < nVertices; i++)
        {
            for (j = 0; j < nVertices; j++)
            {
                matrizes[k][i][j] = min(matrizes[k-1][i][j], matrizes[k-1][i][k-1] + matrizes[k-1][k-1][j]);
            }
        }
    }

    // Imprimindo as matrizes
    for (k = 1; k <= nVertices; k++)
    {
        printf("Matriz %d\n", k);
        for (i = 0; i < nVertices; i++)
        {
            for (j = 0; j < nVertices; j++) 
            {
                if (matrizes[k][i][j] >= INFINITO)
                    printf("%4s", "INF");
                else
                    printf("%4d", matrizes[k][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

}

int min(int a, int b)
{
    if (a < b)
        return a;   
    return b;
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
                    //Se a aresta for = INFINITO, quer dizer que nao a nenhuma aresta ainda
                    //entao basta apenas substituir
                    if (matAdj[vertAtual][num] >= INFINITO)
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
