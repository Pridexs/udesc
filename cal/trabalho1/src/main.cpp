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

#include "../include/heapsort.h"

using namespace std;

int main(int argv, char *argc[])
{
    vector<string> args;

    for (int i = 1; i < argv; i++) {
        args.push_back(string(argc[i]));
    }

    int arr25k[25000], arr50k[50000], arr75k[75000];
    int arr100k[100000], arr1kk[1000000];

    long i;

    srand(time(NULL));

    FILE *fheap, *fcounting, *fbucket;

    fheap       = fopen("csvs/heap.csv", "w");
    fcounting   = fopen("csvs/counting.csv", "w");
    fbucket     = fopen("csvs/bucket.csv", "w");

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

    // Ordenar
    if (find(args.begin(), args.end(), "heap") != args.end() )
    {
        printf("Iniciando heapsort em ordem crescente...\n");
    }

    if (find(args.begin(), args.end(), "counting") != args.end())
    {
        printf("Iniciando counting sort em ordem crescente...\n");
    }

    if (find(args.begin(), args.end(), "bucket") != args.end())
    {
        printf("Iniciando bucket sort em ordem crescente...\n");
    }


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

    // Ordenar
    if (find(args.begin(), args.end(), "heap") != args.end() )
    {
        printf("Iniciando heapsort em ordem decrescente...\n");
    }

    if (find(args.begin(), args.end(), "counting") != args.end())
    {
        printf("Iniciando counting sort em ordem decrescente...\n");
    }

    if (find(args.begin(), args.end(), "bucket") != args.end())
    {
        printf("Iniciando bucket sort em ordem decrescente...\n");
    }


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

    // Ordenar
    if (find(args.begin(), args.end(), "heap") != args.end() )
    {
        printf("Iniciando heapsort em ordem aleatoria...\n");
    }

    if (find(args.begin(), args.end(), "counting") != args.end())
    {
        printf("Iniciando counting sort em ordem aleatoria...\n");
    }

    if (find(args.begin(), args.end(), "bucket") != args.end())
    {
        printf("Iniciando bucket sort em ordem aleatoria...\n");
    }

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

    // Ordenar
    if (find(args.begin(), args.end(), "heap") != args.end() )
    {
        printf("Iniciando heapsort em ordem aleatoria + elemento de 100.000.000...\n");
    }

    if (find(args.begin(), args.end(), "counting") != args.end())
    {
        printf("Iniciando counting sort em ordem aleatoria + elemento de 100.000.000...\n");
    }

    if (find(args.begin(), args.end(), "bucket") != args.end())
    {
        printf("Iniciando bucket sort em ordem aleatoria + elemento de 100.000.000...\n");
    }

}