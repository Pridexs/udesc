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
// bubble   - bubble sort
// merge    - merge sort
// quick    - quick sort
// insert   - insert sort

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
#include "../include/bucketsort.h"
#include "../include/bubblesort.h"
#include "../include/insertsort.h"
#include "../include/quicksort.h"
#include "../include/mergesort.h"

using namespace std;

void inicializarCrescente();
void inicializarDecrescente();
void inicializarAleatorio();
void inicializarAleatorioComElemento100kk();

void executarHeapsort(char const *ordem);
void executarCountingsort(char const *ordem);
void executarBucketsort(char const *ordem);
void executarBubblesort(char const *ordem);
void executarInsertsort(char const *ordem);
void executarQuicksort(char const *ordem);
void executarMergesort(char const *ordem);

// Global para facil acesso
int arr25k[25000], arr50k[50000], arr75k[75000];
int arr100k[100000], arr1kk[1000000];

FILE *fheap, *fcounting, *fbucket, *fbubble, *finsert, *fquick, *fmerge;

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
        fprintf(fheap, "ordem,tempo_25k,tempo_50k,tempo_75k,tempo_100k,tempo_1kk\n");
    }

    if (find(args.begin(), args.end(), "counting") != args.end()) {
         fcounting = fopen("csvs/counting.csv", "w");
         fprintf(fcounting, "ordem,tempo_25k,tempo_50k,tempo_75k,tempo_100k,tempo_1kk\n");
    }

    if (find(args.begin(), args.end(), "bucket") != args.end()) {
        fbucket = fopen("csvs/bucket.csv", "w");
        fprintf(fbucket, "ordem,tempo_25k,tempo_50k,tempo_75k,tempo_100k,tempo_1kk\n");
    }

    if (find(args.begin(), args.end(), "bubble") != args.end()) {
        fbubble = fopen("csvs/bubble.csv", "w");
        fprintf(fbubble, "ordem,tempo_25k,tempo_50k,tempo_75k,tempo_100k\n");
    }

    if (find(args.begin(), args.end(), "insert") != args.end()) {
        finsert = fopen("csvs/insert.csv", "w");
        fprintf(finsert, "ordem,tempo_25k,tempo_50k,tempo_75k,tempo_100k,tempo_1kk\n");
    }

    if (find(args.begin(), args.end(), "quick") != args.end()) {
        fquick = fopen("csvs/quick.csv", "w");
        fprintf(fquick, "ordem,tempo_25k,tempo_50k,tempo_75k,tempo_100k\n");
    }

    if (find(args.begin(), args.end(), "merge") != args.end()) {
        fmerge = fopen("csvs/merge.csv", "w");
        fprintf(fmerge, "ordem,tempo_25k,tempo_50k,tempo_75k,tempo_100k,tempo_1kk\n");
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
        inicializarCrescente();
        executarBucketsort("crescente");

        inicializarDecrescente();
        executarBucketsort("decrescente");

        inicializarAleatorio();
        executarBucketsort("aleatorio");

        inicializarAleatorioComElemento100kk();
        executarBucketsort("aleatorio100kk");
    }

    if (find(args.begin(), args.end(), "bubble") != args.end())
    {
        inicializarCrescente();
        executarBubblesort("crescente");

        inicializarDecrescente();
        executarBubblesort("decrescente");

        inicializarAleatorio();
        executarBubblesort("aleatorio");

        inicializarAleatorioComElemento100kk();
        executarBubblesort("aleatorio100kk");
    }

    if (find(args.begin(), args.end(), "insert") != args.end())
    {
        inicializarCrescente();
        executarInsertsort("crescente");

        inicializarDecrescente();
        executarInsertsort("decrescente");

        inicializarAleatorio();
        executarInsertsort("aleatorio");

        inicializarAleatorioComElemento100kk();
        executarInsertsort("aleatorio100kk");
    }

    if (find(args.begin(), args.end(), "quick") != args.end())
    {
        inicializarCrescente();
        executarQuicksort("crescente");

        inicializarDecrescente();
        executarQuicksort("decrescente");

        inicializarAleatorio();
        executarQuicksort("aleatorio");

        inicializarAleatorioComElemento100kk();
        executarQuicksort("aleatorio100kk");
    }

    if (find(args.begin(), args.end(), "merge") != args.end())
    {
        inicializarCrescente();
        executarMergesort("crescente");

        inicializarDecrescente();
        executarMergesort("decrescente");

        inicializarAleatorio();
        executarMergesort("aleatorio");

        inicializarAleatorioComElemento100kk();
        executarMergesort("aleatorio100kk");
    }

}

void executarHeapsort(char const *ordem)
{
    printf("Iniciando heapsort em ordem %s...\n", ordem);
    fprintf(fheap, "%s,", ordem);
    
    // 25k heap
    start = clock();
    heapSort(arr25k, 25000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("heapSort 25k: %lf segundos\n", tTime);
    fprintf(fheap, "%lf,", tTime);

    // 50k heap
    start = clock();
    heapSort(arr50k, 50000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("heapSort 50k: %lf segundos\n", tTime);
    fprintf(fheap, "%lf,", tTime);

    // 75k heap
    start = clock();
    heapSort(arr75k, 75000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("heapSort 75k: %lf segundos\n", tTime);
    fprintf(fheap, "%lf,", tTime);

    // 100k heap
    start = clock();
    heapSort(arr100k, 100000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("heapSort 100k: %lf segundos\n", tTime);
    fprintf(fheap, "%lf,", tTime);

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
    fprintf(fcounting, "%s,", ordem);
    
    // 25k heap
    start = clock();
    countingSort(arr25k, 25000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("countingSort 25k: %lf segundos\n", tTime);
    fprintf(fcounting, "%lf,", tTime);

    // 50k heap
    start = clock();
    countingSort(arr50k, 50000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("countingSort 50k: %lf segundos\n", tTime);
    fprintf(fcounting, "%lf,", tTime);

    // 75k heap
    start = clock();
    countingSort(arr75k, 75000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("countingSort 75k: %lf segundos\n", tTime);
    fprintf(fcounting, "%lf,", tTime);

    // 100k heap
    start = clock();
    countingSort(arr100k, 100000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("countingSort 100k: %lf segundos\n", tTime);
    fprintf(fcounting, "%lf,", tTime);

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
    printf("Iniciando bucket em ordem %s...\n", ordem);
    fprintf(fbucket, "%s,", ordem);
    
    // 25k heap
    start = clock();
    bucketSort(arr25k, 25000, 10000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("bucketSort 25k: %lf segundos\n", tTime);
    fprintf(fbucket, "%lf,", tTime);

    // 50k heap
    start = clock();
    bucketSort(arr50k, 50000, 20000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("bucketSort 50k: %lf segundos\n", tTime);
    fprintf(fbucket, "%lf,", tTime);

    // 75k heap
    start = clock();
    bucketSort(arr75k, 75000, 35000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("bucketSort 75k: %lf segundos\n", tTime);
    fprintf(fbucket, "%lf,", tTime);

    // 100k heap
    start = clock();
    bucketSort(arr100k, 100000, 50000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("bucketSort 100k: %lf segundos\n", tTime);
    fprintf(fbucket, "%lf,", tTime);

    // 1kk heap
    start = clock();
    bucketSort(arr1kk, 1000000, 300000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("bucketSort 1kk: %lf segundos\n\n", tTime);
    fprintf(fbucket, "%lf\n", tTime);
}

void executarBubblesort(char const *ordem)
{
    printf("Iniciando bubblesort em ordem %s...\n", ordem);
    fprintf(fbubble, "%s,", ordem);
    
    // 25k heap
    start = clock();
    bubbleSort(arr25k, 25000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("bubbleSort 25k: %lf segundos\n", tTime);
    fprintf(fbubble, "%lf,", tTime);

    // 50k heap
    start = clock();
    bubbleSort(arr50k, 50000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("bubbleSort 50k: %lf segundos\n", tTime);
    fprintf(fbubble, "%lf,", tTime);

    // 75k heap
    start = clock();
    bubbleSort(arr75k, 75000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("bubbleSort 75k: %lf segundos\n", tTime);
    fprintf(fbubble, "%lf,", tTime);

    // 100k heap
    start = clock();
    bubbleSort(arr100k, 100000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("bubbleSort 100k: %lf segundos\n", tTime);
    fprintf(fbubble, "%lf\n", tTime);
	/*
    // 1kk heap
    start = clock();
    bubbleSort(arr1kk, 1000000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("bubbleSort 1kk: %lf segundos\n\n", tTime);
    fprintf(fbubble, "%lf\n", tTime);*/
}

void executarInsertsort(char const *ordem)
{
    printf("Iniciando insertsort em ordem %s...\n", ordem);
    fprintf(finsert, "%s,", ordem);
    
    // 25k heap
    start = clock();
    insertSort(arr25k, 25000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("insertSort 25k: %lf segundos\n", tTime);
    fprintf(finsert, "%lf,", tTime);

    // 50k heap
    start = clock();
    insertSort(arr50k, 50000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("insertSort 50k: %lf segundos\n", tTime);
    fprintf(finsert, "%lf,", tTime);

    // 75k heap
    start = clock();
    insertSort(arr75k, 75000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("insertSort 75k: %lf segundos\n", tTime);
    fprintf(finsert, "%lf,", tTime);

    // 100k heap
    start = clock();
    insertSort(arr100k, 100000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("insertSort 100k: %lf segundos\n", tTime);
    fprintf(finsert, "%lf,", tTime);

    // 1kk heap
    start = clock();
    insertSort(arr1kk, 1000000);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("insertSort 1kk: %lf segundos\n\n", tTime);
    fprintf(finsert, "%lf\n", tTime);
}

void executarQuicksort(char const *ordem)
{
    /* CSV fica zoado, mas os dados estao certos */
    int posicao;

    printf("Iniciando quicksort em ordem %s...\n", ordem);
    fprintf(fquick, "%s,", ordem);
    

    /* com pivo na primeira posicao */
    // 25k quick pivo 0
    start = clock();
    quickSort(arr25k, 0, 25000-1, 0);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("quickSort 25k (pivo 0): %lf segundos\n", tTime);
    fprintf(fquick, "%lf,", tTime);


    // 50k pivo 0
    start = clock();
    quickSort(arr50k, 0, 50000-1, 0);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("quickSort 50k (pivo 0): %lf segundos\n", tTime);
    fprintf(fquick, "%lf,", tTime);


    // 75k pivo 0
    start = clock();
    quickSort(arr75k, 0, 75000-1, 0);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("quickSort 75k (pivo 0): %lf segundos\n", tTime);
    fprintf(fquick, "%lf,", tTime);


    // 100k pivo 0
    start = clock();
    quickSort(arr100k, 0, 100000-1, 0);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("quickSort 100k (pivo 0): %lf segundos\n", tTime);
    fprintf(fquick, "%lf\n", tTime);

    /*
    // 1kk pivo 0
    start = clock();
    quickSort(arr1kk, 0, 1000000-1, 0);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("quickSort 1kk (pivo 0): %lf segundos\n", tTime);
    fprintf(fquick, "%lf\n", tTime);
    */


    /* Pivo na posicao aleatoria */
    fprintf(fquick, "pivRdm,tempo_25k,tempo_50k,tempo_75k,tempo_100k\n");

    // 25k pivo na posicao aleatoria
    posicao = rand() % 24999;
    start = clock();
    quickSort(arr25k, 0, 25000-1, posicao);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("quickSort 25k (pivo aleat.): %lf segundos\n", tTime);
    fprintf(fquick, "%lf,", tTime);


    // 50k com pivo na posicao aleatoria
    posicao = rand() % 49999;
    start = clock();
    quickSort(arr50k, 0, 50000-1, posicao);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("quickSort 50k (pivo aleat.): %lf segundos\n", tTime);
    fprintf(fquick, "%lf,", tTime);


    // 75k com pivo na posicao aleatoria
    posicao = rand() % 74999;
    start = clock();
    quickSort(arr75k, 0, 75000-1, posicao);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("quickSort 75k (pivo aleat.): %lf segundos\n", tTime);
    fprintf(fquick, "%lf,", tTime);


    // 100k com pivo na posicao aleatoria
    posicao = rand() % 99999;
    start = clock();
    quickSort(arr100k, 0, 100000-1, posicao);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("quickSort 100k (pivo aleat.): %lf segundos\n\n", tTime);
    fprintf(fquick, "%lf\n", tTime);

    /*
    // 1kk com pivo na posicao aleatoria
    posicao = rand() % (1000000-1);
    start = clock();
    quickSort(arr1kk, 0, 1000000-1, posicao);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("quickSort 1kk (pivo aleat.): %lf segundos\n", tTime);
    fprintf(fquick, "%lf\n", tTime);
    */
}

void executarMergesort(char const *ordem)
{
    printf("Iniciando mergesort em ordem %s...\n", ordem);
    fprintf(fmerge, "%s,", ordem);
    
    // 25k heap
    start = clock();
    mergeSort(arr25k, 0, 25000-1);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("mergeSort 25k: %lf segundos\n", tTime);
    fprintf(fmerge, "%lf,", tTime);

    // 50k heap
    start = clock();
    mergeSort(arr50k, 0, 50000-1);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("mergeSort 50k: %lf segundos\n", tTime);
    fprintf(fmerge, "%lf,", tTime);

    // 75k heap
    start = clock();
    mergeSort(arr75k, 0, 75000-1);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("mergeSort 75k: %lf segundos\n", tTime);
    fprintf(fmerge, "%lf,", tTime);

    // 100k heap
    start = clock();
    mergeSort(arr100k, 0, 100000-1);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("mergeSort 100k: %lf segundos\n", tTime);
    fprintf(fmerge, "%lf,", tTime);

    // 1kk heap
    start = clock();
    mergeSort(arr1kk, 0, 1000000-1);
    end = clock();

    tTime = double(end - start) / (double) CLOCKS_PER_SEC;
    printf("mergeSort 1kk: %lf segundos\n\n", tTime);
    fprintf(fmerge, "%lf\n", tTime);
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
