// Implementation of simple UDP communication (First run server then run client in 2 terminals)
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int c_sock;
    char phoneNumber[10] = "9876543210";
    char otp[5];
    c_sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in client, other;
    client.sin_family = AF_INET;
    client.sin_port = htons(9001);
    client.sin_addr.s_addr = INADDR_ANY;
    socklen_t ad;
    ad = sizeof(other);
    // sending message to server
    sendto(c_sock, phoneNumber, sizeof(phoneNumber), 0, (struct sockaddr *)&client, sizeof(client));
    printf("Phone number sent is : %s\n", phoneNumber);
    close(c_sock);
    int r_sock;
    char msg[256];
    r_sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server, other1;
    server.sin_family = AF_INET;
    server.sin_port = htons(8001);
    server.sin_addr.s_addr = INADDR_ANY;
    socklen_t add;
    bind(r_sock, (struct sockaddr *)&server, sizeof(server));
    add = sizeof(other1);
    // receiving message from server
    recvfrom(r_sock, otp, sizeof(otp), 0, (struct sockaddr *)&other1, &add);
    printf("OTP received is %s\n", otp);
    return 0;
}