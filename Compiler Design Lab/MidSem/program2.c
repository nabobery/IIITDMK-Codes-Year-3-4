// (c) Write a C program for any parsing technique for the above CFG and print whether the given input string is accepted or rejected
// This program is done by CS20B1044 Avinash R Changrani

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void start();
void accept();
void reject();
void fS();
void fC();

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
        case '1':
            token = getchar();
            fC();
            break;
        case '2':
            token = getchar();
            fC();
            break;
        case '3':
            token = getchar();
            fC();
            break;
        case '4':
            token = getchar();
            fC();
            break;
        case '5':
            token = getchar();
            fC();
            break;
        case '6':
            token = getchar();
            fC();
            break;
        case '7':
            token = getchar();
            fC();
            break;
        case '8':
            token = getchar();
            fC();
            break;
        case '9':
            token = getchar();
            fC();
            break;
        default:
            reject();
            break;
    }
}

// function for nonterminal C
void fC(){
    switch (token)
    {
        case '0':
            token = getchar();
            fC();
            break;
        case '1':
            token = getchar();
            fC();
            break;
        case '2':
            token = getchar();
            fC();
            break;
        case '3':
            token = getchar();
            fC();
            break;
        case '4':
            token = getchar();
            fC();
            break;
        case '5':
            token = getchar();
            fC();
            break;
        case '6':
            token = getchar();
            fC();
            break;
        case '7':
            token = getchar();
            fC();
            break;
        case '8':
            token = getchar();
            fC();
            break;
        case '9':
            token = getchar();
            fC();
            break;
        case '-':
            token = getchar();
            fS();
            break;
        case '/':
            token = getchar();
            fS();
            break;
        case '$':
            accept();
        default:
            reject();
            break;
    }
}

int main(){
    printf("Given Grammar : S' → S$, S -> 1C|2C|3C|4C|5C|6C|7C|8C|9C , C -> 0C-S|1C-S|2C-S|3C-S|4C-S|5C-S|6C-S|7C-S|8C-S|9C-S|0C/S|1C/S|2C/S|3C/S|4C/S|5C/S|6C/S|7C/S|8C/S|9C/S|0C|1C|2C|3C|4C|5C|6C|7C|8C|9C|epsilon\n");
    printf("Please Enter the string: \n");
    start();
    return 0;
}