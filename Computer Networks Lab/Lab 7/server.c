// Implementation of simple UDP communication (First run server then run client in 2 terminals)
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdlib.h>

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
    int s_sock, t_sock;
    char msg[256];
    s_sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server, other;
    server.sin_family = AF_INET;
    server.sin_port = htons(9001);
    server.sin_addr.s_addr = INADDR_ANY;
    socklen_t add;
    bind(s_sock, (struct sockaddr *)&server, sizeof(server));
    add = sizeof(other);
    // getting message from client
    recvfrom(s_sock, msg, sizeof(msg), 0, (struct sockaddr *)&other, &add);
    printf("Received Phone Number is :%s\n", msg);
    generateOtp();
    printf("OTP generated is %s\n", otp);
    int c_sock;
    char phoneNumber[10] = "9876543210";
    t_sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in client, other1;
    client.sin_family = AF_INET;
    client.sin_port = htons(8001);
    client.sin_addr.s_addr = INADDR_ANY;
    socklen_t ad;
    ad = sizeof(other1);
    // sending message to client
    sendto(t_sock, otp, sizeof(otp), 0, (struct sockaddr *)&client, sizeof(client));
    close(t_sock);
    return 0;
}