/*
Create server program:
1. Wait for the "Phone Number" sent by the client.
2. Generate a random OTP of 4 digits and send the OTP to client.
3. Wait for OTP submitted by the client.
4. Check the OTP is valid or invalid and acknowledge the client

Create client program:
1. Read "Phone Number" from user and send to the server.
2. Receive OTP from server and display the OTP.
3. Send OTP to the server and wait for the acknowledgement.
4. Receive the acknowledgement and display.
*/
// This program is done by CS20B1044 Avinash R Changrani
// TCP Socket Communication
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <netdb.h>

char otp[5];

// used for generating 4 digit random otp
void generateOtp()
{
    srand(time(0));
    char ch;
    for (int i = 0; i < 4; i++)
    {
        ch = rand() % 10 + '0';
        otp[i] = ch;
    }
    otp[4] = '\0';
}

int main()
{
    int s_sock, connfd;
    char msg[256];
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
    // getting message from client
    read(connfd, msg, sizeof(msg));
    printf("Received Phone Number is : %s\n", msg);
    generateOtp();
    printf("OTP generated is %s\n", otp);
    // sending message to client
    write(connfd, otp, sizeof(otp));
    char otp1[5];
    // reading otp received from client
    read(connfd, otp1, sizeof(otp1));
    int flag = 1;
    // verifying otp received from client
    for (int i = 0; i < 4; i++)
    {
        if (otp1[i] != otp[i])
        {
            flag = 0;
            break;
        }
    }
    // sending acknowledgment to client after verifying otp
    char acknowledgement[2][256] = {"OTP entered is Invalid!!", "OTP entered is Valid"};
    char msg1[256];
    for (int i = 0; acknowledgement[flag][i] != '\0'; i++)
        msg1[i] = acknowledgement[flag][i];
    // send acknowledgement
    write(connfd, msg1, sizeof(msg1));
    close(s_sock);
    return 0;
}