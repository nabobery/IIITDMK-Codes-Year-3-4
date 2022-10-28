// This program is done by CS20B1044 Avinash R Changrani
// TCP Socket Communication
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
    int c_sock, connfd, n = 0, size;
    char frames[1000], msg[256];
    char temp[5];
    // create TCP Socket
    c_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, client;
    client.sin_family = AF_INET;
    client.sin_port = htons(9001);
    client.sin_addr.s_addr = htonl(INADDR_ANY);
    // connect the client to socket
    if (connect(c_sock, (struct sockaddr *)&client, sizeof(client)) != 0)
    {
        printf("Connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
    printf("Please enter the size of the message you want to send: ");
    scanf("%d", &size);
    printf("Please enter the message you want to send: \n");
    char ch = '0';
    while (n < size)
    {
        scanf(" %c", &ch);
        frames[n] = ch;
        n++;
    }
    frames[n] = '#';
    printf("The order in which frames will be sent is : \n");
    for (int i = 0; i < n; i++)
        printf("%c ", frames[i]);
    printf("\n");
    int i = 0;
    while (i <= size)
    {
        if (i < size)
        {
            printf("The frame sent to the server is : %c ", frames[i]);
            for (int j = 0; j < 5; j++)
                temp[j] = '\0';
            temp[0] = frames[i];
            write(c_sock, temp, sizeof(temp));
            read(c_sock, temp, sizeof(temp));
            if (temp[0] == '1')
            {
                printf("The server has successfully received the frame %c and a positive acknowledgement was received. \n", frames[i]);
                i++;
            }
            else
            {
                printf("The server has not received the frame %c and a negative acknowledgement was received.So we resend the frame \n", frames[i]);
            }
        }
        else
        {
            temp[0] = frames[i];
            write(c_sock, temp, sizeof(temp));
            i++;
        }
    }
    printf("All frames have been sent to the server\n");
    close(client);
    return 0;
}