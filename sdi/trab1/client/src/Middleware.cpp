#include "Middleware.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

Middleware::Middleware(char *ip, char *port)
{
    this->ip = std::string(ip);
    this->port = atoi(port);
    counter = 0;

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error socket\n");
        exit(-1);
    } 

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family     = AF_INET;
	servaddr.sin_port       = htons(atoi(port));
	
    if(inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0)
	{
        printf("Error inet_pton for %s", ip);
        exit(-1);
    }

	if(connect(sockfd, (struct sockaddr * )&servaddr, sizeof(servaddr)) < 0)
    {
		printf("Error connect\n");
        exit(-1);
	}

    n = read(sockfd, recvline, MAXLINE);
    
    if (n < 0)
    {
        printf("Error reading.\n");
        exit(-1);
    }

    recvline[n] = '\0';
	printf("%s", recvline);

    // printf("Entre com o usuario: ");
    // scanf("%s", username);
    // printf("Entre com a senha: ");
    // scanf("%s", password);

    // snprintf(sendline, sizeof(sendline), "username: %s password: %s\r\n\r\n", username, password);
    // n = write(sockfd, sendline, strlen(sendline));

    // if (n < 0)
    // {
    //     printf("Read error\n");
    // }

    // while ( (n = read(sockfd, recvline, MAXLINE)) > 0)
    // {
	// 	counter++;
	// 	recvline[n] = 0;
	// 	if (fputs(recvline, stdout) == EOF)
    //     {
    //         printf("Error fputs\n");
    //         return;
    //     }
	// }

	// if(n < 0)
    // {
    //     printf("Read error\n");
    //     return;
    // }
		
    // close(sockfd);
}

int Middleware::idExists(char *id)
{
    snprintf(sendline, sizeof(sendline), "idexists;%s\r\n\r\n", id);
    n = write(sockfd, sendline, strlen(sendline));

    if (n <  0)
    {
        printf("Error writing\n");
        exit(-1);
    }

    n = read(sockfd, recvline, MAXLINE);

    if (n < 0)
    {
        printf("Error reading\n");
        exit(-1);
    }

    recvline[n] = '\0';

    if (strcmp(recvline, "true") == 0)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

// Criar usuario
// The server can return three different things.
//   0: if the server could not create the user for some unknown reason
//   1: if the server succeded in creating the user
//   2: if there was already a user with the id wanted
int Middleware::createUser(char *id, char *pass)
{
    snprintf(sendline, sizeof(sendline), "createuser;%s;%s\r\n\r\n", id, pass);
    n = write(sockfd, sendline, strlen(sendline));

    if (n <  0)
    {
        printf("Error writing\n");
        exit(-1);
    }

    n = read(sockfd, recvline, MAXLINE);

    if (n < 0)
    {
        printf("Error reading\n");
        exit(-1);
    }

    recvline[n] = '\0';

    if (strcmp(recvline, "success") == 0)
    {
        return 1;
    }
    else if (strcmp(recvline, "error;id_exists") == 0)
    {
        return 2;
    }
    else if (strcmp(recvline, "error;unknown") == 0)
    {
        return 0;
    }

    return 0;
}

// Ler todos os usuarios
std::vector<std::string> Middleware::listUsers()
{
    std::vector<std::string> ids;

    snprintf(sendline, sizeof(sendline), "listids;\r\n\r\n");
    n = write(sockfd, sendline, strlen(sendline));
    
    if (n < 0)
    {
        printf("Error writing\n");
        exit(-1);
    }

    char *token, *saveptr;

    bool exit = false;
    while ( !exit && (n = read(sockfd, recvline, MAXLINE)) > 0 )
    {
        recvline[n] = '\0';

        token = strtok_r(recvline, ";", &saveptr);
        while( token != NULL )
        {
            std::string tok(token);

            if ( tok == "\r\n\r\n" )
            {
                exit = true;
                break;
            }
            ids.push_back(tok);
            token = strtok_r(NULL, ";", &saveptr);
        }
    }

    if (n < 0)
    {
        printf("Error reading\n");
        return std::vector<std::string>();
    }

    return ids;
}

// Efetuar um login
int Middleware::login(char *id, char *pass)
{
    snprintf(sendline, sizeof(sendline), "login;%s;%s\r\n\r\n", id, pass);
    n = write(sockfd, sendline, strlen(sendline));

    if (n < 0)
    {
        printf("Error writing\n");
        exit(-1);
    }

    n = read(sockfd, recvline, MAXLINE);
    
    if (n < 0)
    {
        printf("Error reading\n");
        exit(-1);
    }

    recvline[n] = '\0';
    printf("\n%s\n", recvline);
}

// Fechar conexao
void Middleware::closeConn()
{
    close(sockfd);
}
