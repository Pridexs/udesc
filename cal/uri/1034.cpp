#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int blocos[26];
int minBlocos[1000001];
int t, n, m, b, i, j;

int comp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int min() {
    int bloco;

    if (m % blocos[n-1] == 0) {
        return m/blocos[n-1];
    }

    minBlocos[0] = 0;
    for (i = 1; i <= m; i++) {
        minBlocos[i] = 1+minBlocos[i-1];
        for (j = 0; j < n; j++) {
            if (i - blocos[j] >= 0) {
                minBlocos[i] = min(minBlocos[i], 1+minBlocos[i-blocos[j]]);
            } else {
                break;
            }
        }
    }

    return minBlocos[m];
}

int main() {
    scanf("%d", &t);

    while(t--) {
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++) {
            scanf("%d", &blocos[i]);
        }

        qsort(blocos, n, sizeof(int), comp);
        printf("%d\n", min());
    }

}
