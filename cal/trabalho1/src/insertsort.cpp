#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

#include "insertsort.h"

void insertSort(int arr[], int n){
	int i, j, atual;

	for (i = 1; i < n; i++)
	{
		atual = arr[i];
		j = i - 1;

		while ((j >= 0) && (atual < arr[j]))
		{
			arr[j + 1] = arr[j];
            j = j - 1;
		}
    
		arr[j + 1] = atual;
	}
}
