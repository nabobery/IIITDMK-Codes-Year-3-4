// Implementation of CheckSum for your Roll Number
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Input message update with your roll no
char rollno[9] = "CS20B1044";

int size = 0;

char bs[100];

int block_size = 8;

char checksum[8];
char result[8];
char received_message[80];

// convert an integer to binary string
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
    for (int j = 7; j >= 0; j--)
    {
        if (j >= i)
            bs[size] = '0';
        else
            bs[size] = binaryNum[j];
        size++;
    }
}

// Generate binary string from input message
char *genbs(char *ipmsg)
{
    printf("\nASCII values: ");
    for (int i = 0; ipmsg[i] != '\0'; i++)
    {
        int next = ipmsg[i];
        printf("(%d)", ipmsg[i]);
        decToBinary(next);
    }
    return (bs);
}

//
char *ones_complement(char data[])
{
    for (int i = 0; i < block_size; i++)
    {
        if (data[i] == '0')
            data[i] = '1';
        else
            data[i] = '0';
    }
    return data;
}

// function for implementing checksum
void sender(char data[], int s)
{
    for (int i = 0; i < block_size; i++)
    {
        checksum[i] = data[i];
    }
    // add all the 8 bits blocks in one's complement addition
    for (int i = block_size; i < s; i += block_size)
    {
        // Stores the data of the next block
        char next[8], temp[8];
        for (int j = i; j < i + block_size; j++)
        {
            next[j - i] = data[j];
        }
        int sum = 0, carry = 0;
        for (int k = block_size - 1; k >= 0; k--)
        {
            sum += ((next[k] - '0') + (checksum[k] - '0'));
            carry = sum / 2;
            if (sum == 0)
            {
                temp[k] = '0';
                sum = carry;
            }
            else if (sum == 1)
            {
                temp[k] = '1';
                sum = carry;
            }
            else if (sum == 2)
            {
                temp[k] = '0';
                sum = carry;
            }
            else
            {
                temp[k] = '1';
                sum = carry;
            }
        }
        char end[8];
        if (carry == 1)
        {
            for (int i = block_size - 1; i >= 0; i--)
            {
                if (carry == 0)
                {
                    end[i] = temp[i];
                }
                else if (((temp[i] - '0') + carry) % 2 == 0)
                {
                    end[i] = '0';
                    carry = 1;
                }
                else
                {
                    end[i] = '1';
                    carry = 0;
                }
            }
            for (int i = 0; i < block_size; i++)
            {
                checksum[i] = end[i];
            }
        }
        else
        {
            for (int i = 0; i < block_size; i++)
            {
                checksum[i] = temp[i];
            }
        }
    }
    // take one's complement at the end
    ones_complement(checksum);
}

void receiver(char data[], int s)
{
    for (int i = 0; i < block_size; i++)
    {
        result[i] = data[i];
    }
    // add all the 8 bits blocks in one's complement addition
    for (int i = block_size; i < s; i += block_size)
    {
        // Stores the data of the next block
        char next[8], temp[8];
        for (int j = i; j < i + block_size; j++)
        {
            next[j - i] = data[j];
        }
        int sum = 0, carry = 0;
        for (int k = block_size - 1; k >= 0; k--)
        {
            sum += ((next[k] - '0') + (result[k] - '0'));
            carry = sum / 2;
            if (sum == 0)
            {
                temp[k] = '0';
                sum = carry;
            }
            else if (sum == 1)
            {
                temp[k] = '1';
                sum = carry;
            }
            else if (sum == 2)
            {
                temp[k] = '0';
                sum = carry;
            }
            else
            {
                temp[k] = '1';
                sum = carry;
            }
        }
        char end[8];
        if (carry == 1)
        {
            for (int i = block_size - 1; i >= 0; i--)
            {
                if (carry == 0)
                {
                    end[i] = temp[i];
                }
                else if (((temp[i] - '0') + carry) % 2 == 0)
                {
                    end[i] = '0';
                    carry = 1;
                }
                else
                {
                    end[i] = '1';
                    carry = 0;
                }
            }
            for (int i = 0; i < block_size; i++)
            {
                result[i] = end[i];
            }
        }
        else
        {
            for (int i = 0; i < block_size; i++)
            {
                result[i] = temp[i];
            }
        }
    }
    // take one's complement at the end
    ones_complement(result);
    printf("The checksum value is %s\n", result);
    int flag = 0;
    for (int i = 0; i < 8; i++)
    {
        if (result[i] == '1')
            flag = 1;
    }
    if (flag == 1)
        printf("There's an error in the data sent\n");
    else
        printf("There's no error in the data sent\n");
}

// main function
int main()
{
    printf("Input Message: %s", rollno);
    printf("\nBinary String: %s\n", genbs(rollno));
    sender(bs, size);
    printf("The checksum of the given Binary String is %s\n", checksum);
    printf("The Data after appending checksum is \n");
    printf("%s%s\n", bs, checksum);
    for (int i = 0; i < size; i++)
        received_message[i] = bs[i];
    for (int i = size; i < size + 8; i++)
        received_message[i] = checksum[i - size];
    printf("The data sent by receiver is %s\n", received_message);
    receiver(received_message, size + 8);
    return 0;
}