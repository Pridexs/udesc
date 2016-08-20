#include <stdio.h>
#include <stdlib.h>

/*
 * Utilizando long long para ocupar mais espaco no arquivo, 8 bytes cada long long.
*/
struct reg1 {
    long long id;             // Chave Primaria
    long long temp, dia, mes, ano;
    // Chaves secundarias = temp, ano;
};

int main()
{
    FILE *fp = fopen("arq1.xs", "wb");
    unsigned long long i;
    
    // Quantas medicoes para gerar um arquivo de 12 gbs.
    unsigned long long nMedicoes = (long long)((40*500) / (sizeof(struct reg1)));
    printf("Gerando %lld medicoes.\n", nMedicoes);
    for (i = 0; i < nMedicoes; i++) { 
        struct reg1 m;
        m.id = i;
        m.temp = rand() % 51;
        m.dia = rand() % 31;
        m.mes = (rand() % 12) + 1;
        m.ano = 1950 + (rand() % 66); // 1950 - 2015 s
        fwrite(&m, sizeof(struct reg1), 1, fp);
    }
    fclose(fp);
    return 0;
}


