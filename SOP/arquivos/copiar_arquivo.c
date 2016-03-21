/***************************
*						   *
* Nome: Alexandre Maros    *
*		 & Tiago Heinrich  *
*						   *
****************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    struct stat fileStat;
	void *buffer;
	int tamanhoBuffer, tamanhoArquivo;

    if (stat(argv[1], &fileStat) < 0) {
        printf("Erro ao conseguir status!\n");
        return -1;
    }

	tamanhoBuffer = fileStat.st_blksize;
	tamanhoArquivo = fileStat.st_size;
	buffer = (void*) malloc(tamanhoBuffer);
	
    int arq2 = open(argv[2], O_RDONLY);

    if (arq2 != -1) {
        printf("Arquivo ja existe! Cancelando.\n");
        close(arq2);
        return -3;
    } else {
        arq2 = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (arq2 < 0) {
            printf("Erro criando arquivo!\n");
            return -4;
        }
    }
	
	int arq = open(argv[1], O_RDONLY);
	if (arq < 0) {
		printf("Erro ao abrir arq1!\n");
		return -2;
	}
	
	int lido;
	lido = read(arq, buffer, tamanhoBuffer);
	while ( lido != 0)
	{
		if ( write(arq2, buffer, lido) == -1) {
			printf("Erro ao escrever no arquivo!\n");
			return -5;
		}
		lido = read(arq, buffer, tamanhoBuffer);
	}
	
    if (close(arq) == -1) {
		printf("Erro ao fechar arquivo 1\n");
		return -7;
	}

    if (close(arq2) == -1) {
		printf("Erro ao fechar arquivo 2\n");
		return -8;
	}

    return 0;
}
