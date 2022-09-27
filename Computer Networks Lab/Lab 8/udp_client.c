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
#include <netdb.h>
#include <unistd.h>

int main()
{
    int c_sock, connfd, len;
    char phoneNumber[10] = "9876543210", msg[256];
    char otp[5];
    // create UDP Socket for client
    c_sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server, client;
    client.sin_family = AF_INET;
    client.sin_port = htons(9001);
    client.sin_addr.s_addr = htonl(INADDR_ANY);
    // sending message to server
    printf("Please enter your Phone Number: \n");
    scanf("%s", phoneNumber);
    sendto(c_sock, phoneNumber, sizeof(phoneNumber), 0, (const struct sockaddr *)&client, sizeof(client));
    printf("Phone number sent is : %s\n", phoneNumber);
    // receiving message from server
    recvfrom(c_sock, otp, sizeof(otp), 0, (struct sockaddr *)&client, &len);
    printf("OTP received is %s\n", otp);
    printf("Please enter the OTP Sent by server: ");
    // get otp verification from user
    for (int i = 0; i < 4; i++)
    {
        scanf(" %c", &otp[i]);
    }
    otp[4] = '\0';
    // send otp to server
    sendto(c_sock, otp, sizeof(otp), 0, (const struct sockaddr *)&client, sizeof(client));
    // receive acknowledgement
    recvfrom(c_sock, msg, sizeof(msg), 0, (struct sockaddr *)&client, &len);
    printf("Message received from server is %s\n", msg);
    return 0;
}