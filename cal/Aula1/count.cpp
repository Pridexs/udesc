// Testar complexidade com map

#include <map>
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int nNums, num;
    map<int, int> numeros;

    printf("Informe a quantidade de inteiros: ");
    scanf("%d", &nNums);
    printf("Informe os inteiros\n");

    for (int i = 0; i < nNums; i++) {
        scanf("%d", &num);
        numeros[num]++;
    }

    printf("Informe o inteiro a ser contado: ");
    scanf("%d", &num);
    printf("O numero %d aparece %d vezes.\n", num, numeros[num]);

    return 0;
}