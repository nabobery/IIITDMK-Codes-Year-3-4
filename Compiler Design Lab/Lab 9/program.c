// Given a boolean expression as an input, write a program to generate intermediate code for that boolean expression by using short circuit evaluation.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char arr[100][100];
char list[100];
char expression[100];
int n = 1, m = 0;

void printer()
{
    int i = 0;
    printf("\nTokens:\n");
    while (i < n - 1)
    {
        printf("%s\n", arr[i]);
        i++;
    }
    printf("\nSymbols:\n");
    printf("%s\n\n", list);
}

// function to split a<b<c into a<b&&b<c
void preParser()
{
    // loop through the expression
    int i = 0;
    char temp[100];
    while (i < strlen(expression))
    {
        // detect consecutive opearators
        if (expression[i] == '<' || expression[i] == '>')
        {
            if (i + 2 < strlen(expression))
            {
                if (expression[i + 2] == '<' || expression[i + 2] == '>')
                {
                    // copy string following first opearator to temp
                    strcpy(temp, expression + i + 1);
                    // go to second opearator
                    i += 2;
                    // put null
                    expression[i] = '\0';
                    // concatenate && to the first opearator
                    strcat(expression, "&&");
                    // concatenate the rest of the string to the first opearator
                    strcat(expression, temp);
                    // print the new expression
                    printf("new: %s\n", expression);
                }
            }
        }
        i++;
    }
}

void parser()
{
    int i = 0, j = 0;
    char token[10];
    for (int k = 0; k < 10; k++)
        token[k] = '\0';
    printf("expression: %s\n", expression);
    while (expression[i] != '\0')
    {
        if (expression[i] == '&' || expression[i] == '|')
        {
            // push symbol to list
            list[m] = expression[i];
            list[m + 1] = '\0';
            m++;
            strcpy(arr[n - 1], token);
            strcpy(arr[j], token);
            n++;
            j++;
            i++;
        }
        else
        {
            int k = strlen(token);
            token[k] = expression[i];
            token[k + 1] = '\0';
        }
        i++;
    }
    if (strlen(token) > 0)
    {
        strcpy(arr[n - 1], token);
        strcpy(arr[j], token);
        n++;
        j++;
    }
    printer();
}

void intermediateGenerator()
{
    int and = 1, or = m + 1;
    int i = 0;
    int counter = 0;
    printf("Intermediate code:\n");
    while (i < strlen(list))
    {
        if (list[i] == '&')
        {
            if (counter == 0)
            {
                printf("if %s goto L%d\n", arr[i], and);
            }
            else
            {
                printf("L%d: if %s goto L%d\n", counter, arr[i], and);
            }
            and++;
            counter++;
            printf("goto L%d\n", and);
        }
        else
        {
            if (counter == 0)
            {
                printf("if %s goto L%d\n", arr[i], m - counter + 1);
            }
            else
            {
                printf("L%d: if %s goto L%d\n", counter, arr[i], or);
            }
            or --;
        }
        i++;
    }
    // printf final array element
    if (list[i - 1] == '&')
    {
        printf("L%d: if %s goto L%d\n", counter, arr[i], n);
        printf("L%d: %s\n", counter + 1, "T=0");
        and++;
        counter++;
    }
    else
    {
        if (counter == 0)
        {
            printf("if %s goto L%d\n", arr[i], n - 2);
            printf("%s\n", "T=0");
        }
        else
        {
            printf("L%d: if %s goto L%d\n", counter + 1, arr[i], n);
            printf("%s\n", "T=0");
            or --;
        }
        if (counter != 0)
        {
            counter++;
        }
    }
    // setup remaining truths and falses
    printf("goto L%d\n", counter + 2);
    printf("L%d: %s\n", counter + 1, "T=1");
    printf("L%d: %s\n", counter + 2, "next code");
}

int main()
{
    printf("Enter the boolean expression E = ");
    int i = 0;
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
        }
    }
    for (int j = i; j < 100; j++)
        expression[j] = '\0';
    // printf("%s", exp);
    preParser();
    parser();
    intermediateGenerator();
    return 0;
}