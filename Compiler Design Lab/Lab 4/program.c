/*Given an input string in the format (a+b+c)*$ as an argument, write a c program for recursive descent
parsing and identifying whether the given string is accepted / rejected by the
following CFG given in attachments.
*/

// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdlib.h>

void start();
void fS();
void fA();
void fB();
void accept();
void reject();

char token;

void accept()
{
        printf("The given string is accepted by the given CFG!\n");
        exit(0);
}

void reject()
{
        printf("The given string is rejected by the given CFG!\n");
        exit(0);
}

// function for nonterminal S’
void start()
{
        token = getchar();
        fS();
        if (token == '$')
                accept();
        else
                reject();
}

// function for nonterminal S
void fS()
{
        switch (token)
        {
        case 'a':
                token = getchar();
                fA();
                fS();
                break;
        case 'c':
                token = getchar();
                break;
        default:
                reject();
                break;
        }
}

// A --> ba | SB
void fA()
{
        switch (token)
        {
        case 'b':
                token = getchar();
                if (token == 'a')
                        token = getchar();
                else
                        reject();
                break;
        case 'a':
                fS();
                fB();
                break;
        case 'c':
                fS();
                fB();
                break;
        default:
                reject();
                break;
        }
}

// B --> bA | S
void fB()
{
        switch (token)
        {
        case 'b':
                token = getchar();
                fA();
                break;
        case 'a':
                fS();
                break;
        case 'c':
                fS();
                break;
        default:
                reject();
                break;
        }
}

int main()
{
        printf("Given Grammar : S' → S$, S → aAS | c, A → ba | SB, B → bA | S\n");
        printf("Please Enter the string: \n");
        start();
        return 0;
}
