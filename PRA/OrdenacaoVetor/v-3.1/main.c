/*
 * main.c
 * 
 * Copyright 2015 MateuZ Boiani && Alexandre Maros
 * 
 *           ORDENAÇÃO EXTERNA PELO METÓDO - SELEÇÃO POR SUBSTITUIÇÃO
 *  * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MEM_MAX 200000000
#define TAM_MAX_ARQ 12000000000

typedef struct {
    long long indice;
    long long temperatura;
    long long dia;
    long long mes;
    long long ano;
} Medicao;

int carregarArquivoVetor(FILE*, Medicao*, unsigned long long);
int todosCongelados(char*, unsigned long long);
int todosInvalidos(Medicao*, int);
void juntarArquivos(FILE*, FILE*, FILE*);
void montar_nome_arquivo(char *, int, int);

int main(int argc, char **argv)
{
    int i, tam_buffer = 0, nArq = 1, ultimo_escrito = -1;
    unsigned long long nMedicoes = MEM_MAX / (sizeof(Medicao));

    Medicao *medicoes = (Medicao*) malloc(nMedicoes*sizeof(Medicao));
    //status = 1 -> Congelado
    char *status = (char*)malloc(nMedicoes*sizeof(char));
    memset(status, '0', nMedicoes*sizeof(char));
    FILE *fp = fopen("arq1.xs", "rb");              //arquivo gigante
    if(fp == NULL)
    {
        printf("Erro abrindo arquivo!\nEncerrando execucao...\n");
        exit(1);
    }
    tam_buffer = carregarArquivoVetor(fp, medicoes, nMedicoes);             //carrega as medicoes no vetor de medicao, tam_buffer = quantidade de medicoes lidas;
    FILE *arquivo = fopen("./Arquivos/arq_temp0_1.xs", "wb");
    if(arquivo == NULL)
    {
        printf("Erro abrindo arquivo!\nEncerrando execucao...\n");
        exit(1);
    }
    
    do{
        if(todosCongelados(status, tam_buffer)) 
        {
            //printf("Criando arquivo novo...\n");
            nArq++;
            fclose(arquivo);                                                //se algum arquivo esta aberto          
            memset(status, '0', nMedicoes);                                 //descongela todo mundo...      
            char nomeArquivo[500];                
            montar_nome_arquivo(nomeArquivo, 0, nArq);
            arquivo = fopen(nomeArquivo, "wb");
            if(arquivo == NULL){
                printf("Erro abrindo arquivo!\nEncerrando execução...\n");
                exit(1);
            }
            ultimo_escrito = -1;
        }
        int menor_temp = INT_MAX;
        if(ultimo_escrito != -1)
        {
            for(i = 0; i < tam_buffer; i++)
            {
                    if(medicoes[i].temperatura < ultimo_escrito && status[i]!='1')
                        status[i] = '1';
            }           
        }
        for(i = 0; i < tam_buffer; i++)                                      //procura a menor temperatura
        {
            if(medicoes[i].temperatura < ultimo_escrito)
                status[i] = '1';
            else if (medicoes[i].temperatura < menor_temp && medicoes[i].temperatura != -1 && status[i] != '1')
                menor_temp = medicoes[i].temperatura;
        }
        //printf("Ultimo escrito: %d\nMenor: %d\n",ultimo_escrito, menor_temp);
        if(ultimo_escrito <= menor_temp || ultimo_escrito == -1)
        {                                                                   //depois da primeira passada o ultimo escrito nunca será -1
            for(i = 0; i < tam_buffer; i++)
            {
                if(medicoes[i].temperatura == menor_temp)                   //salva o numero no arquivo, traz um novo.
                {                   
                    fseek(arquivo, 0, SEEK_END);
                    Medicao m = medicoes[i];
                    fwrite(&m, sizeof(Medicao), 1, arquivo);
                    ultimo_escrito = m.temperatura;
                    if (!feof(fp) && fread(&m, sizeof(Medicao), 1, fp) == 1)
                    {
                        medicoes[i] = m;
                        i--;
                    }else{
                        medicoes[i].temperatura = -1;
                        status[i] = '1';
                    }
                }
            }
        }
        
    }while( !todosInvalidos(medicoes, tam_buffer) );
    
    fclose(arquivo);

    if (nArq == 1)
    {
        printf("Arquivo ja ordenado\n");
        return 0;
    }
    
    char ultimoArquivoCriado[500];
    
    //Juntar arquivos

    int nArq_aux = nArq;
    int etapa = 1;
    int nArq_ultimo;
    do{
        nArq_ultimo = nArq_aux;
        nArq_aux = 0;
        if(nArq_ultimo %2 != 0){
            char nomeUltimoArquivo[500];
            char nomeNovoArquivo[500];
            montar_nome_arquivo(nomeUltimoArquivo, etapa-1, nArq_ultimo);
            montar_nome_arquivo(nomeNovoArquivo, etapa, 1);
            printf("Renomeando %s para %s\n", nomeUltimoArquivo, nomeNovoArquivo);
            if (rename(nomeUltimoArquivo, nomeNovoArquivo) == -1) {
                printf("Renomeacao falhou!\n");
                exit(-1);
            }
            nArq_aux++;
        }
        for (i = 1; i <= nArq-1; i += 2) 
        {
            nArq_aux++;

            char nomeArquivo1[500];
            char nomeArquivo2[500];       
            char nomeArquivo3[500];       
            montar_nome_arquivo(nomeArquivo1, etapa-1, i);
            printf("Abrindo arquivo %s\n", nomeArquivo1);
            FILE *f1 = fopen(nomeArquivo1, "rb");
            
            montar_nome_arquivo(nomeArquivo2, etapa-1, i+1);
            printf("Abrindo arquivo %s\n", nomeArquivo2);
            FILE *f2 = fopen(nomeArquivo2, "rb");
            
            montar_nome_arquivo(nomeArquivo3, etapa, nArq_aux);
            printf("Criando arquivo %s\n", nomeArquivo3);
            FILE *fp = fopen(nomeArquivo3, "wb");

            strcpy(ultimoArquivoCriado, nomeArquivo3);
            juntarArquivos(f1, f2, fp);

            printf("Deletando arquivo %s e arquivo %s\n", nomeArquivo1, nomeArquivo2);
            if (remove(nomeArquivo1) != 0)
            {
                printf("Erro ao remover arquivo %s\n", nomeArquivo1);
                exit(-1);
            }
            if (remove(nomeArquivo2) != 0)
            {
                printf("Erro ao remover arquivo %s\n", nomeArquivo2);
                exit(-1);
            }
        }
        
        printf("Terminada etapa %d. Narquivo Criados: %d. Ultimo arquivo criado: %s.\n\n", etapa, nArq_aux, ultimoArquivoCriado);

        nArq = nArq_aux;
        etapa++;
        
    } while(nArq_aux > 1);

    printf("Renomeando arquivo final.\n");
    if (rename(ultimoArquivoCriado, "arq_ordenado.xs") == -1) {
        printf("Erro ao renomear %s para arq_odenado.x\n", ultimoArquivoCriado);
    }
    
    return 0;
}

void montar_nome_arquivo(char *strIni, int etapa, int num_arquivo){
        char numero[20];
        strcpy(strIni, "./Arquivos/arq_temp");
        sprintf(numero, "%d", etapa);                                 
        strcat(strIni, numero);
        strcat(strIni, "_");
        sprintf(numero, "%d", num_arquivo);
        strcat(strIni, numero);
        strcat(strIni, ".xs");
}

void juntarArquivos(FILE *f1, FILE *f2, FILE *fp)
{
    if (f1 == NULL) {
        printf("ARQUIVO f1 NULL!\n"); exit(-1);
    }
    if (f2 == NULL) {
        printf("ARQUIVO f2 NULL!\n"); exit(-2);
    }
    if (fp == NULL) {
        printf("ARQUIVO fp NULL!\n"); exit(-3);
    }

    int jaLeu1 = 0, jaLeu2 = 0;
    Medicao m1, m2;
    while (!feof(f1) || !feof(f2)) 
    {
        if (!feof(f1) && !jaLeu1) {
            if (fread(&m1, sizeof(Medicao), 1, f1) == 1)
            {
                jaLeu1 = 1;
            }
        }
        if (!feof(f2) && !jaLeu2) {
            if(fread(&m2, sizeof(Medicao), 1, f2))
            {
                jaLeu2 = 1;
            }
        }
        
        if (jaLeu1 && jaLeu2) 
        {
            if (m1.temperatura <= m2.temperatura)
            {
                fwrite(&m1, sizeof(Medicao), 1, fp);
                jaLeu1 = 0;
            }
            else
            {
                fwrite(&m2, sizeof(Medicao), 1, fp);
                jaLeu2 = 0;
            }
        }
        else if (jaLeu1)
        {
            fwrite(&m1, sizeof(Medicao), 1, fp);
            jaLeu1 = 0;
        }
        else if (jaLeu2)
        {
            fwrite(&m2, sizeof(Medicao), 1, fp);
            jaLeu2 = 0;
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(fp);
}

int todosInvalidos(Medicao *medicoes, int tam_buffer) 
{
    int i;
    for(i = 0; i < tam_buffer; i++) 
    {
        if (medicoes[i].temperatura != -1)
            return 0;
    }
    return 1;
}   

int carregarArquivoVetor(FILE* fp, Medicao* medicoes, unsigned long long nMedicoes)
{
    int i, medicoes_lidas=0;
    for (i = 0; i < nMedicoes && !feof(fp); i++)                            //lê nMedicoes ou a quantidade restante no arquivo;
    {
        fread(&medicoes[i], sizeof(Medicao), 1, fp);
        medicoes_lidas++;
    }
    return medicoes_lidas;
}

int todosCongelados(char*status, unsigned long long nMedicoes)
{
    int i;
    for(i = 0; i < nMedicoes; i++)
    {
        if(status[i]!='1') return 0;
    }
    return 1;
}
