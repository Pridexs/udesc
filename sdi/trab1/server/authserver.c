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
    int                 listenfd, connfd, n;
    struct sockaddr_in  servaddr;
    char                in_buff[MAXLINE];
    char                out_buff[MAXLINE];
    char                user[64], pass[64];
    char                cliIp[MAXLINE];
    struct sockaddr_in  cliaddr;
    socklen_t           len;

    if (argc != 2) {
        printf("Usage: ./x <PortNumber>");
        return -1;
    }

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (listenfd < 0) {
        printf("Error opening socket\n");
        return -1;
    }


    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(atoi(argv[1]));

    if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) {
        printf("Error on binding\n");
        return -1;
    }

    listen(listenfd, 32);

    for(;;)
    {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
        inet_ntop(AF_INET, &cliaddr.sin_addr, cliIp, sizeof(cliIp));

        while( (n = read(connfd, in_buff, MAXLINE)) > 0)
        {
            if (strstr(in_buff, "\r\n\r\n"))
            {
                break;
            }
        }

        if (n < 0) {
            printf("Error reading\n");
            return -1;
        }

        sscanf(in_buff, "username: %s password: %s", user, pass);
        if (strcmp(user, "admin") == 0 && strcmp(pass, "pass") == 0)
        {
            snprintf(out_buff, sizeof(out_buff),
                "PROCEED, Your IP Address is: %s and your Port Number is: %d\r\n",
                cliIp, ntohs(cliaddr.sin_port));
        }
        else
        {
            snprintf(out_buff, sizeof(out_buff), "DENIED\r\n");
        }

        int nwrite = write(connfd, out_buff, strlen(out_buff));
        if (nwrite < 0) {
            printf("Error writing\n");
        }

        close(connfd);
    }
    return 0;
}
