// Alexandre Maros & Nadyan S. Pscheidt
// CAL - Trabalho 1

#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

#include "mergesort.h"

void mergeSort(int arr[], int inicio, int fim){
    int i, j, k, metadeTamanho, *vetorTemp;  

    if(inicio == fim) return;

    metadeTamanho = (inicio + fim) / 2;
    mergeSort(arr, inicio, metadeTamanho);
    mergeSort(arr, metadeTamanho+1, fim);

    i = inicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (int *) malloc(sizeof(int) * (fim - inicio + 1));

    while(i < metadeTamanho + 1 || j < fim + 1){
        if(i == metadeTamanho + 1){
            vetorTemp[k] = arr[j];
            j++;
            k++;
        }else{
            if(j == fim + 1){
                vetorTemp[k] = arr[i];
                i++;
                k++;
            }else{
                if(arr[i] < arr[j]){
                    vetorTemp[k] = arr[i];
                    i++;
                    k++;
                }else{
                    vetorTemp[k] = arr[j];
                    j++;
                    k++;
                }
            }   
        }   
    }

    for(i = inicio; i <= fim; i++){
        arr[i] = vetorTemp[i - inicio];
    }
    free(vetorTemp);
}
