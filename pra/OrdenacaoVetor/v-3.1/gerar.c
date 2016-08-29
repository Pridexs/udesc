#include <stdio.h>
#include <stdlib.h>

/*
 * Utilizando long long para ocupar mais espaco no arquivo, 8 bytes cada long long.
*/
typedef struct {
    long long indice;
    long long temperatura;
    long long dia;
    long long mes;
    long long ano;
} Medicao;

int main()
{
    FILE *fp = fopen("arq1.xs", "wb");
    unsigned long long i;
    
    // Quantas medicoes para gerar um arquivo de 12 gbs.
    unsigned long long nMedicoes = (long long)(12000000000 / (sizeof(Medicao)));
    printf("Gerando %lld medicoes.\n", nMedicoes);
    for (i = 0; i < nMedicoes; i++) { 
        Medicao m;
        m.indice = i;
        m.temperatura = rand() % 51;
        m.dia = rand() % 31;
        m.mes = (rand() % 12) + 1;
        m.ano = 1950 + (rand() % 66); // 1950 - 2015 s
        fwrite(&m, sizeof(Medicao), 1, fp);
    }
    fclose(fp);
    return 0;
}


