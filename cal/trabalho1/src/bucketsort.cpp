#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

#include "bucketsort.h"

void bucketSort(int arr[], int n, int nBuckets)
{
    std::vector<std::vector<int> > b;
    for (int i = 0; i < nBuckets; i++) {
        b.push_back(std::vector<int>());
    }
    
    for (int i=0; i < n; i++)
    {
        int bi = (int) arr[i] / nBuckets;
        b[bi].push_back(arr[i]);
    }

    for (int i=0; i < nBuckets; i++) {
        std::sort(b[i].begin(), b[i].end());
    }

    int index = 0;
    for (int i = 0; i < nBuckets; i++) {
        for (int j = 0; j < b[i].size(); j++) {
            arr[index++] = b[i][j];
        }
    }
}