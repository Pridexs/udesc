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
#include <functional>

using namespace std;

void executarVector();
void executarArvore();
void executarHash();

clock_t start, clockEnd;

double tTime;

class CustomHash
{
public:
    size_t operator() (string const& key) const
    {
        size_t hash = 0;
        
        size_t nSize = key.size();

        for (int i = 0; i < nSize; i++)
        {
            hash += key[i] * (i+1);
        }

        return hash;
    }
};

class ComparadorStrings
{
public:
    bool operator() (string const& n1, string const& n2) const
    {
        return n1 == n2;
    }
};

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
    vector<pair<unsigned, string> > nomes;
    unsigned int ordem;
    int nElementos, nPesquisas, sizeNomes;
    int i,j;
    string e1, e2;

    scanf("%d", &nElementos);
    for (i = 0; i < nElementos; i++)
    {
        cin >> ordem >> e1 >> e2;
        nomes.push_back(make_pair(ordem, e1+"-"+e2));
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
    // unordered_map com hash custom
    unordered_map<string, int, CustomHash, ComparadorStrings> nomes;
    
    // unordered_map com hash do c++
    //unordered_map<string, int> nomes;
    
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