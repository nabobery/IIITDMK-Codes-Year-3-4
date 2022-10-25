// (b) Write a C program to identify number of tokens and print the tokens
// This program is done by CS20B1044 Avinash R Changrani

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// map structures to maintain count of unique tokens
struct token
{
    int count;
    char token[100];
};

struct token Tokens[100];
int size = 0;
char temp[100];

// to increment the count of token
void increment_token(char *token)
{
    bool flag = true;
    for (int i = 0; i < size; i++)
    {
        // if already there in the array
        if (strcmp(Tokens[i].token, token) == 0)
        {
            Tokens[i].count += 1;
            flag = false;
            break;
        }
    }
    // if newly added token
    if (flag == true)
    {
        for (int i = 0; i < 100; i++)
            Tokens[size].token[i] = '\0';
        for (int i = 0; i < strlen(token); i++)
        {
            Tokens[size].token[i] = token[i];
        }
        Tokens[size].count = 1;
        size++;
    }
    return;
}

// Returns true if the character is a DELIMITER.
bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '|' || ch == '&' || ch == '!')
        return (true);
    return (false);
}

// Returns true if the character is an OPERATOR.
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '|' || ch == '&' || ch == '^' || ch == '!')
        return (true);
    return (false);
}

// Returns true if the string is an INTEGER.
bool isInteger(char *str)
{
    int i, len = strlen(str);
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}

// Returns true if the string is a REAL NUMBER.
bool isRealNumber(char *str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

// Returns true if the character is a SPECIAL SYMBOL.
bool isSpecialSymbol(char ch)
{
    if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ';' || ch == ',')
        return true;
    return false;
}

// Extracts the SUBSTRING given the start, end position and the string
char *subString(char *str, int left, int right)
{
    int i;
    char *subStr = (char *)malloc(sizeof(char) * (right - left + 2));
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

// Parsing the input STRING.
void parse(char *str)
{
    int left = 0, right = 0;
    int len = strlen(str);
    while (right <= len && left <= right)
    {
        if(str[right] == '\n'){
            char *subStr = subString(str, left, right - 1);
            if (isInteger(subStr) == true || isRealNumber(subStr) == true)
            {
                increment_token(subStr);
                printf("%s", subStr);
                printf(" IS A CONSTANT\n");
            }
            else if (isDelimiter(str[right - 1]) == false)
            {
                increment_token(subStr);
                printf("%s", subStr);
                printf(" IS NOT A VALID IDENTIFIER\n");
            }
            break;
        }
        if (isDelimiter(str[right]) == false)
            right++;
        if (isDelimiter(str[right]) == true && left == right)
        {
            if (isOperator(str[right]) == true)
            {
                while (isOperator(str[right]) == true)
                {
                    right++;
                }
                right--;
                char *subStr = subString(str, left, right);
                increment_token(subStr);
                printf("%s", subStr);
                printf(" IS AN OPERATOR\n");
            }
            else if (isSpecialSymbol(str[right]) == true)
            {
                printf("%c", str[right]);
                for (int i = 0; i < 100; i++)
                    temp[i] = '\0';
                temp[0] = str[right];
                increment_token(temp);
                printf(" IS A SPECIAL SYMBOL\n");
            }
            right++;
            left = right;
        }
        else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right)){
            char *subStr = subString(str, left, right - 1);
            if (isInteger(subStr) == true || isRealNumber(subStr) == true)
            {
                increment_token(subStr);
                printf("%s", subStr);
                printf(" IS A CONSTANT\n");
            }
            else if (isDelimiter(str[right - 1]) == false)
            {
                increment_token(subStr);
                printf("%s", subStr);
                printf(" IS NOT A VALID IDENTIFIER\n");
            }
            left = right;
        }    
    }
    return;
}

int main()
{
    char str[1000] = "";
    printf("Please enter the given String: ");
    fgets(str, 1000, stdin);
    parse(str);
    printf("Count of various tokens are: \n");
    printf("Token \t\t count\n");
    int totalcount = 0;
    for (int i = 0; i < size; i++)
    {
        totalcount += Tokens[i].count;
        for (int j = 0; Tokens[i].token[j] != '\0'; j++)
        {
            printf("%c", Tokens[i].token[j]);
        }
        printf(" ----------------- %d\n", Tokens[i].count);
    }
    printf("\nThe total number of Tokens are: %d\n", totalcount);
    return (0);
}