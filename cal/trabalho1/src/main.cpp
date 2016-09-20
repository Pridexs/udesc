// Alexandre Maros & Nadyan S. Pscheidt
// CAL - Trabalho 1
//
// Como usar
// ./main <algoritmos de sort>
//
// Exemplo (quero executar heap e bucket sort apenas)
// ./main heap bucket
//
// Tags:
// heap     - heap sort
// bucket   - bucket sort
// counting - counting sort

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>

#include "../include/heapsort.h"
#include "../include/countingsort.h"


using namespace std;

void inicializarCrescente();
void inicializarDecrescente();
void inicializarAleatorio();
void inicializarAleatorioComElemento100kk();

void executarHeapsort(char const *ordem);
void executarCountingsort(char const *ordem);
void executarBucketsort(char const *ordem);

// Global para facil acesso
int arr25k[25000], arr50k[50000], arr75k[75000];
int arr100k[100000], arr1kk[1000000];

FILE *fheap, *fcounting, *fbucket;

clock_t start, end;

double tTime;

int main(int argv, char *argc[])
{
    vector<string> args;

    for (int i = 1; i < argv; i++) {
        args.push_back(string(argc[i]));
    }

    long i;

    srand(time(NULL));

    // Abrir apenas os arquivos necessarios
    if (find(args.begin(), args.end(), "heap") != args.end() ) {
        fheap = fopen("csvs/heap.csv", "w");
        fprintf(fheap, "ordem;tempo_25k;tempo_50k;tempo_75k;tempo_100k;tempo_1kk\n");
    }

    if (find(args.begin(), args.end(), "counting") != args.end()) {
         fcounting = fopen("csvs/counting.csv", "w");
         fprintf(fcounting, "ordem;tempo_25k;tempo_50k;tempo_75k;tempo_100k;tempo_1kk\n");
    }

    if (find(args.begin(), args.end(), "bucket") != args.end()) {
        fbucket = fopen("csvs/bucket.csv", "w");
        fprintf(fbucket, "ordem;tempo_25k;tempo_50k;tempo_75k;tempo_100k;tempo_1kk\n");
    }

    // Ordenar
    if (find(args.begin(), args.end(), "heap") != args.end() )
    {
        inicializarCrescente();
        executarHeapsort("crescente");

        inicializarDecrescente();
        executarHeapsort("decrescente");

        inicializarAleatorio();
        executarHeapsort("aleatorio");

        inicializarAleatorioComElemento100kk();
        executarHeapsort("aleatorio100kk");
        
    }

    if (find(args.begin(), args.end(), "counting") != args.end())
    {
        inicializarCrescente();
        executarCountingsort("crescente");

        inicializarDecrescente();
        executarCountingsort("decrescente");

        inicializarAleatorio();
        executarCountingsort("aleatorio");

        inicializarAleatorioComElemento100kk();
        executarCountingsort("aleatorio100kk");
    }

    if (find(args.begin(), args.end(), "bucket") != args.end())
    {
        printf("Iniciando bucket sort em ordem crescente...\n");
    }

}

void executarHeapsort(char const *ordem)
{
    printf("Iniciando heapsort em ordem %s...\n", ordem);
    fprintf(fheap, "%s;", ordem);
    
    // 25k heap
    start = clock();
    heapSort(arr25k, 25000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("heapSort 25k: %lf segundos\n", tTime);
    fprintf(fheap, "%lf;", tTime);

    // 50k heap
    start = clock();
    heapSort(arr50k, 50000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("heapSort 50k: %lf segundos\n", tTime);
    fprintf(fheap, "%lf;", tTime);

    // 75k heap
    start = clock();
    heapSort(arr75k, 75000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("heapSort 75k: %lf segundos\n", tTime);
    fprintf(fheap, "%lf;", tTime);

    // 100k heap
    start = clock();
    heapSort(arr100k, 100000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("heapSort 100k: %lf segundos\n", tTime);
    fprintf(fheap, "%lf;", tTime);

    // 1kk heap
    start = clock();
    heapSort(arr1kk, 1000000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("heapSort 1kk: %lf segundos\n\n", tTime);
    fprintf(fheap, "%lf\n", tTime);
}

void executarCountingsort(char const *ordem)
{
    printf("Iniciando counting em ordem %s...\n", ordem);
    fprintf(fcounting, "%s;", ordem);
    
    // 25k heap
    start = clock();
    countingSort(arr25k, 25000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("countingSort 25k: %lf segundos\n", tTime);
    fprintf(fcounting, "%lf;", tTime);

    // 50k heap
    start = clock();
    countingSort(arr50k, 50000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("countingSort 50k: %lf segundos\n", tTime);
    fprintf(fcounting, "%lf;", tTime);

    // 75k heap
    start = clock();
    countingSort(arr75k, 75000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("countingSort 75k: %lf segundos\n", tTime);
    fprintf(fcounting, "%lf;", tTime);

    // 100k heap
    start = clock();
    countingSort(arr100k, 100000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("countingSort 100k: %lf segundos\n", tTime);
    fprintf(fcounting, "%lf;", tTime);

    // 1kk heap
    start = clock();
    countingSort(arr1kk, 1000000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("countingSort 1kk: %lf segundos\n\n", tTime);
    fprintf(fcounting, "%lf\n", tTime);
}

void executarBucketsort(char const *ordem)
{
    
}

void inicializarCrescente()
{
    long i;
    // (1) em ordem crescente
    for (i = 0; i < 25000; i++) {
        arr25k[i] = i;
    }

    for (i = 0; i < 50000; i++) {
        arr50k[i] = i;
    }

    for (i = 0; i < 75000; i++) {
        arr75k[i] = i;
    }

    for (i = 0; i < 100000; i++) {
        arr100k[i] = i;
    }

    for (i = 0; i < 1000000; i++) {
        arr1kk[i] = i;
    }
}

void inicializarDecrescente()
{
    long i;
    // (2) em ordem decrescente
    for (i = 25000-1; i >= 0; i--) {
        arr25k[i] = i;
    }

    for (i = 50000-1; i >= 0; i--) {
        arr50k[i] = i;
    }

    for (i = 75000-1; i >= 0; i--) {
        arr75k[i] = i;
    }

    for (i = 100000-1; i >= 0; i--) {
        arr100k[i] = i;
    }

    for (i = 1000000-1; i >= 0; i--) {
        arr1kk[i] = i;
    }
}

void inicializarAleatorio()
{
    long i;
    // (3) em ordem aleatoria
    for (i = 0; i < 25000; i++) {
        arr25k[i] = rand() % 25000;
    }

    for (i = 0; i < 50000; i++) {
        arr50k[i] = rand() % 50000;
    }

    for (i = 0; i < 75000; i++) {
        arr75k[i] = rand() % 75000;
    }

    for (i = 0; i < 100000; i++) {
        arr100k[i] = rand() % 100000;
    }

    for (i = 0; i < 1000000; i++) {
        arr1kk[i] = rand() % 1000000;
    }
}

void inicializarAleatorioComElemento100kk()
{
    long i;

    // (4) em ordem aleatoria mas com um elemento 100.000.000 (em qualquer posição)
    for (i = 0; i < 25000; i++) {
        arr25k[i] = rand() % 25000;
    }
    arr25k[rand()%25000] = 100000000;

    for (i = 0; i < 50000; i++) {
        arr50k[i] = rand() % 50000;
    }
    arr50k[rand()%50000] = 100000000;

    for (i = 0; i < 75000; i++) {
        arr75k[i] = rand() % 75000;
    }
    arr75k[rand()%75000] = 100000000;

    for (i = 0; i < 100000; i++) {
        arr100k[i] = rand() % 100000;
    }
    arr100k[rand()%100000] = 100000000;

    for (i = 0; i < 1000000; i++) {
        arr1kk[i] = rand() % 1000000;
    }
    arr1kk[rand()%1000000] = 100000000;
}