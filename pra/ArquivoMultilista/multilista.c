#include <stdio.h>
#include <stdlib.h>

#define ascendente   1
#define zero         0
#define n_chaves_sec 2

struct reg1 {
    long long id;             // Chave Primaria
    long long temp, dia, mes, ano;
    // Chaves secundarias = temp, ano;
};

struct reg2 {
    long long ed;
    long long chave_primaria;             // Chave Primaria
    long long temp, ano; // Chaves Secundarias
};

struct reg3 {
    long long chave_sec_i;
    long long ed;
    long long chave_primaria;
};

struct reg5 {
    long long chave_sec_i;
    long long ec;
    long long cl;
};

struct reg6 {
    long long chave_sec_i;
    long long ed;
    long long chave_primaria;
    long long proximo_i;
};

struct reg8 {
    long long ed;
    //chave pro temp
    long long chave_primaria;
    //chave pro ano
    long long chave_secundaria;
    //informação
    long long temp;
    long long ano;
    long long dia, mes;
    //onde ta o prox_temp
    long long prox_temp;
    //onde ta o prox_ano
    long long prox_ano;
    
};

void gerarArquivoMultilista();
void consultar();

int main()
{
    int opcao;

    do {
        printf("1. Gerar arquivo Multilista.\n");
        printf("2. Consultar Arquivo Multilista.\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);
        switch(opcao) 
        {
            case 1:
                gerarArquivoMultilista();
                break;
            case 2:
                consultar();
                break;
        }

    } while (opcao != 0);

    return 0;
}

int comparar_por_chavesec(const void *a, const void *b)
{
    struct reg3 *aa = (struct reg3 *)a;
    struct reg3 *bb = (struct reg3 *)b;
    if(bb->chave_primaria < aa->chave_sec_i) {
        return -1;
    } else if (bb->chave_sec_i == aa->chave_sec_i) {
        return 0;
    } else {
        return 1;
    }
}


int comparar_por_chavesec1(const void *a, const void *b)
{
    struct reg6 *aa = (struct reg6 *)a;
    struct reg6 *bb = (struct reg6 *)b;
    if(bb->chave_sec_i < aa->chave_sec_i)
    {
        return -1;
    } else if (bb->chave_sec_i == aa->chave_sec_i){
        return 0;
    } else {
        return 1;
    }
}


void gerarArquivoMultilista()
{
    FILE *farq1, *farq2, *farq3_1, *farq3_2;
    FILE *farq4_1, *farq4_2, *farq5, *farq6, *farq7, *farq8;
    FILE *farq5_1, *farq5_2, *farq6_1, *farq6_2, *farq7_1;
    FILE *farq7_2, *farq8_1, *farq8_2;
    // Primeiro passo
    farq1 = fopen("arq1.xs", "r");
    farq2 = fopen("arq2.xs", "w");
    int i = 1, j;
    while(!feof(farq1))
    {
        struct reg1 r1;
        if(fread(&r1, sizeof(struct reg1), 1, farq1) == 1){
            struct reg2 r2;
            r2.ed = i;
            r2.chave_primaria = r1.id;
            r2.temp = r1.temp;
            r2.ano = r1.ano;
            i++;
            fwrite(&r2, sizeof(struct reg2), 1, farq2);
        }
    }
    fclose(farq1);
    fclose(farq2);
    // Fim primeiro passo

    //Segundo passo
    farq2 = fopen("arq2.xs", "r");
    farq3_1 = fopen("arq3_1.xs", "w");
    farq3_2 = fopen("arq3_2.xs", "w");

    while(!feof(farq2))
    {
        struct reg2 r2;
        struct reg3 r3;
        if(fread(&r2, sizeof(struct reg2), 1, farq2) == 1){
            r3.ed = r2.ed;
            r3.chave_primaria = r2.chave_primaria;
            r3.chave_sec_i = r2.temp;
            fwrite(&r3, sizeof(struct reg3), 1, farq3_1);
            r3.chave_sec_i = r2.ano;
            fwrite(&r3, sizeof(struct reg3), 1, farq3_2);
        }
    }
    
    fclose(farq2);
    remove("./arq2.xs");
    fclose(farq3_1);
    fclose(farq3_2);
    //Fim segundo passo

    //Terceiro passo
    
    farq3_1 = fopen("arq3_1.xs", "r");
    farq3_2 = fopen("arq3_2.xs", "r");
    farq4_1 = fopen("arq4_1.xs", "w");
    farq4_2 = fopen("arq4_2.xs", "w");
    
    struct reg3 reg3_1[500];
    i = 0;
    //poderia ser até 500, mas vamos assim que é tipo "padrão"
    while(!feof(farq3_1)){
        //preenche o vetor
        if(fread(&reg3_1[i], sizeof(struct reg3), 1, farq3_1)==1){
            i++;
        }
    }

    struct reg3 reg3_2[500];
    i = 0;
    //poderia ser até 500, mas vamos assim que é tipo "padrão"
    while(!feof(farq3_2)){
        //preenche o vetor
        if(fread(&reg3_2[i], sizeof(struct reg3), 1, farq3_2)==1){
            i++;
        }
    }    

    //indíce de 3_1 é temperatura & indíce de 3_2 é ano
    qsort (&reg3_1, 500, sizeof(struct reg3), comparar_por_chavesec);
    qsort (&reg3_2, 500, sizeof(struct reg3), comparar_por_chavesec);

    fwrite(&reg3_1, sizeof(struct reg3), 500, farq4_1);
    fwrite(&reg3_2, sizeof(struct reg3), 500, farq4_2);

    fclose(farq3_1);
    fclose(farq3_2);
    fclose(farq4_1);
    fclose(farq4_2);
    remove("./arq3_1.xs");
    remove("./arq3_2.xs");

    //Fim terceiro passo
    //Quarto passo
    farq4_1 = fopen("arq4_1.xs", "r");
    farq5_1 = fopen("arq5_1.xs", "w");
    farq6_1 = fopen("arq6_1.xs", "w");
    
    //por que os registros do arquivo 4 é do tipo reg3!
    struct reg3 r4_1;
    struct reg5 r5_1;
    struct reg6 r6_1;
    fread(&r4_1, sizeof(struct reg3), 1, farq4_1);
    
    r5_1.chave_sec_i = r4_1.chave_sec_i;
    r5_1.ec = r4_1.ed;
    r5_1.cl = 1;
    
    r6_1.chave_sec_i = r4_1.chave_sec_i;
    r6_1.ed = r4_1.ed;
    r6_1.chave_primaria = r4_1.chave_primaria;

    while(!feof(farq4_1))
    {
        if(fread(&r4_1, sizeof(struct reg3), 1, farq4_1) == 1)
        {
            if(r4_1.chave_sec_i != r6_1.chave_sec_i)
            {
                fwrite(&r5_1, sizeof(struct reg5), 1, farq5_1);
                r6_1.proximo_i = 0;
                fwrite(&r6_1, sizeof(struct reg6), 1, farq6_1);
                
                r5_1.chave_sec_i = r4_1.chave_sec_i;
                r5_1.ec = r4_1.ed;
                r5_1.cl = 1;
                
                r6_1.chave_sec_i = r4_1.chave_sec_i;
                r6_1.ed = r4_1.ed;
                r6_1.chave_primaria = r4_1.chave_primaria;

            }else{
                r5_1.cl = r5_1.cl +1;
                r6_1.proximo_i = r4_1.ed;
                fwrite(&r6_1, sizeof(struct reg6), 1, farq6_1);
                
                r6_1.chave_sec_i = r4_1.chave_sec_i;
                r6_1.ed = r4_1.ed;
                r6_1.chave_primaria = r4_1.chave_primaria;                
            }
        }
    }
    fwrite(&r5_1, sizeof(struct reg5), 1, farq5_1);
    r6_1.proximo_i = 0;
    fwrite(&r6_1, sizeof(struct reg6), 1, farq6_1);
    fclose(farq4_1);
    fclose(farq5_1);
    fclose(farq6_1);
    remove("./arq4_1.xs");

    farq4_2 = fopen("arq4_2.xs", "r");
    farq5_2 = fopen("arq5_2.xs", "w");
    farq6_2 = fopen("arq6_2.xs", "w");

    //por que os registros do arquivo 4 é do tipo reg3!
    struct reg3 r4_2;
    struct reg5 r5_2;
    struct reg6 r6_2;
    fread(&r4_2, sizeof(struct reg3), 1, farq4_2);
    
    r5_2.chave_sec_i = r4_2.chave_sec_i;
    r5_2.ec = r4_2.ed;
    r5_2.cl = 1;
    
    r6_2.chave_sec_i = r4_2.chave_sec_i;
    r6_2.ed = r4_2.ed;
    r6_2.chave_primaria = r4_2.chave_primaria;

    while(!feof(farq4_2))
    {
        if(fread(&r4_2, sizeof(struct reg3), 1, farq4_2) == 1)
        {
            if(r4_2.chave_sec_i != r6_2.chave_sec_i)
            {
                fwrite(&r5_2, sizeof(struct reg5), 1, farq5_2);
                r6_2.proximo_i = 0;
                fwrite(&r6_2, sizeof(struct reg6), 1, farq6_2);
                
                r5_2.chave_sec_i = r4_2.chave_sec_i;
                r5_2.ec = r4_2.ed;
                r5_2.cl = 1;
                
                r6_2.chave_sec_i = r4_2.chave_sec_i;
                r6_2.ed = r4_2.ed;
                r6_2.chave_primaria = r4_2.chave_primaria;

            }else{
                r5_2.cl = r5_2.cl +1;
                r6_2.proximo_i = r4_2.ed;
                fwrite(&r6_2, sizeof(struct reg6), 1, farq6_2);
                
                r6_2.chave_sec_i = r4_2.chave_sec_i;
                r6_2.ed = r4_2.ed;
                r6_2.chave_primaria = r4_2.chave_primaria;                
            }
        }
    }
    fwrite(&r5_2, sizeof(struct reg5), 1, farq5_2);
    r6_2.proximo_i = 0;
    fwrite(&r6_2, sizeof(struct reg6), 1, farq6_2);
    fclose(farq4_2);
    fclose(farq5_2);
    fclose(farq6_2);
    remove("arq6_2.xs");
    //Fim Quarto passo
    //Quinto Passo

    farq6_1 = fopen("arq6_1.xs", "r");
    farq6_2 = fopen("arq6_2.xs", "r");
    farq7_1 = fopen("arq7_1.xs", "w");
    farq7_2 = fopen("arq7_2.xs", "w");
    
    struct reg6 r6_1vet[500];
    i = 0;
    //poderia ser até 500, mas vamos assim que é tipo "padrão"
    while(!feof(farq6_1)){
        //preenche o vetor
        if(fread(&r6_1vet[i], sizeof(struct reg6), 1, farq6_1)==1){
            i++;
        }
    }

    struct reg6 r6_2vet[500];
    i = 0;
    //poderia ser até 500, mas vamos assim que é tipo "padrão"
    while(!feof(farq6_2)){
        //preenche o vetor
        if(fread(&r6_2vet[i], sizeof(struct reg6), 1, farq6_2)==1){
            i++;
        }
    }    

    //indíce de 3_1 é temperatura & indíce de 3_2 é ano
    qsort (&r6_1vet, 500, sizeof(struct reg6), comparar_por_chavesec1);
    qsort (&r6_2vet, 500, sizeof(struct reg6), comparar_por_chavesec1);

    fwrite(&r6_1vet, sizeof(struct reg6), 500, farq7_1);
    fwrite(&r6_2vet, sizeof(struct reg6), 500, farq7_2);

    fclose(farq6_1);
    fclose(farq6_2);
    fclose(farq7_1);
    fclose(farq7_2);
    remove("./arq6_1.xs");
    remove("./arq6_2.xs");
    //Fim Quinto Passo
    //Sexto Passo
    farq1 = fopen("arq1.xs", "r");
    farq7_1 = fopen("arq7_1.xs", "r");
    farq7_2 = fopen("arq7_2.xs", "r");
    farq8 = fopen("arq8.xs", "w");

    struct reg1 r1;

    fread(&r1, sizeof(struct reg1), 1, farq1);
    while(!feof(farq1)){
        //os arquivos do reg 7 são do tipo 6;
        struct reg6 r7_1;
        struct reg6 r7_2;
        fread(&r7_1, sizeof(struct reg6), 1, farq7_1);
        fread(&r7_2, sizeof(struct reg6), 1, farq7_2);
        struct reg8 r8;
        //qual a chave primaria??? 7_1 ou 7_2?
        r8.chave_primaria = r7_1.chave_sec_i;
        r8.chave_secundaria = r7_2.chave_sec_i;
        //tanto faz..Será??
        r8.prox_temp = r7_1.proximo_i;
        r8.prox_ano = r7_2.proximo_i;
        //7_1 ou 7_2? O ed é um caso sério, nao pensei numa solução
        r8.ed = r7_1.ed;
        r8.dia = r1.dia;
        r8.mes = r1.mes;
    }
    fclose(farq1);
    fclose(farq8_1);
    fclose(farq7_1);
    remove("./arq7_1.xs");
    fclose(farq7_2);
    remove("./arq7_2.xs");
    //Fim Sexto Passo
}


void consultar()
{
    int op;
    printf("Voce deseja consultar as medicoes por:\n");
    printf("1. Temperatura\n");
    printf("2. Ano\n");
    scanf("%d", &op);

    long long chave;
    if (op == 1)
    {
        printf("Digite a temepratura.\n");
        scanf("%d", &chave);

        //

    }
    else if (op == 2)
    {
        printf("Digite o ano.\n");
        scanf("%d", &chave);

        //
    }
    else
    {
        printf("Opcao Invalida!\n");
    }

}