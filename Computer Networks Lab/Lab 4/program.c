/*
Write a C program to simulate the Hamming code generation and error detection.
You need to write two functions as follows:
1) gen_hcode(): to generate hamming code
2) detect_herr(): to perform error detection

Also experiment with following cases using switch case:
1) No error: with out changing data and redundant bits check for error
2) Error 1: change two random data bits and check for errors
3) Error 2: change one random parity bit and check for errors
4) Error 3: change three random data and parity bits and check for errors
 */
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

char receieved_msg[7];

int p[3] = {0, 1, 3};

void gen_hcode(char data[], int parity, int size)
{
    char rev_data[size];
    for (int i = 0; i < size; i++)
    {
        rev_data[i] = data[size - i - 1];
    }
    int r = 3;
    for (r = 1;; r++)
    {
        int temp = pow(2, r);
        if (temp >= (size + r + 1))
        {
            break;
        }
    }
    char result[size + r];
    char parity_bits[r];
    int j = 0, k = 0;
    for (int i = 0; i < (size + r); i++)
    {
        if (i == ((int)pow(2, k) - 1))
        {
            result[i] = '0';
            receieved_msg[i] = '0';
            k++;
        }
        else
        {
            result[i] = rev_data[j];
            receieved_msg[i] = rev_data[j];
            j++;
        }
    }
    for (int i = 0; i < r; i++)
    {
        int position = pow(2, i);
        int count = 0, j, k;
        j = position - 1;
        while (j < (size + r))
        {
            for (k = j; k < j + position; k++)
            {
                if (result[k] == '1')
                    count++;
            }
            j = j + 2 * position;
        }
        if (count % 2 == 0)
        {
            if (parity == 1)
            {
                parity_bits[i] = '1';
            }
            else
            {
                parity_bits[i] = '0';
            }
        }
        else
        {
            if (parity == 1)
            {
                parity_bits[i] = '0';
            }
            else
            {
                parity_bits[i] = '1';
            }
        }
    }
    for (int i = 0; i < r; i++)
    {
        int t = pow(2, i);
        result[t - 1] = parity_bits[i];
        receieved_msg[t - 1] = parity_bits[i];
    }
    printf("Sender's Side \n");
    printf("Number of parity Bits is %d\n", r);
    printf("The input message is ");
    for (int i = 0; i < 4; i++)
    {
        printf("%c", data[i]);
    }
    printf("\nHamming Code is ");
    for (int i = 0; i < r; i++)
    {
        printf("%c", parity_bits[i]);
    }
    printf("\nSent message with Hamming Code is ");
    for (int i = size + r - 1; i >= 0; i--)
    {
        printf("%c", result[i]);
    }
}

void detect_herr(int parity)
{
    srand(time(0));
    int choice;
    printf("\n1) No error: with out changing data and redundant bits check for error\n2) Error 1: change one random data bit and check for errors\n3) Error 2: change one random parity bit and check for errors\n4) Error 3: change two random data(1) and parity bits(1) and check for errors\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        // do nothing
    }
    else if (choice == 2)
    {
        int temp1 = rand() % 8;
        while (temp1 == 0 || temp1 == 1 || temp1 == 3)
        {
            temp1 = rand() % 8;
        }
        char c = receieved_msg[temp1];
        if (c == '0')
            receieved_msg[temp1] = '1';
        else
            receieved_msg[temp1] = '0';
    }
    else if (choice == 3)
    {
        int temp1 = rand() % 3;
        char c = receieved_msg[p[temp1]];
        if (c == '0')
            receieved_msg[p[temp1]] = '1';
        else
            receieved_msg[p[temp1]] = '0';
    }
    else if (choice == 4)
    {

        int temp1 = rand() % 8;
        int temp2 = rand() % 3;
        while (temp1 == 0 || temp1 == 1 || temp1 == 3)
        {
            temp1 = rand() % 8;
        }
        char c = receieved_msg[temp1];
        if (c == '0')
            receieved_msg[temp1] = '1';
        else
            receieved_msg[temp1] = '0';
        c = receieved_msg[p[temp2]];
        if (c == '0')
            receieved_msg[p[temp2]] = '1';
        else
            receieved_msg[p[temp2]] = '0';
    }
    else
    {
        printf("You've entered something wrong. Please try again!\n");
        exit(0);
    }
    printf("Receiver's Side \n");
    printf("Received message(7 bits) is ");
    for (int i = 6; i >= 0; i--)
    {
        printf("%c", receieved_msg[i]);
    }
    printf("\n");
    char p_bits[3];
    int flag = 1;
    for (int i = 0; i < 3; i++)
    {
        int j = p[i], k = 0, position = p[i] + 1, count = 0;
        while (j < 7)
        {
            for (k = j; k < j + position; k++)
            {
                if (k == p[i])
                    continue;
                if (receieved_msg[k] == '1')
                    count++;
            }
            j = j + 2 * position;
        }
        if (count % 2 == 0)
        {
            if (parity == 1)
            {
                p_bits[i] = '1';
            }
            else
            {
                p_bits[i] = '0';
            }
        }
        else
        {
            if (parity == 1)
            {
                p_bits[i] = '0';
            }
            else
            {
                p_bits[i] = '1';
            }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        printf("The parity bit at position %d is %c\n", p[i] + 1, p_bits[i]);
        if (p_bits[i] != receieved_msg[p[i]])
            flag = 0;
    }
    if (flag == 1)
    {
        printf("There's no error in the recieved Message \n");
    }
    else
    {
        printf("There's an errror in the message \n");
    }
}

int main()
{
    char data[4];
    int choice, transmissionCase, size = 0;
    printf("Please enter the message in bit format (4 bits): \n");
    for (int i = 0; i < 4; i++)
    {
        scanf(" %c", &data[i]);
        size++;
    }
    printf("Enter the type of parity you want: \n1)Odd Parity\n2)Even Parity\n");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2)
    {
        printf("You've entered the wrong option. Please try again!!\n");
        exit(0);
    }
    gen_hcode(data, choice, size);
    detect_herr(choice);
    return 0;
}

