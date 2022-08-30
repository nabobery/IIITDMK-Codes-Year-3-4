#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Input message update with your roll no
char rollno[10] = "CS20B1044";
// Input polynomial donot change
char poly[8] = "10111011";

int size = 0;

char bs[100];
char code[8];

void decToBinary(int n)
{
    char binaryNum[32];
    int i = 0;
    while (n > 0)
    {
        binaryNum[i] = n % 2 + '0';
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        bs[size] = binaryNum[j];
        size++;
    }
}

char *decimalToBinary(int n)
{
    char binaryNum[32];
    char *result = malloc(sizeof(char) * (9));
    int i = 0;
    while (n > 0)
    {
        binaryNum[i] = n % 2 + '0';
        n = n / 2;
        i++;
    }
    int s = 0;
    for (int j = i - 1; j >= 0; j--)
    {
        result[s] = binaryNum[j];
        s;
    }
    return result;
}

// Generate binary string from input message (2 Mark)
char *genbs(char *ipmsg)
{
    printf("\nASCII values: ");
    for (int i = 0; ipmsg[i] != '\0'; i++)
    {
        int temp = ipmsg[i];
        printf("(%d)", ipmsg[i]);
        decToBinary(temp);
    }
    return (bs);
}
// CRC code generation (3 Marks)
char *genCRC(char *ipstr)
{
    // Write code to generate CRC code from input binary string
    int divBits = 8;
    int counter = divBits;
    int s = size + divBits - 1;
    char result[s];
    for (int i = 0; i < size; i++)
    {
        result[i] = bs[i];
    }
    for (int i = size; i < s; i++)
    {
        result[i] = '0';
    }
    char temp[divBits];
    for (int i = 0; i < divBits; i++)
    {
        temp[i] = bs[i];
    }
    while (counter < s)
    {
        if (temp[0] == '1')
        {
            for (int i = 1; i < divBits; i++)
            {
                if (temp[i] != poly[i])
                    temp[i - 1] = '1';
                else
                    temp[i - 1] = '0';
            }
            temp[divBits - 1] = result[counter];
        }
        else
        {
            for (int i = 1; i < divBits; i++)
            {
                temp[i - 1] = temp[i];
            }
            temp[divBits - 1] = result[counter];
        }
        counter++;
    }
    if (temp[0] == '1')
    {
        for (int i = 1; i < divBits; i++)
        {
            if (temp[i] != poly[i])
                temp[i - 1] = '1';
            else
                temp[i - 1] = '0';
        }
    }
    else
    {
        for (int i = 1; i < divBits; i++)
        {
            temp[i - 1] = temp[i];
        }
    }
    for (int j = 0; j < divBits - 1; j++)
    {
        code[j] = temp[j];
    }
    return (code);
}

// LRC code generation (2 Marks)
char *genLRC(char *ipstr)
{
    // char *code = malloc(sizeof(char) * (9));
    //  Write code to generate LRC code from input binary string
    for (int i = 0; i < 8; i++)
    {
        int sum = 0;
        for (int j = i; j < size; j += 8)
        {
            if (bs[j] == '1')
                sum++;
        }
        if (sum % 2 == 0)
            code[i] = '0';
        else
            code[i] = '1';
    }
    return (code);
}

// VRC code generation (2 Marks)
char genVRC(char *ipstr, int x)
{
    char ch;
    // Write code to generate VRC code from input binary string
    char *bs = decimalToBinary(ipstr[x]);
    int sum = 0;
    for (int i = 0; i < 8; i++)
    {
        if (bs[i] == '1')
            sum++;
    }
    if (sum % 2 == 0)
        ch = '0';
    else
        ch = '1';
    return (ch);
}

void main()
{
    printf("\nInput Polynomial: %s", poly);
    printf("\nInput Message: %s", rollno);
    printf("\nBinary String: %s", genbs(rollno));
    printf("\nCRC code: %s", genCRC(rollno));
    printf("\nLRC code %s is %s", rollno, genLRC(rollno));
    for (int i = 0; i < 9; i++)
    {
        printf("\nVRC code for character %c: %c", rollno[i], genVRC(rollno, i));
    }
    printf("\n");
}