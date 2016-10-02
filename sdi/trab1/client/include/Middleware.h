#ifndef MIDDLEWARE_HPP
#define MIDDLEWARE

#include <string>
#include <vector>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAXLINE 512

class Middleware
{
    public:
        Middleware(char *ip, char *port);

        // Se existe um login com nome u
        int idExists(char *id);
        
        // Criar usuario
        int createUser(char *id, char *pass);

        // Ler todos os usuarios
        std::vector<std::string> listUsers();

        // Efetuar um login
        int login(char *id, char *pass);

        // Fechar conexao
        void closeConn();

    private:
        int port;
        std::string ip;
        int sockfd, n, counter;
        char recvline[MAXLINE + 1];
        char sendline[MAXLINE + 1];
        char username[256], password[256];
        struct sockaddr_in servaddr;      
};


#endif