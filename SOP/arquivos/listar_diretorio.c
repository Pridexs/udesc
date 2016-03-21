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
#include <dirent.h>
#include <string.h>

int main(int argc, char **argv)
{
    DIR *diret;
    struct dirent *dirnt;

    if(argc == 1)
        diret = opendir("./");
    else if (argc == 2)
        diret = opendir(argv[1]);

    if ( diret == NULL) {
        printf("Erro ao abrir diretorio\n");
        return -1;
    }

    while ((dirnt = readdir(diret)) != NULL) {
        if (dirnt->d_type == DT_DIR)
            printf("D ");
        else if (dirnt->d_type == DT_REG)
            printf("A ");
        else
            printf("O ");
        printf("%s\n", dirnt->d_name);
    }

    if (closedir(diret) == -1) {
        printf("Erro ao fechar diretorio!\n");
        return -2;
    }

    return 0;
}
