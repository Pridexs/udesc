// Alexandre Maros
// 
// SDI - Distributed Systems
// Goal: Make a kind of shared-variable server using TCP
//
// Server Side.
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
#include <iostream>

using namespace std;

#define MAXLINE 512

void *handleConnection_worker(void *arg);
void handleConnection(int tid, const int connfd, struct sockaddr_in cliaddr);

int handleLogin(int connfd, char *out_buff, string id, string pass);
int handleIdExists(int connfd, char *out_buff, string id);

typedef struct {
      int tid;
      int connfd;
      struct sockaddr_in cliaddr;
      //vector<pair<string, string> > &logins;
} param_t;

// Vector to hold the usernames & passwords.
vector<pair<string, string> > logins;

// Mutex to ensure that only one thread can use
// the login vector at the same time
pthread_mutex_t mutex;

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
    param_t   *args    = (param_t *)   malloc(100 * sizeof(param_t));

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_mutex_init(&mutex, NULL);

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

        args[threadCounter].tid     = threadCounter;
        args[threadCounter].connfd  = connfd;
        //args[threadCounter].logins  = logins;
        args[threadCounter].cliaddr = cliaddr;
        pthread_create(&threads[threadCounter], &attr, handleConnection_worker, (void *) (args + threadCounter) );
        threadCounter++;
    }
    return 0;
}

void *handleConnection_worker(void *arg)
{
    param_t *p = (param_t *) arg;
    handleConnection(p->tid, p->connfd, p->cliaddr);
    pthread_exit((void*) arg);
}

void handleConnection(int tid, const int connfd, struct sockaddr_in cliaddr)
{
    char                    in_buff[MAXLINE];
    char                    out_buff[MAXLINE];
    char                    user[64], pass[64];
    char                    cliIp[MAXLINE];
    int                     n;
    pair<string, string>    pair_user;
    vector<string>          request;

    inet_ntop(AF_INET, &cliaddr.sin_addr, cliIp, sizeof(cliIp));

    printf("Thread %d initializing\n", tid);

    snprintf(out_buff, sizeof(out_buff),
            "Welcome, Your IP Address is: %s and your Port Number is: %d\r\n",
            cliIp, ntohs(cliaddr.sin_port));

    int nwrite = write(connfd, out_buff, strlen(out_buff));
    if (nwrite < 0) {
        printf("Error writing\n");
    }

    while(1)
    {
        memset(in_buff, 0, sizeof(in_buff));
        while( (n = read(connfd, in_buff, MAXLINE)) > 0)
        {
            if (strstr(in_buff, "\r\n\r\n"))
            {
                break;
            }
        }
    
        if (n < 0)
        {
            printf("Error reading\n");
            exit(-1);
        }

        // This means the TCP connection was CLOSED.
        if (n == 0)
        {
            break;
        }

        // To remove the \r\n\r\n from the string
        in_buff[n-4] = '\0';

        char *token, *saveptr;

        token = strtok_r(in_buff, ";", &saveptr);
        while( token != NULL )
        {
            string tok(token);
            request.push_back(tok);
            token = strtok_r(NULL, ";", &saveptr);
        }

        cout << "tokens:" << endl;
        for (int i = 0; i < request.size(); i++)
        {
            cout << request[i] << endl;
        }
        cout << endl;

        if (request.size() == 0)
        {
            printf("Error parsing the request\n");
            exit(-1);
        }
        
        if (request[0] == "closeconn")
        {
            break;
        }
        else if (request[0] == "login")
        {
            handleLogin(connfd, out_buff, request[1], request[2]);
        }
        else if (request[0] == "idexists")
        {
            handleIdExists(connfd, out_buff, request[1]);
        }

        request.clear();

    }

    printf("Thread %d closing\n", tid);

    close(connfd);
}

int handleLogin(int connfd, char *out_buff, string id, string pass)
{
    pair<string, string> user;
    bool found = false;
    char arrUser[256];

    // !!! BEGIN CRITICAL AREA !!! //
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < logins.size(); i++)
    {
        if (logins[i].first == id)
        {
            user = logins[i];
            found = true;
            break; 
        }
    }

    pthread_mutex_unlock(&mutex);
    // !!! END CRITICAL AREA !!! //

    strcpy(arrUser, user.first.c_str());

    if (found && pass == user.second)
    {
        snprintf(out_buff, sizeof(char) * MAXLINE, "Welcome %s! You are now logged in\r\n", arrUser);
    }
    else
    {
        snprintf(out_buff, sizeof(char) * MAXLINE, "User or password incorrect\r\n");
    }

    int n = write(connfd, out_buff, strlen(out_buff));
    if (n < 0)
    {
        printf("Error writing\n");
    }

    return 1;
}

int handleIdExists(int connfd, char *out_buff, string id)
{
    pair<string, string> user;
    bool found = false;
    
    // !!! BEGIN CRITICAL AREA !!! //
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < logins.size(); i++)
    {
        if (logins[i].first == id)
        {
            user = logins[i];
            found = true;
            break; 
        }
    }

    pthread_mutex_unlock(&mutex);
    // !!! END CRITICAL AREA !!! //

    if (found)
    {
        snprintf(out_buff, sizeof(char) * MAXLINE, "true");
    }
    else
    {
        snprintf(out_buff, sizeof(char) * MAXLINE, "false");
    }

    int n = write(connfd, out_buff, strlen(out_buff));
    if (n < 0)
    {
        printf("Error writing\n");
    }

    return 1;
}