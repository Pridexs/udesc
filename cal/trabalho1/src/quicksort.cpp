// Alexandre Maros & Nadyan S. Pscheidt
// CAL - Trabalho 1

#include "quicksort.h"
#include <algorithm>
 
// main function to do quick sort
void quickSort(int a[], int left, int right, int piv){
	int i, j, x, y;
	
	i = left;
	j = right;
	x = piv;
	
	while(i <= j){
		while(a[i] < x && i < right){
			i++;
		}
		while(a[j] > x && j > left){
			j--;
		}
		if(i <= j){
			y = a[i];
			a[i] = a[j];
			a[j] = y;
			i++;
			j--;
		}
	}
	
	if(j > left){
		quickSort(a, left, j, x);
	}
	if(i < right){
		quickSort(a, i, right, x);
	}
}
