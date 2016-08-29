#include <cstdio>
#include <cstdlib>
#include <cmath>

// Funcao pow
// Complexidade: O(n)
int customPow(int a, int b) {
    if (b == 0) {                   // O(1)
        return 1;                   // O(1)
    }                               //
    for (int i = 2; i < b; i++) {   // O(n)
        a *= a;                     // O(1)
    }                               // 
    return a;                       // O(1)
}

// Funcao multiplicar duas matrizes de mesma ordem
// Recebe 2 matrizes e um ponteiro pra onde sera salvo
// Complexidade: O(n^3)
void multMatriz(int **a, int **b, int **res, int n) {
    int i, j, z;                                    // O(1)
    for (i = 0; i < n; i++) {                       // O(n)
        for (j = 0; j < n; j++) {                   // O(n)
            res[i][j] = 0;                          // O(1)
            for (z = 0; z < n; z++) {               // O(n)
                res[i][j] +=  a[j][z] * b[z][j];    // O(1)
            }                                       //
        }                                           //
    }                                               //
}

int main() {

    // Teste custom pow
    printf("%d^%d: %d\n", 2, 4, customPow(2, 4));

    // Teste multMatriz
    int **a, **b, **res;

    a = (int**) malloc(3 * sizeof(int*));
    b = (int**) malloc(3 * sizeof(int*));
    res = (int**) malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++) {
        a[i] = (int*) malloc(3 * sizeof(int));
        b[i] = (int*) malloc(3 * sizeof(int));
        res[i] = (int*) malloc(3 * sizeof(int));
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a[i][j] = b[i][j] = j + 1;
        }
    }

    multMatriz(a, b, res, 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", res[i][j]);
        }
        putchar('\n');
    }

    // Libera memoria //

    return 0;
}