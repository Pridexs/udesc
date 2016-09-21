#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

#include "bubblesort.h"

void bubbleSort(int arr[], int n){
    int i, j, aux;
    //int r;
    
    for(i = n-1; i >= 1; i--){  
        for(j = 0; j < i ; j++){
            if(arr[j] > arr[j+1]){
                aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
        }
    }

    //for(r = 0; r < 10; ++r){
        //printf("%d\n",vetor[r]);
    //}
}
