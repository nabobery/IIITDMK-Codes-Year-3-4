/*
Given an input string which is an assignment statement with arithmetic operations(DMAS- Division, Multiplication, Addition, Subtraction), write a C program to generate three address code by considering the following.

Division and multiplication (DM) has same precedence.
Addition and subtraction (AS )has same  precedence.
But DM has high precedence over AS.

Also consider left-to-right associativity which defines the order in which the operators of the same precedence will be evaluated in an expression
*/

// This program is done by CS20B1044 Avinash R Changrani

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char expression[100], steps[100][100];

int counter = 0, hp = 0, count = 0;

// function to convert given expression to 3 address code
void three_address_code()
{
    while (counter--)
    {
        int size = strlen(expression);
        char temp[100];
        if (hp > 0)
        {
            for (int j = 0; j < 100; j++)
                temp[j] = '\0';
            for (int i = 0; i < size; i++)
            {
                if (expression[i] == '*' || expression[i] == '/')
                {
                    for (int j = 0; j < (i - 1); j++)
                        temp[j] = expression[j];
                    char ch = '0' + count;
                    temp[i - 1] = ch;
                    int c = 0;
                    for (int j = i - 1; j < i + 2; j++)
                    {
                        steps[count][c++] = expression[j];
                    }
                    for (int j = c; j < 100; j++)
                        steps[count][j] = '\0';
                    for (int j = i; expression[j + 2] != '\0'; j++)
                    {
                        temp[j] = expression[j + 2];
                    }
                    for (int j = 0; temp[j] != '\0'; j++)
                        expression[j] = temp[j];
                    count++;
                    break;
                }
            }
            hp--;
        }
        else
        {
            for (int j = 0; j < 100; j++)
                temp[j] = '\0';
            for (int i = 0; i < size; i++)
            {
                if (expression[i] == '+' || expression[i] == '-')
                {
                    for (int j = 0; j < (i - 1); j++)
                        temp[j] = expression[j];
                    char ch = '0' + count;
                    temp[i - 1] = ch;
                    int c = 0;
                    for (int j = i - 1; j < i + 2; j++)
                    {
                        steps[count][c++] = expression[j];
                    }
                    for (int j = c; j < 100; j++)
                        steps[count][j] = '\0';
                    for (int j = i; expression[j + 2] != '\0'; j++)
                    {
                        temp[j] = expression[j + 2];
                    }
                    for (int j = 0; temp[j] != '\0'; j++)
                        expression[j] = temp[j];
                    count++;
                    break;
                }
            }
        }
    }
}

int main()
{
    int i = 0;
    printf("Enter the boolean expression out = ");
    while (true)
    {
        char ch;
        ch = getchar();
        if (ch == '\n')
            break;
        if (ch == ' ')
            continue;
        else
        {
            expression[i++] = ch;
            if (ch == '*' || ch == '/' || ch == '+' || ch == '-')
            {
                counter++;
                if (ch == '*' || ch == '/')
                    hp++;
            }
        }
    }
    for (int j = i; j < 100; j++)
        expression[j] = '\0';
    three_address_code();
    printf("T1 = ");
    printf("%s;\n", steps[0]);
    for (int i = 1; i < count; i++)
    {
        if (i == count - 1)
        {
            printf("out = ");
            for (int j = 0; steps[i][j] != '\0'; j++)
            {
                if (steps[i][j] >= '0' && steps[i][j] <= '9')
                {
                    int d = steps[i][j] - '0' + 1;
                    printf("T%d", d);
                }
                else
                    printf("%c", steps[i][j]);
            }
            printf(";\n");
        }
        else
        {
            printf("T%d = ", i + 1);
            for (int j = 0; steps[i][j] != '\0'; j++)
            {
                if (steps[i][j] >= '0' && steps[i][j] <= '9')
                {
                    int d = steps[i][j] - '0' + 1;
                    printf("T%d", d);
                }
                else
                    printf("%c", steps[i][j]);
            }
            printf(";\n");
        }
    }
    return 0;
}