// Alexandre Maros
// pridexs.com
// CAL0001 - Complexidade de Algoritmos

#include <cmath>
#include <cstdio>
#include <ctime>

// Complexidade: O(1)
long unsigned int binet_fib(unsigned int n) {
    double fi = (1 + sqrt(5))/2;
    return (pow(fi, n) - pow(1-fi, n)) / sqrt(5);
}

long unsigned int iterative_fib(unsigned int n)
 {
   long unsigned int i = 0, j = 1, k, t;
   for (k = 1; k < n; ++k)
   {
     t = i + j;
     i = j;
     j = t;
   }
   return j;
 }

// Complexidade: O(2^n??)
long unsigned int recursive_fib(unsigned int n){
   if (n < 2)
     return n;
   else
     return recursive_fib(n - 1) + recursive_fib(n - 2);
 }

 int main() {
     unsigned int i;
     int msec_binet, msec_recursivo;
     clock_t start, diff;

     FILE *planilha;

     // Cria arquivo no formato csv com as devidas colunas
     planilha = fopen("dados.csv", "w");
     fprintf(planilha, "N;tempo_iterativo;tempo_recursivo\n");

     for (i = 25; i <= 60; i++) {
         // Fibonacci pelo metodo Iterativo
         start = clock();
         printf("%d Fibonacci Iterativo: %lu\n", i, iterative_fib(i));
         diff = clock() - start;
         msec_binet = diff * 1000 / CLOCKS_PER_SEC;
         
         // Fibonacci pelo metodo Recursivo
         start = clock();
         printf("%d Fibonacci Recursivo: %lu\n\n", i, recursive_fib(i));
         diff = clock() - start;
         msec_recursivo = diff * 1000 / CLOCKS_PER_SEC;

         // Escreve no arquivo
         fprintf(planilha, "%u;%d;%d\n", i, msec_binet, msec_recursivo);
     }

     // Fecha arquivo
     fclose(planilha);

     return 0;
 }