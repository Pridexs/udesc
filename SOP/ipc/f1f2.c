#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 2000

 
// ls -l /dev/shm/  <<-- diretório do semaforo
// rm /dev/shm/*nomeprocesso* <<--Exclui processo
// Compilação: gcc -Wall -pthread -o "f1&f2" "f1&f2.c" -lrt 

int sai = 0;

void f1(int *argp, sem_t *mutex) {
	int i, temp;
	for (i = 0; i < MAX; i++) {
		sem_wait(mutex);
		temp = *argp;
		temp++;
		*argp = temp;
		sem_post(mutex);
	}
}

void f2(int *argp, sem_t *mutex) {
	int i, temp;
	for (i = 0; i < MAX; i++) {
		sem_wait(mutex);
		temp = *argp;
		temp--;
		*argp = temp;
		sem_post(mutex);	
	}
}

void sair()
{
    sai = 1;
}

int main(){
	int *ptr;
	sem_t *sem_mutex;
	int status;
	
    /* abre objeto de memoria compartilhada, criando se nao existir */
    int fd = shm_open("/shm", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (-1 == fd) {
		perror("/shm");
		exit(1);
    }
    /* define o tamanho da regiao de memoria compartilhada */
    int ret = ftruncate(fd, sizeof(int));
    if (ret == -1) {
		perror("/shm");
		exit(2);
    }
    /* obtem um ponteiro para a regiao de memoria compartilhada */
    ptr = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
		perror("shm-mmap");
		exit(3);
    }
    /* cria o semaforo "/full" e o inicializa em 1 */
    sem_mutex = sem_open("/mutex", O_CREAT, 0664, 1);
    if (sem_mutex == SEM_FAILED) {
		perror("full");
		exit(4);
    }
	signal(SIGINT, sair);
	pid_t f;
	f = fork();
	printf("pid: %u\n", f);
	if(f==0){
		f1(ptr, sem_mutex);
	}else{
		f2(ptr, sem_mutex);
		waitpid(f, &status, 0);	
		printf("Valor final na memória: %d\n\n", *ptr);
		ret = munmap(ptr, sizeof(int));
		if (-1 == ret)
		perror("shm-munmap");
		ret = shm_unlink("/shm");
		if (-1 == ret)
		perror("shm-unlink");
		ret = sem_close(sem_mutex);
		if (-1 == ret)
		perror("sem_mutex");
		ret = sem_unlink("/mutex");
		if (-1 == ret)
		perror("sem_full");
	}
    return 0;
}
