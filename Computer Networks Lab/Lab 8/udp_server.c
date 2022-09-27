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
// UDP Socket Communication
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <netdb.h>
#include <unistd.h>

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
    int s_sock;
    char msg[256];
    struct sockaddr_in server, client;
    // create UDP socket for server
    s_sock = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(9001);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    // Binding newly created socket to given IP and verification
    if ((bind(s_sock, (struct sockaddr *)&server, sizeof(server))) < 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
    int len = sizeof(client);
    // getting message from client
    recvfrom(s_sock, (char *)msg, sizeof(msg), 0, (struct sockaddr *)&client, &len);
    printf("Received Phone Number is : %s\n", msg);
    generateOtp();
    printf("OTP generated is %s\n", otp);
    // sending message to client
    sendto(s_sock, otp, sizeof(otp), 0, (struct sockaddr *)&client, len);
    char otp1[5];
    // reading otp received from client
    recvfrom(s_sock, otp1, sizeof(otp1), 0, (struct sockaddr *)&client, &len);
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
    sendto(s_sock, msg1, sizeof(msg1), 0, (struct sockaddr *)&client, len);
    close(s_sock);
    return 0;
}