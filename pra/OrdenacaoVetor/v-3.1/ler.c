#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    long long indice;
    long long temperatura;
    long long dia;
    long long mes;
    long long ano;
} Medicao;

int main()
{
	
	
    FILE *fp = fopen("arq_ordernado.xs", "rb");
	if (fp == NULL) {
		printf("ARQUIVO NAO ENCONTRADO!\n");
		exit (-1);
	}
    unsigned long long i;
    while (!feof(fp)) { 
        Medicao m;
        fread(&m, sizeof(Medicao), 1, fp);
        printf("%3lld %3lld %3lld %3lld %3lld\r", m.indice, m.temperatura, m.dia, m.mes, m.ano);
    }

    return 0;
}
