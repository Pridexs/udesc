// Alexandre Maros
// 
// SDI - Distributed Systems
// Goal: Make a kind of shared-variable server using TCP
//
// Client Side.
//

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iostream>

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
            printf("\nEnter the id: ");
            scanf("%s", id);
            printf("Enter the password: ");
            scanf("%s", pass);
            server.login(id, pass);
        }
        else if (option == 2)
        {
            printf("\nEnter the id you want to check: ");
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
            printf("\nEnter the id for the user you want to create: ");
            scanf("%s", id);
            printf("Enter the password for the user you want to create: ");
            scanf("%s", pass);
            
            int returnCode = server.createUser(id, pass);
            if (returnCode == 1)
            {
                printf("User created successfully\n");
            }
            else if (returnCode == 0)
            {
                printf("Unknown error while creating new user\n");
            }
            else if (returnCode == 2)
            {
                printf("User with id %s already exists\n", id);
            }
        }
        else if (option == 4)
        {
            std::vector<std::string> ids;
            ids = server.listUsers();
            printf("\nUsers registered:\n");

            for (std::vector<std::string>::iterator it = ids.begin(); it != ids.end(); it++)
            {
                std::cout << *it << std::endl;
            }

            printf("\n");
        }
    }

    server.closeConn();

    return 0;
}