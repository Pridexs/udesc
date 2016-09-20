#include <cstdlib>
#include <cstdio>

#include "countingsort.h"

int maximum(int * array, int size){

    int curr = 0;
    int max = 0;

    for(curr = 0; curr < size; curr++) {
        if(array[curr] > max) {
            max = array[curr];
        }
    }

    return max+1;
}

void countingSort(int * array, int size) {

    int curr = 0;
    int max = maximum(array, size);
    int *counting_array;
    counting_array = (int*) calloc(max, sizeof(int));

    for(curr = 0; curr < size; curr ++) {
        counting_array[array[curr]]++;
    }

    int num = 0;
    curr = 0;

    while(curr < size){
        while(counting_array[num] > 0) {
            array[curr] = num;
            counting_array[num]--;
            curr++;
            if(curr > size) {
                break;
            }
        }
        num++;
    }

    free(counting_array);
}