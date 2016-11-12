#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

int arr[110];
int flag;

int max_subarray(int n) {
    int max_ending_here = 0, max_so_far = 0;
    for (int i = 0; i < n; i++) {
        max_ending_here = max(arr[i], max_ending_here + arr[i]);
        max_so_far = max(max_so_far, max_ending_here);
    }
    return max_so_far;
}

int main() {
    int t, n;
    while(scanf("%d", &n) != EOF) {
        int custoManutencao;
        scanf("%d", &custoManutencao);
        int idx = 1;
        for (int i = 0; i < n; i++) {
            arr[idx] = -custoManutencao;
            idx += 2;
        }
        idx = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[idx]);
            idx += 2;
        }
        int lucro = max_subarray(n*2) - custoManutencao;
        if (lucro > 0) {
            printf("%d\n", lucro);
        } else {
            printf("0\n");
        }
    }

}
