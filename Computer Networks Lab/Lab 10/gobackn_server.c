// This program is done by CS20B1044 Avinash R Changrani
// TCP Socket Communication
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
    srand(time(0));
    int s_sock, connfd;
    char temp[5];
    struct sockaddr_in server, client;
    // create TCP socket for server
    s_sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(9001);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    // Binding newly created socket to given IP and verification
    if ((bind(s_sock, (struct sockaddr *)&server, sizeof(server))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
    // Now server is ready to listen and verification
    if ((listen(s_sock, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    int len = sizeof(client);
    // Accept the data packet from client and verification
    connfd = accept(s_sock, (struct sockaddr *)&client, &len);
    if (connfd < 0)
    {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accepts the client...\n");
    char ch;
    int acknowledgement;
    while (1)
    {
        read(connfd, temp, sizeof(temp));
        ch = temp[0];
        if (ch == '#')
            break;
        acknowledgement = rand() % 2;
        if (acknowledgement == 0)
        {
            printf("Time out Timer is over!! No packet received.\n");
            for (int i = 0; i < 5; i++)
                temp[i] = '\0';
            temp[0] = '0';
            printf("Negative acknowledgement sent to the client \n");
            write(connfd, temp, sizeof(temp));
        }
        else
        {
            printf("The frame received from the server is : %c\n", ch);
            for (int i = 0; i < 5; i++)
                temp[i] = '\0';
            temp[0] = '1';
            printf("Positive acknowledgement sent to the client \n");
            write(connfd, temp, sizeof(temp));
        }
    }
    printf("All frames have been received from the client\n");
    return 0;
}