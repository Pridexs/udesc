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
	
    while(option != 5)
    {
        printf("\nChoose what you want to do:\n"
                "1. Login\n2. Check if user exists\n3. Create user\n"
                "4. Show all variables on server\n"
                "5. Close connection and exit\n\n"
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
            printf("Enter the id you want to check: ");
            scanf("%s", id);
            if (server.idExists(id)) 
            {
                printf("Yes, that id already exists on the server\n");
            }
            else
            {
                printf("No that id does not exist on the server\n");
            }
        }
        else if (option == 3)
        {

        }
        else if (option == 4)
        {

        }
    }

    server.closeConn();

    return 0;
}