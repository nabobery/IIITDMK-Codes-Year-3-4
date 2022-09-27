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
#include <netdb.h>

int main()
{
    int c_sock, connfd;
    char phoneNumber[10] = "9876543210", msg[256];
    char otp[5];
    // create TCP Socket
    c_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, client;
    client.sin_family = AF_INET;
    client.sin_port = htons(9001);
    client.sin_addr.s_addr = htonl(INADDR_ANY);
    // connect the client to socket
    if (connect(c_sock, (struct sockaddr *)&client, sizeof(client)) != 0)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
    // sending message to server
    printf("Please enter your Phone Number: \n");
    scanf("%s", phoneNumber);
    write(c_sock, phoneNumber, sizeof(phoneNumber));
    printf("Phone number sent is : %s\n", phoneNumber);
    // receiving message from server
    read(c_sock, otp, sizeof(otp));
    printf("OTP received is %s\n", otp);
    printf("Please enter the OTP Sent by server: ");
    // get otp verification from user
    for (int i = 0; i < 4; i++)
    {
        scanf(" %c", &otp[i]);
    }
    otp[4] = '\0';
    // send otp to server
    write(c_sock, otp, sizeof(otp));
    // receive acknowledgement
    read(c_sock, msg, sizeof(msg));
    printf("Message received from server is %s\n", msg);
    return 0;
}