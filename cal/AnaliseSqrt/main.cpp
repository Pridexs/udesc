// Alexandre Maros
// pridexs.com
// CAL0001 - Complexidade de Algoritmos

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

/*

Relacao de recorrencia:
T(n)            = T(n/2) + O(1)
T(n/2)          = T(n/(2^2)) + O(1)
T(n/(2^2))      = T(n/(2^3)) + O(1)
. . .
T(n/(2^(h-1)))  = T(n/(2^h)) + O(1)

n / (2^h)       = 1
n               = 2^h
h               = log(n) [base 2]

= O(log n)

*/

double custom_sqrt(double n) {
    double low, high, meio = n, meio_antigo = -1, raiz;

    if (n < 1) { 
        low = n;
        high = 1;
    } else {
        low = 1;
        high = n;
    }

    do {
        meio_antigo = meio;
        meio = (low + high) / 2.0;
        raiz = meio * meio;
        
        if (raiz > n) 
            high = meio;
        else
            low = meio;

        //cout << meio << " " << meio_antigo << " " << high << " " << low << endl;        

    } while(fabs(meio - meio_antigo) > 0.00001);

    return meio;
}

int main() {
    double n;

    cout << "Digite o numero para calcular a raiz: ";
    cin >> n;

    cout << "Raiz quadrade de " << n << " = " << custom_sqrt(n) << endl; 

    return 0;
}