// Alexandre Maros
// 
// SDI
// Trabalho 1 - TCP
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
	
#define MAXLINE 512

int main(int argc, char **argv)
{
	int sockfd, n, counter = 0;
	char recvline[MAXLINE + 1];
    char sendline[MAXLINE + 1];
    char username[256], password[256];
	struct sockaddr_in servaddr;

	if(argc != 3) 
    {
        printf("Usage: ./authclient <IPaddress> <Port>\n");
        return -1;
    }
		

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error socket\n");
        return -1;
    } 

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family     = AF_INET;
	servaddr.sin_port       = htons(atoi(argv[2]));
	
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
        printf("Error inet_pton for %s", argv[1]);
        return -1;
    }

	if(connect(sockfd, (struct sockaddr * )&servaddr, sizeof(servaddr)) < 0)
    {
		printf("Error connect\n");
	}

    printf("Entre com o usuario: ");
    scanf("%s", username);
    printf("Entre com a senha: ");
    scanf("%s", password);

    snprintf(sendline, sizeof(sendline), "username: %s password: %s\r\n\r\n", username, password);
    n = write(sockfd, sendline, strlen(sendline));

    if (n < 0)
    {
        printf("Read error\n");
    }

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0)
    {
		counter++;
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF)
        {
            printf("Error fputs\n");
            return -1;
        }
	}

	if(n < 0)
    {
        printf("Read error\n");
        return -1;
    }
		
    close(sockfd);

    return 0;
}