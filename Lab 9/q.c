/*
Read IP address, subnet mask address, number of subnets from the user.
Check weather the subneting is possible or not.
If possible print the possible IDs.
*/
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int dec[4] = {0, 0, 0, 0}, bits[32];
int numberOfBits = 0;

// to convert the 4 numbers present in dec to binary using 32 bits
void inttobin()
{
    for (int i = 0; i < 4; i++)
    {
        int temp = dec[i];
        for (int j = i * 8 + 7; j >= i * 8; j--)
        {
            if (temp % 2 == 0)
                bits[j] = 0;
            else
                bits[j] = 1;
            temp /= 2;
        }
    }
}

// to print ip address in dot format using binary representation of ip address
void bintoint()
{
    for (int i = 0; i < 4; i++)
    {
        int temp = 0;
        for (int j = i * 8; j <= i * 8 + 7; j++)
        {
            temp *= 2;
            temp += bits[j];
        }
        printf("%d", temp);
        if (i != 3)
            printf(".");
    }
}

// function to check if it's a valid IPV4 Ip address
bool validateIP(char ip[])
{
    int nc = 0, counter = 0;
    char temp[3];
    for (int i = 0; i < 3; i++)
        temp[i] = '\0';
    for (int i = 0; ip[i] != '\0' && i < 16; i++)
    {
        if (ip[i] == '.')
        {
            if (nc > 3 || nc == 0)
            {
                return false;
            }
            int k = 0;
            for (int i = 0; i < 3; i++)
                temp[i] = '\0';
            for (int j = (i - nc); j < i; j++)
            {
                temp[k] = ip[j];
                k++;
            }
            int d = atoi(temp);
            if (d > 255)
                return false;
            dec[counter] = d;
            counter++;
            nc = 0;
        }
        else if (ip[i] >= '0' && ip[i] <= '9')
        {
            nc++;
        }
        else
            return false;
    }
    return true;
}

// function to check if the given subnet is a power of 2
bool validateSubnets(int n)
{
    if (n == 0)
        return 0;
    while (n != 1)
    {
        if (n % 2 != 0)
            return false;
        n /= 2;
        numberOfBits++;
    }
    return true;
}

int main()
{
    char networkid[16], subnetMask[15];
    int numberOfSubnets, z;
    printf("Please Enter the IP Address of the network you want to make subnets of: ");
    scanf("%s", networkid);
    networkid[15] = '.';
    if (validateIP(networkid) == false)
    {
        printf("\033[0;31m");
        printf("The given network id is not correct! Please try again!\n");
        exit(0);
    }
    printf("Please enter the number of subnets you want to divide the network into: ");
    scanf("%d", &numberOfSubnets);
    if (validateSubnets(numberOfSubnets) == false)
    {
        printf("\033[0;31m");
        printf("The number of Subnets should be  is not correct! Please try again!\n");
        exit(0);
    }
    printf("Please Enter the Subnet Mask Address: ");
    scanf("%s", subnetMask);
    printf("\n");
    // assigning z which is maximum number of bits that can be used to represent the subnet
    if (dec[0] <= 127)
    {
        z = 23;
        for (int i = 1; i < 4; i++)
            dec[i] = 0;
    }
    else if (dec[0] <= 191)
    {
        z = 15;
        for (int i = 2; i < 4; i++)
            dec[i] = 0;
    }

    else if (dec[0] <= 223)
    {
        z = 7;
        dec[3] = 0;
    }
    else
    {
        printf("\033[0;31m");
        printf("The given IP address doesnot come under Class A, B and C\n");
        exit(0);
    }
    // if number of bits required to represent the subnet more than z then not possible
    if (log2(numberOfSubnets) > z)
    {
        printf("\033[0;31m");
        printf("Number of Subnets not possible for the given Network's IP Address\n");
        exit(0);
    }
    long long int temp = pow(2, z + 1);
    printf("The total number of IP Addresses possible in the given Network is %lld\n", temp);
    printf("Total number of hosts per subnet is %lld\n", (temp / numberOfSubnets));
    inttobin();
    // Printing interface, subnet id and limited broadcastr adddress
    printf("Interface\tSubnet ID(Start Address)\tLimited Broadcast Address(End Address)\n");
    printf("1\t\t");
    bintoint();
    printf("\t\t");
    for (int i = 31 - z + numberOfBits; i < 32; i++)
        bits[i] = 1;
    bintoint();
    printf("\n");
    for (int i = 1; i < pow(2, numberOfBits); i++)
    {
        for (int j = 31 - z + numberOfBits; j < 32; j++)
            bits[j] = 0;
        printf("%d\t\t", i + 1);
        for (int j = 30 - z + numberOfBits;; j--)
        {
            if (bits[j] == 0)
            {
                bits[j] = 1;
                break;
            }
            bits[j] = 0;
        }
        bintoint();
        printf("\t\t");
        for (int j = 31 - z + numberOfBits; j < 32; j++)
            bits[j] = 1;
        bintoint();
        printf("\n");
    }
    return 0;
}