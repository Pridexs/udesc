// Alexandre Maros & Nadyan S. Pscheidt
// CAL - Trabalho 2
//
// Como usar
// ./main <estrutura>
//
// Exemplo (quero executar vector use)
// ./main vector
//
// Tags:
// vector, tree, hash

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <map>
#include <unordered_map>

using namespace std;

void executarVector();
void executarArvore();
void executarHash();

FILE *fvector, *ftree, *fhash;

clock_t start, clockEnd;

double tTime;

int main(int argv, char *argc[])
{
    vector<string> args;

    for (int i = 1; i < argv; i++) {
        args.push_back(string(argc[i]));
    }

    long i;

    srand(time(NULL));

    if (find(args.begin(), args.end(), "vector") != args.end() )
    {
        fvector = fopen("csvs/vector.csv", "w");
        //fprintf(fvector, "ordem,tempo_25k,tempo_50k,tempo_75k,tempo_100k,tempo_1kk\n");
        executarVector();
    }
    else if (find(args.begin(), args.end(), "tree") != args.end()) 
    {
        executarArvore();
    }
    else if (find(args.begin(), args.end(), "hash") != args.end())
    {
        executarHash();
    }

}

void executarVector()
{
    //vector<pair<string, string> > nomes;
    vector<pair<unsigned, string> > nomes;
    unsigned int ordem;
    int nElementos, nPesquisas, sizeNomes;
    int i,j;
    string e1, e2;

    scanf("%d", &nElementos);
    for (i = 0; i < nElementos; i++)
    {
        cin >> ordem >> e1 >> e2;
        //nomes.pusb_back(make_pair(e1, e2));
        nomes.push_back(make_pair(ordem, e1+"-"+e2));
        //cout << nomes[i] << endl;
    }

    start = clock();

    scanf("%d", &nPesquisas);
    sizeNomes = nomes.size();
    for (i = 0; i < nPesquisas; i++)
    {

        cin >> e1 >> e2;
        e1 += "-"+e2;
        for (j = 0; j < sizeNomes; j++ )
        {
            if (nomes[j].second == e1)
            {
                cout << nomes[j].first << endl;
                break;
            }
        }
    }

    clockEnd = clock();
    tTime = double(clockEnd - start) / (double) CLOCKS_PER_SEC;
    printf("Tempo: %lf\n", tTime);
}

void executarArvore()
{
    //vector<pair<string, string> > nomes;
    map<string, int> nomes;
    unsigned int ordem;
    int nElementos, nPesquisas, sizeNomes;
    int i,j;
    string e1, e2;

    scanf("%d", &nElementos);
    for (i = 0; i < nElementos; i++)
    {
        cin >> ordem >> e1 >> e2;
        nomes[e1+"-"+e2] = ordem;
    }

    start = clock();

    scanf("%d", &nPesquisas);
    sizeNomes = nomes.size();
    for (i = 0; i < nPesquisas; i++)
    {

        cin >> e1 >> e2;
        e1 += "-"+e2;
        cout << nomes.find(e1)->second << endl;
    }

    clockEnd = clock();
    tTime = double(clockEnd - start) / (double) CLOCKS_PER_SEC;
    printf("Tempo: %lf\n", tTime);
}

void executarHash()
{
    //vector<pair<string, string> > nomes;
    unordered_map<string, int> nomes;
    unsigned int ordem;
    int nElementos, nPesquisas, sizeNomes;
    int i,j;
    string e1, e2;

    scanf("%d", &nElementos);
    for (i = 0; i < nElementos; i++)
    {
        cin >> ordem >> e1 >> e2;
        nomes[e1+"-"+e2] = ordem;
    }

    start = clock();

    scanf("%d", &nPesquisas);
    sizeNomes = nomes.size();
    for (i = 0; i < nPesquisas; i++)
    {

        cin >> e1 >> e2;
        e1 += "-"+e2;
        cout << nomes.find(e1)->second << endl;
    }

    clockEnd = clock();
    tTime = double(clockEnd - start) / (double) CLOCKS_PER_SEC;
    printf("Tempo: %lf\n", tTime);
}