#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

int peso_projetil[52];
int poder_projetil[52];

int acharMaxPoder(int n, int capacidade) {
    int m[n+1][capacidade+1];
    
    memset(m, 0, sizeof(int) * (n+1) * (capacidade+1) );

    int item = 1;
    int valor, peso;
    for (int item = 1; item <= n; item++) {
        valor = poder_projetil[item];
        peso = peso_projetil[item];
        for (int k = 0; k <= capacidade; k++) {
            if (k-peso >= 0) {
                m[item][k] = max( m[item-1][k], valor + m[item-1][k-peso] );
            } else {
                m[item][k] = m[item-1][k];
            }
        }
    }

    // for (int i = 0; i <= n; i++) {
    //     for (int j = 0; j <= capacidade; j++) {
    //         printf("%-3d ", m[i][j]);
    //     }
    //     printf("\n");
    // }

    return m[n][capacidade];
}

int main() {
    int t, n;
    int x, y;
    int capacidadeCarga;
    int resistencia;

    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &x, &y);
            poder_projetil[i] = x;
            peso_projetil[i] = y;
        }
        scanf("%d", &capacidadeCarga);
        scanf("%d", &resistencia);

        int maxPoder = acharMaxPoder(n, capacidadeCarga);
        //printf("maxpoder: %d\n", maxPoder);
        if (maxPoder >= resistencia) {
            printf("Missao completada com sucesso\n");
        } else {
            printf("Falha na missao\n");
        }
    }

}
