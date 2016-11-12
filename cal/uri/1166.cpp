#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

int nBolas[52];
int topoFileira[52];

bool quadradoPerfeito(int n) {
    int raiz = sqrt(n);
    return raiz * raiz == n;
}

int calcularBolas(int n) {
    memset(topoFileira, 0, sizeof(int) * (n));
    int proxBola = 1;
    int idxHaste = 0;
    int loop = -1;

    while (1) {
        if (topoFileira[idxHaste] == 0) {
            topoFileira[idxHaste] = proxBola++;
            loop = -1;
            idxHaste = 0;
        } else if ( quadradoPerfeito(topoFileira[idxHaste] + proxBola) ) {
            topoFileira[idxHaste] = proxBola++;
            loop = -1;
            idxHaste = 0;
        } else {
            if (loop == idxHaste) {
                break;
            } else {
                if (loop == -1) {
                    loop = idxHaste;
                }
                idxHaste++;
                if (idxHaste >= n) {
                    idxHaste = 0;
                }
            }
        }
    }

    nBolas[n] = proxBola - 1;
    return nBolas[n];
}

int main() {
    int t, n;

    memset(nBolas, 0, sizeof(nBolas));

    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);

        if (nBolas[n] == 0) {
            printf("%d\n", calcularBolas(n));
        } else {
            printf("%d\n", nBolas[n]);
        }
    }

}
