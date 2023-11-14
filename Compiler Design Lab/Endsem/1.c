// This program is done by CS20B1044 Avinash R Changrani

// (a) Given a file name, Write a C Program to take it as an argument and identify the number of tokens which are UDVs, number of unique UDVs and print them

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// map structures to maintain count of unique udv
struct token
{
    int count;
    char token[100];
};

struct token Tokens[100];
int count_udv = 0;
char temp[100];

// to increment the count of udv
void increment_token(char *token)
{
    bool flag = true;
    for (int i = 0; i < count_udv; i++)
    {
        // if already there in the array
        if (strcmp(Tokens[i].token, token) == 0)
        {
            Tokens[i].count += 1;
            flag = false;
            break;
        }
    }
    // if newly added udv
    if (flag == true)
    {
        for (int i = 0; i < 100; i++)
            Tokens[count_udv].token[i] = '\0';
        for (int i = 0; i < strlen(token); i++)
        {
            Tokens[count_udv].token[i] = token[i];
        }
        Tokens[count_udv].count = 1;
        count_udv++;
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

bool specialchar(char ch)
{
    if (ch == '!' || ch == '@' || ch == '#' || ch == '$' || ch == '%' || ch == '&' || ch == '*')
        return (true);
    return (false);
}

// Returns true if the string is a VALID UDV.
// first letter is Capital and last but one letter is of 7 special characters (!,@,#,$,%,&,*) and last tetter is a didigt between 0 and 9
bool validUDV(char *str)
{
    int n = strlen(str);
    // ASCII of A is 65 and Z is 90
    if ((str[0] >= 'A' || str[0] <= 'Z') && specialchar(str[n - 2]) && (str[n - 1] >= '0' && str[n - 1] <= '9'))
        return (true);
    return (false);
}

// Returns true if the string is a KEYWORD.
bool isKeyword(char *str)
{
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") || !strcmp(str, "continue") ||
        !strcmp(str, "int") || !strcmp(str, "float") || !strcmp(str, "return") ||
        !strcmp(str, "char") || !strcmp(str, "case") ||
        !strcmp(str, "auto") || !strcmp(str, "sizeof") ||
        !strcmp(str, "typedef") || !strcmp(str, "switch") ||
        !strcmp(str, "unsigned") || !strcmp(str, "void") ||
        !strcmp(str, "static") || !strcmp(str, "struct") ||
        !strcmp(str, "goto") || !strcmp(str, "const") ||
        !strcmp(str, "default") || !strcmp(str, "enum") ||
        !strcmp(str, "extern") || !strcmp(str, "for") ||
        !strcmp(str, "volatile") || !strcmp(str, "union") || !strcmp(str, "string"))
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

// Function for removing redundant lines, spaces and comments
void start(char *filename)
{
    FILE *reqFilePtr = fopen(filename, "r");
    FILE *outputFilePtr = fopen("temp.txt", "w+");
    int prevChar = '\n';
    int currentChar = fgetc(reqFilePtr);
    while (currentChar != EOF)
    {
        // remove multiline comments
        if (currentChar == '*' && prevChar == '/')
        {
            while (1)
            {
                if (currentChar == '/' && prevChar == '*')
                {
                    break;
                }
                prevChar = currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            prevChar = currentChar;
            currentChar = fgetc(reqFilePtr);
            prevChar = currentChar;
            currentChar = fgetc(reqFilePtr);
        }
        // remove single line comments
        else if (currentChar == '/' && prevChar == '/')
        {
            while (1)
            {
                if (currentChar == '\n')
                {
                    break;
                }
                prevChar = currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            prevChar = currentChar;
            currentChar = fgetc(reqFilePtr);
        }
        // remove redundant spaces
        else if (currentChar == ' ' && prevChar == ' ')
        {
            while (1)
            {
                if (currentChar != ' ')
                {
                    break;
                }
                prevChar = currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            prevChar = currentChar;
            currentChar = fgetc(reqFilePtr);
        }
        // remove redundant lines
        else if (currentChar == '\n' && prevChar == '\n')
        {
            while (1)
            {
                if (currentChar != '\n')
                {
                    break;
                }
                prevChar = currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            prevChar = currentChar;
            currentChar = fgetc(reqFilePtr);
        }
        // remove preprocessor directives like #include,#ifdef and #define
        else if (prevChar == '#')
        {
            char nextChar = fgetc(reqFilePtr);
            if((currentChar == 'i' || currentChar == 'd') && (nextChar < '0' || nextChar > '9')){
                prevChar = currentChar;
                currentChar = nextChar;
                while (1)
                {
                    if (currentChar == '\n')
                    {
                        break;
                    }
                    prevChar = currentChar;
                    currentChar = fgetc(reqFilePtr);
                }
                prevChar = currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            else{
                fputc(prevChar, outputFilePtr);
                prevChar = currentChar;
                currentChar = nextChar;
            }   
        }
        // else insert the char into the file
        else
        {
            fputc(prevChar, outputFilePtr);
            prevChar = currentChar;
            currentChar = fgetc(reqFilePtr);
        }
    }
    fputc(prevChar, outputFilePtr);
    fclose(reqFilePtr);
    fclose(outputFilePtr);
    reqFilePtr = fopen(filename, "w");
    outputFilePtr = fopen("temp.txt", "r");
    char c = fgetc(outputFilePtr);
    while (c != EOF)
    {
        fputc(c, reqFilePtr);
        c = fgetc(outputFilePtr);
    }
    fclose(reqFilePtr);
    fclose(outputFilePtr);
    remove("temp.txt");
}

// Parsing the input STRING.
void parse(char *str, FILE *fp)
{
    int left = 0, right = 0;
    int len = strlen(str);
    while (right <= len && left <= right)
    {
        if (str[right] == '\n')
            break;
        if (str[right] == '"')
        {
            left = right;
            right++;
            while (str[right] != '"')
            {
                right++;
            }
            char *subStr = subString(str, left, right);
            fputs(subStr, fp);
            fputs(" IS A STRING\n", fp);
            right++;
            left = right;
            continue;
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
                fputs(subStr, fp);
                fputs(" IS AN OPERATOR\n", fp);
            }
            else if (isSpecialSymbol(str[right]) == true)
            {
                fputc(str[right], fp);
                fputs(" IS A SPECIAL SYMBOL\n", fp);
            }
            right++;
            left = right;
        }
        else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right))
        {
            char *subStr = subString(str, left, right - 1);
            if (isKeyword(subStr) == true)
            {
                fputs(subStr, fp);
                fputs(" IS A KEYWORD\n", fp);
            }
            else if (validUDV(subStr) == true)
            {
                fputs(subStr, fp);
                increment_token(subStr);
                fputs(" IS A VALID USER DEFINED VARIABLE\n", fp);
            }
            else if (isInteger(subStr) == true || isRealNumber(subStr) == true)
            {
                fputs(subStr, fp);
                fputs(" IS A CONSTANT\n", fp);
            }
            else if (validUDV(subStr) == false)
            {
                fputs(subStr, fp);
                fputs(" IS NOT A VALID USER DEFINED VARIABLE\n", fp);
            }
            left = right;
        }
    }
    return;
}

int main(int args, char *argv[])
{
    FILE *fp1, *fp2;
    start(argv[1]);
    start(argv[1]);
    fp1 = fopen(argv[1], "r");
    fp2 = fopen("result.txt", "w");
    char str[1000] = "";
    while (fgets(str, sizeof(str), fp1))
    {
        parse(str, fp2);
    }
    printf("The total number of unique UDVs are %d\n", count_udv);
    printf("Count of various UDVs are: \n");
    printf("UDV \t\t count\n");
    int total = 0;
    for (int i = 0; i < count_udv; i++)
    {
        for (int j = 0; Tokens[i].token[j] != '\0'; j++)
        {
            printf("%c", Tokens[i].token[j]);
        }
        printf(" --------- %d\n", Tokens[i].count);
        total += Tokens[i].count;
    }
    fclose(fp1);
    fclose(fp2);
    return (0);
}