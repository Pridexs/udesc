#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

int comp(const void *a, const void *b) {
    return (*(unsigned long long*)b - *(unsigned long long*)a);
}

int main() {
    unsigned long long n, a;
    unsigned long long maiorAltura = 0;
    unsigned long long alturas[100001];
    double tolerancia = 1e-10;
    double tol2 = tolerancia;

    while(scanf("%llu %llu", &n, &a) && n && a) {
        for (int i = 0; i < n; i++) {
            scanf("%llu", &alturas[i]);
            if (alturas[i] > maiorAltura) {
                maiorAltura = alturas[i];
            }
        }

        qsort(alturas, n, sizeof(unsigned long long), comp);
        
        double area;
        
        area = 0;
        for (long i = 0; i < n; i++) {
            area += alturas[i];
        }

        if (area < a) {
            printf("-.-\n");
            continue;
        } else if (area == a || a == 0) {
            printf(":D\n");
            continue;
        }

        double menorCorte = 0;
        double maiorCorte = maiorAltura;
        double corte = maiorAltura/2;

        while( maiorCorte - menorCorte > tolerancia ) {
            area = 0;
            for (long i = 0; i < n; i++) {
                if (alturas[i] > corte) {
                    area += alturas[i] - corte;
                } else {
                    break;
                }
            }
            //printf("a^2:%lf a:%lf menorc:%lf maiorc:%lf corte:%lf\n", areaQuadrada, area, menorCorte, maiorCorte, corte );
            if (area > a) {
                menorCorte = corte;
            } else if (area > a- tol2 && area < a + tol2) {
                break;
            } else {
                maiorCorte = corte;
            }

            corte = (menorCorte + maiorCorte) / 2;
        }
        
        printf("%.4lf\n", corte + tolerancia);
    }

}
