// Alexandre Maros
// 
// SDI - Distributed Systems
// Goal: Make a kind of shared-variable server using TCP
//
// Client Side.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Middleware.h"

// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <netdb.h>
	
// #define MAXLINE 512

int main(int argc, char **argv)
{
	int option;
    char id[256], pass[256];

	if(argc != 3) 
    {
        printf("Usage: ./authclient <IPaddress> <Port>\n");
        return -1;
    }

    Middleware server(argv[1], argv[2]);
	
    while(option != 4)
    {
        printf("\nChoose what you want to do:\n"
                "1. Login\n2. Create user\n"
                "3. Show all variables on server\n"
                "4. Close connection and exit\n\n"
                "> ");
        
        scanf("%d", &option);

        if (option == 1)
        {
            printf("Enter the id: ");
            scanf("%s", id);
            printf("Enter the password: ");
            scanf("%s", pass);
            server.login(id, pass);
        }
        else if (option == 2)
        {

        }
        else if (option == 3)
        {

        }
    }

    server.closeConn();

    return 0;
}