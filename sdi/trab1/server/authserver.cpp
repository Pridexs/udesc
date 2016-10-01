// Alexandre Maros
// 
// SDI
// Trabalho 1 - TCP
//

#include <cstdio>
#include <cstdlib>

#include <pthread.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <vector>
#include <utility>
#include <cstring>
#include <string>

using namespace std;

#define MAXLINE 512

void *handleConnection_worker(void *arg);
void handleConnection(int tid, const int connfd, struct sockaddr_in cliaddr);

typedef struct {
      int tid;
      int connfd;
      struct sockaddr_in cliaddr;
      //vector<pair<string, string> > &logins;
} param_t;

// Vector to hold the usernames & passwords.
vector<pair<string, string> > logins;

int main(int argc, char **argv)
{
    int                 listenfd, connfd, n;
    int                 threadCounter = 0;
    struct sockaddr_in  servaddr;
    struct sockaddr_in  cliaddr;
    char                cliIp[MAXLINE];
    socklen_t           len;

    pthread_attr_t      attr;

    pthread_t *threads = (pthread_t *) malloc(100 * sizeof(pthread_t));
    param_t   *args   = (param_t *)   malloc(100 * sizeof(param_t));

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    logins.push_back(make_pair("admin","pass"));

    if (argc != 2) {
        printf("Usage: ./authserver <PortNumber>\n");
        return -1;
    }

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (listenfd < 0) 
    {
        printf("Error opening socket\n");
        return -1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(atoi(argv[1]));

    if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) 
    {
        printf("Error on binding\n");
        return -1;
    }

    listen(listenfd, 32);

    for(;;)
    {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
        inet_ntop(AF_INET, &cliaddr.sin_addr, cliIp, sizeof(cliIp));
        printf("1\n");
        printf("1\n");
        args[threadCounter].tid     = threadCounter;
        args[threadCounter].connfd  = connfd;
        //args[threadCounter].logins  = logins;
        args[threadCounter].cliaddr = cliaddr;
        printf("1\n");
        pthread_create(&threads[threadCounter], &attr, handleConnection_worker, (void *) (args + threadCounter) );
        threadCounter++;
        printf("1\n");
    }
    return 0;
}

void *handleConnection_worker(void *arg)
{
    printf("2\n");
    param_t *p = (param_t *) arg;
    printf("2\n");
    handleConnection(p->tid, p->connfd, p->cliaddr);
    printf("2\n");
    pthread_exit((void*) arg);
}

void handleConnection(int tid, const int connfd, struct sockaddr_in cliaddr)
{
    char    in_buff[MAXLINE];
    char    out_buff[MAXLINE];
    char    user[64], pass[64];
    char    cliIp[MAXLINE];
    int     n;
    //struct sockaddr_in  cliaddr;

    printf("Thread %d initializing\n", tid);

    

    while( (n = read(connfd, in_buff, MAXLINE)) > 0)
    {
        if (strstr(in_buff, "\r\n\r\n"))
        {
            break;
        }
    }

    if (n < 0) {
        printf("Error reading\n");
        exit(-1);
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

    printf("Thread %d closing\n", tid);

    close(connfd);
}