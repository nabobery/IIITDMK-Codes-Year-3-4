/*
By taking the input as intermediate (Three address) code generated from assignment statements with arithmetic operations from the previous lab, write a C program to generate 3 tables data structures (namely Hash Table, ValNum Table and Name Table) and print them.
Hash Table maintains expressions-related information by using two fields (Expression and Value_Number)

ValNum Table contains two fields (Name, Value_Number)

Name Table maintains constant variables information by using 3 fields (Value_Number, Constant value and const flag)
*/

// This program is done by CS20B1044 Avinash R Changrani

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// structs for the various tables
typedef struct
{
    char exp[10];
    int value_num;
} hash_cell;

typedef struct
{
    char name[10];
    int value_num[10];
    int size, counter;
} valnum_cell;

typedef struct
{
    int name, const_value, const_flag;
} name_cell;

char expression[20], steps[100][20];

hash_cell hashTable[20];

valnum_cell valnumTable[20];

name_cell nameTable[20];

int count = 0, t = 0, sh = 0, sv = 0, sn = 0;

// function to convert statements to 3 address code
void three_address_code(int ops)
{
    if (ops < 2)
    {
        strcpy(steps[count], expression);
        count++;
    }
    else
    {
        int hp = 0;
        for (int i = 0; expression[i] != '\0'; i++)
        {
            if (expression[i] == '*' || expression[i] == '/')
                hp++;
        }
        while (ops--)
        {
            int size = strlen(expression);
            char temp[100];
            // printf("%s\n", expression);
            if (hp > 0)
            {
                for (int j = 0; j < 100; j++)
                    temp[j] = '\0';
                for (int i = 0; i < size; i++)
                {
                    if (expression[i] == '*' || expression[i] == '/')
                    {
                        if (ops > 0)
                        {
                            int p, q;
                            for (p = i - 1; (expression[p] != '=' && expression[p] != '*' && expression[p] != '/' && expression[p] != '+' && expression[p] != '-'); p--)
                                ;
                            for (q = i + 1; q < strlen(expression) && (expression[q] != '*' && expression[q] != '/' && expression[q] != '+' && expression[q] != '-'); q++)
                                ;
                            for (int j = 0; j <= p; j++)
                                temp[j] = expression[j];
                            char ch = '0' + t + 1;
                            temp[p + 1] = 't';
                            temp[p + 2] = ch;
                            int c = 0;
                            steps[count][c++] = 't';
                            steps[count][c++] = ch;
                            steps[count][c++] = '=';
                            for (int j = p + 1; j < q; j++)
                            {
                                steps[count][c++] = expression[j];
                            }
                            for (int j = c; j < 100; j++)
                                steps[count][j] = '\0';
                            for (int j = p + 3; expression[q] != '\0'; j++)
                            {
                                temp[j] = expression[q];
                                q++;
                            }
                            strcpy(expression, temp);
                            t++;
                        }
                        else
                        {
                            strcpy(steps[count], expression);
                        }
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
                        if (ops > 0)
                        {
                            int p, q;
                            for (p = i - 1; (expression[p] != '=' && expression[p] != '*' && expression[p] != '/' && expression[p] != '+' && expression[p] != '-'); p--)
                                ;
                            for (q = i + 1; q < strlen(expression) && (expression[q] != '*' && expression[q] != '/' && expression[q] != '+' && expression[q] != '-'); q++)
                                ;
                            for (int j = 0; j <= p; j++)
                                temp[j] = expression[j];
                            char ch = '0' + t + 1;
                            temp[p + 1] = 't';
                            temp[p + 2] = ch;
                            int c = 0;
                            steps[count][c++] = 't';
                            steps[count][c++] = ch;
                            steps[count][c++] = '=';
                            for (int j = p + 1; j < q; j++)
                            {
                                steps[count][c++] = expression[j];
                            }
                            for (int j = c; j < 100; j++)
                                steps[count][j] = '\0';
                            for (int j = p + 3; expression[q] != '\0'; j++)
                            {
                                temp[j] = expression[q];
                                q++;
                            }
                            strcpy(expression, temp);
                            t++;
                        }
                        else
                        {
                            strcpy(steps[count], expression);
                        }
                        count++;
                        break;
                    }
                }
            }
        }
    }
}

// function for the value numbering algorithm
void value_numbering()
{
    int value = 1;
    for (int i = 0; i < count; i++)
    {
        int ops = 0;
        for (int j = 0; steps[i][j] != '\0'; j++)
        {
            if (steps[i][j] == '+' || steps[i][j] == '-' || steps[i][j] == '*' || steps[i][j] == '/')
                ops++;
        }
        bool flag = false;
        char temp[10];
        for (int j = 0; j < 10; j++)
            temp[j] = '\0';
        int tmp = 0, ind;
        for (tmp = 0; steps[i][tmp] != '='; tmp++)
        {
            temp[tmp] = steps[i][tmp];
        }
        for (int j = 0; j < sv; j++)
        {
            if (strcmp(temp, valnumTable[j].name) == 0)
            {
                ind = j;
                flag = true;
                break;
            }
        }
        // if already exists in table
        if (flag == true)
        {
            valnumTable[ind].value_num[valnumTable[ind].size] = value;
            valnumTable[ind].size += 1;
        }
        else
        {
            // if number of operations is 0
            if (ops == 0)
            {
                bool found = (steps[i][tmp + 1] >= '0' && steps[i][tmp + 1] <= '9');
                // if there is only is number
                if (found == true)
                {
                    strcpy(valnumTable[sv].name, temp);
                    valnumTable[sv].value_num[0] = value;
                    valnumTable[sv].size = 1;
                    nameTable[sn].name = value;
                    valnumTable[sv].counter = 0;
                    for (int j = 0; j < 10; j++)
                        temp[j] = '\0';
                    for (int j = tmp + 1; steps[i][j] != '\0'; j++)
                    {
                        temp[j - tmp - 1] = steps[i][j];
                    }
                    // printf("%s\n", temp);
                    nameTable[sn].const_value = atoi(temp);
                    // printf("%d\n", nameTable[sn].const_value);
                    nameTable[sn].const_flag = 1;
                    sv++;
                    sn++;
                    value++;
                }
                // if it is not a number
                else
                {
                    strcpy(valnumTable[sv].name, temp);
                    valnumTable[sv].size = 1;
                    bool indirect = false;
                    for (int j = 0; j < 10; j++)
                        temp[j] = '\0';
                    for (int j = tmp + 1; steps[i][j] != '\0'; j++)
                    {
                        temp[j - tmp - 1] = steps[i][j];
                    }
                    for (int j = 0; j < sv; j++)
                    {
                        if (strcmp(temp, valnumTable[j].name) == 0)
                        {
                            valnumTable[sv].value_num[0] = valnumTable[j].value_num[0];
                            indirect = true;
                            break;
                        }
                    }
                    if (indirect == false)
                    {
                        valnumTable[sv].value_num[0] = value;
                        value++;
                    }
                    sv++;
                }
            }
            // if number of operations != 0
            else
            {
                char temp1[10];
                strcpy(temp1, temp);
                bool f = (steps[i][tmp + 1] >= '0' && steps[i][tmp + 1] <= '9');
                for (int j = 0; j < 10; j++)
                    temp[j] = '\0';
                // if 1st operand is a number
                if (f == true)
                {
                    tmp += 1;
                    int x = 0;
                    for (; (steps[i][tmp] >= '0' && steps[i][tmp] <= '9'); tmp++)
                    {
                        temp[x] = steps[i][tmp];
                        x++;
                    }
                    x = atoi(temp);
                    char op = steps[i][tmp];
                    tmp += 1;
                    for (int j = 0; j < 10; j++)
                        temp[j] = '\0';
                    int y = 0;
                    for (; steps[i][tmp] != '\0'; tmp++)
                    {
                        temp[y] = steps[i][tmp];
                        y++;
                    }
                    bool fg = false;
                    for (int j = 0; j < sn; j++)
                    {
                        if (strcmp(valnumTable[nameTable[j].name - 1].name, temp) == 0)
                        {
                            y = nameTable[j].const_value;
                            // printf("%d\n", y);
                            fg = true;
                            break;
                        }
                    }
                    // if 2nd number is in name table
                    if (fg == true)
                    {
                        strcpy(valnumTable[nameTable[sn].name - 1].name, valnumTable[sv].name);
                        nameTable[sn].const_flag = 1;
                        if (op == '*')
                            nameTable[sn].const_value = x * y;
                        else if (op == '/')
                            nameTable[sn].const_value = x / y;
                        else if (op == '+')
                            nameTable[sn].const_value = x + y;
                        else if (op == '-')
                            nameTable[sn].const_value = x - y;
                        tmp = 0;
                        for (tmp = 0; steps[i][tmp] != '='; tmp++)
                        {
                        }
                        tmp += 1;
                        for (int j = 0; j < 10; j++)
                            temp[j] = '\0';
                        // itoa(nameTable[sn].const_value, temp, 10);
                        sprintf(temp, "%d", nameTable[sn].const_value);
                        for (int j = 0; temp[j] != '\0'; j++)
                        {
                            steps[i][tmp] = temp[j];
                            tmp++;
                        }
                        for (int j = tmp; j < 20; j++)
                            steps[i][j] = '\0';
                        strcpy(valnumTable[sv].name, temp1);
                        valnumTable[sv].value_num[0] = value;
                        valnumTable[sv].size = 1;
                        valnumTable[sv].counter = 0;
                        nameTable[sn].name = value;
                        value++;
                        sv++;
                        sn++;
                    }
                    // if not in name Table
                    else
                    {
                        bool tem = false;
                        int ind;
                        for (int j = 0; j < sv; j++)
                        {
                            if (strcmp(temp, valnumTable[j].name) == 0)
                            {
                                tem = true;
                                ind = j;
                                break;
                            }
                        }
                        if (tem == false)
                        {
                            for (int j = 0; j < sv; j++)
                            {
                                if (valnumTable[j].value_num[0] == valnumTable[ind].value_num[0] && j < ind)
                                {
                                    for (tmp = 0; (steps[i][tmp] != '+' || steps[i][tmp] != '-' || steps[i][tmp] != '*' || steps[i][tmp] != '/'); tmp++)
                                    {
                                    }
                                    tmp += 1;
                                    for (int k = 0; valnumTable[j].name[k] != '\0'; k++)
                                    {
                                        steps[i][tmp++] = valnumTable[j].name[k];
                                    }
                                    break;
                                }
                            }
                        }
                        else
                        {
                            strcpy(valnumTable[sv].name, temp);
                            valnumTable[sv].value_num[0] = value;
                            valnumTable[sv].size = 1;
                            value++;
                            sv++;
                        }
                        strcpy(valnumTable[sv].name, temp1);
                        valnumTable[sv].value_num[0] = value;
                        valnumTable[sv].size = 1;
                        valnumTable[sv].counter = 0;
                        value++;
                        sv++;
                    }
                }
                // if 1st operand is not a number
                else
                {
                    tmp += 1;
                    for (int j = 0; j < 10; j++)
                        temp[j] = '\0';
                    int d = 0, y, x = tmp, ind1, ind2;
                    for (; (steps[i][tmp] != '*' && steps[i][tmp] != '/' && steps[i][tmp] != '+' && steps[i][tmp] != '-'); tmp++)
                    {
                        temp[d++] = steps[i][tmp];
                    }
                    bool fg1 = false;
                    for (int j = 0; j < sv; j++)
                    {
                        if (strcmp(temp, valnumTable[j].name) == 0)
                        {
                            fg1 = true;
                            ind1 = j;
                            break;
                        }
                    }
                    // if 1st operand not in valnumTable
                    if (fg1 == false)
                    {
                        strcpy(valnumTable[sv].name, temp);
                        valnumTable[sv].value_num[0] = value;
                        valnumTable[sv].size = 1;
                        value++;
                        sv++;
                    }
                    char op = steps[i][tmp];
                    bool f1 = false, f2 = false;
                    for (int j = 0; j < sn; j++)
                    {
                        if (strcmp(valnumTable[nameTable[j].name - 1].name, temp) == 0)
                        {
                            y = nameTable[j].const_value;
                            f1 = true;
                            break;
                        }
                    }
                    char str[10];
                    for (int j = 0; j < 10; j++)
                        str[j] = '\0';
                    tmp += 1;
                    d = 0;
                    for (; steps[i][tmp] != '\0'; tmp++)
                    {
                        str[d] = steps[i][tmp];
                        d++;
                    }
                    for (int j = 0; j < sn; j++)
                    {
                        if (strcmp(valnumTable[nameTable[j].name - 1].name, str) == 0)
                        {
                            y = nameTable[j].const_value;
                            f2 = true;
                            break;
                        }
                    }
                    bool fg2 = false;
                    for (int j = 0; j < sv; j++)
                    {
                        if (strcmp(str, valnumTable[j].name) == 0)
                        {
                            fg2 = true;
                            ind2 = j;
                            break;
                        }
                    }
                    // if 2nd operand not there in valnum table
                    if (fg2 == false)
                    {
                        strcpy(valnumTable[sv].name, str);
                        valnumTable[sv].value_num[0] = value;
                        valnumTable[sv].size = 1;
                        value++;
                        sv++;
                    }
                    // if 1st operand in name table
                    if (f1 == true)
                    {
                        char s[10];
                        for (int j = 0; j < 10; j++)
                            s[j] = '\0';
                        // itoa(y, s, 10);
                        sprintf(s, "%d", y);
                        for (int j = 0; s[j] != '\0'; j++)
                        {
                            steps[i][x++] = s[j];
                        }
                        steps[i][x++] = op;
                        for (int j = 0; str[j] != '\0'; j++)
                        {
                            steps[i][x++] = str[j];
                        }
                        for (int j = x; j < 20; j++)
                            steps[i][j] = '\0';
                    }
                    else if (f2 == true)
                    {
                        char s[10];
                        for (int j = 0; j < 10; j++)
                            s[j] = '\0';
                        // itoa(y, s, 10);
                        // follows C standard
                        sprintf(s, "%d", y);
                        // printf("%d\n", temp);
                        for (int j = 0; temp[j] != '\0'; j++)
                        {
                            steps[i][x++] = temp[j];
                        }
                        steps[i][x++] = op;
                        for (int j = 0; s[j] != '\0'; j++)
                        {
                            steps[i][x++] = s[j];
                        }
                        for (int j = x; j < 20; j++)
                            steps[i][j] = '\0';
                    }
                    strcpy(valnumTable[sv].name, temp1);
                    valnumTable[sv].value_num[0] = value;
                    valnumTable[sv].size = 1;
                    value++;
                    sv++;
                    // if 1st operand in valnum table see if it shares the same value number with some other name and replace it with the other name
                    if (fg1 == true)
                    {
                        for (int j = 0; j < sv; j++)
                        {
                            if (valnumTable[j].value_num[0] == valnumTable[ind1].value_num[0] && j < ind1)
                            {
                                char string[10];
                                for (int k = 0; k < 10; k++)
                                    string[k] = '\0';
                                int tm, tmp1;
                                for (tmp1 = 0; (steps[i][tmp1] != '='); tmp1++)
                                {
                                    string[tmp1] = steps[i][tmp1];
                                }
                                string[tmp1] = steps[i][tmp1];
                                tmp1 += 1;
                                for (tm = tmp1; (steps[i][tm] != '*' && steps[i][tm] != '/' && steps[i][tm] != '+' && steps[i][tm] != '-'); tm++)
                                {
                                }
                                for (int k = 0; valnumTable[j].name[k] != '\0'; k++)
                                {
                                    string[tmp1++] = valnumTable[j].name[k];
                                }
                                for (int k = tm; steps[i][k] != '\0'; k++)
                                {
                                    string[tmp1++] = steps[i][k];
                                }
                                for (tm = 0; string[tm] != '\0'; tm++)
                                {
                                    steps[i][tm] = string[tm];
                                }
                                for (int k = tm; k < 20; k++)
                                {
                                    steps[i][k] = '\0';
                                }
                            }
                        }
                    }
                    // if 2nd operand in valnum table see if it shares the same value number with some other name and replace it with the other name
                    if (fg2 == true)
                    {
                        for (int j = 0; j < sv; j++)
                        {
                            if (valnumTable[j].value_num[0] == valnumTable[ind2].value_num[0] && j < ind2)
                            {
                                for (tmp = 0; (steps[i][tmp] != '+' || steps[i][tmp] != '-' || steps[i][tmp] != '*' || steps[i][tmp] != '/'); tmp++)
                                {
                                }
                                tmp += 1;
                                for (int k = 0; valnumTable[j].name[k] != '\0'; k++)
                                {
                                    steps[i][tmp++] = valnumTable[j].name[k];
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    // creating hashTable
    for (int i = 0; i < count; i++)
    {
        int ops = 0;
        for (int j = 0; steps[i][j] != '\0'; j++)
        {
            if (steps[i][j] == '+' || steps[i][j] == '-' || steps[i][j] == '*' || steps[i][j] == '/')
                ops++;
        }
        if (ops > 0)
        {
            char temp[10];
            for (int j = 0; j < 10; j++)
                temp[j] = '\0';
            int tmp = 0, d = 0, ind;
            for (tmp = 0; steps[i][tmp] != '='; tmp++)
            {
                temp[tmp] = steps[i][tmp];
            }
            for (int j = 0; j < sv; j++)
            {
                if (strcmp(valnumTable[j].name, temp) == 0)
                {
                    hashTable[sh].value_num = valnumTable[j].value_num[valnumTable[j].counter];
                    if (valnumTable[j].size > 1)
                        valnumTable[j].counter += 1;
                    break;
                }
            }
            for (int j = 0; j < 10; j++)
                temp[j] = '\0';
            tmp += 1;
            for (; steps[i][tmp] != '\0'; tmp++)
            {
                temp[d++] = steps[i][tmp];
            }
            bool flag = false;
            for (int j = 0; j < sh; j++)
            {
                if (strcmp(hashTable[j].exp, temp) == 0)
                {
                    flag = true;
                    ind = j;
                    break;
                }
            }
            if (flag == false)
            {
                strcpy(hashTable[sh].exp, temp);
                sh++;
            }
            else
            {
                char temp1[10];
                for (int j = 0; j < 10; j++)
                    temp1[j] = '\0';
                int id;
                for (int j = 0; j < sv; j++)
                {
                    if (valnumTable[j].value_num[0] == hashTable[ind].value_num)
                    {
                        strcpy(temp1, valnumTable[j].name);
                        id = j;
                    }
                }
                for (int j = 0; j < 10; j++)
                    temp[j] = '\0';
                for (tmp = 0; steps[i][tmp] != '='; tmp++)
                {
                    temp[tmp] = steps[i][tmp];
                }
                for (int j = 0; j < sv; j++)
                {
                    if (strcmp(valnumTable[j].name, temp) == 0)
                    {
                        if (valnumTable[id].size == 1)
                        {
                            valnumTable[j].value_num[0] = valnumTable[id].value_num[0];
                        }
                        else
                        {
                            for (int k = 0; k < valnumTable[id].size; k++)
                            {
                                valnumTable[j].value_num[k] = valnumTable[id].value_num[k];
                            }
                        }
                        break;
                    }
                }
                for (int j = i + 1; j < count; j++)
                {
                    char *pch = strstr(steps[j], temp);
                    if (pch != NULL)
                    {
                        int p = (int)(pch - steps[j]);
                        int q = d + p, cu = 0;
                        char temp2[10];
                        for (int k = 0; k < 10; k++)
                            temp2[k] = '\0';
                        for (int k = q - 1; steps[j][k] != '\0'; k++)
                        {
                            temp2[cu++] = steps[j][k];
                        }
                        for (cu = p; temp1[cu - p] != '\0'; cu++)
                        {
                            steps[j][cu] = temp1[cu - p];
                        }
                        for (int k = 0; temp2[k] != '\0'; k++)
                        {
                            steps[j][cu++] = temp2[k];
                        }
                        for (int k = cu; k < 20; k++)
                            steps[j][k] = '\0';
                    }
                }
            }
        }
    }
}

int main()
{
    char input[100][20];
    char temp[20];
    int p = 0;
    printf("Enter expressions line by line and enter exit to end\n");
    while (true)
    {
        scanf("%[^\n]%*c", temp);
        if (strcmp(temp, "exit") != 0)
        {
            strcpy(input[p], temp);
            p++;
        }
        else
            break;
    }
    printf("Given Input is : \n");
    for (int i = 0; i < p; i++)
    {
        printf("%s\n", input[i]);
    }
    for (int i = 0; i < p; i++)
    {
        strcpy(temp, input[i]);
        int c = 0;
        for (int j = 0; temp[j] != '\0'; j++)
        {
            if (temp[j] != ' ')
            {
                input[i][c++] = temp[j];
            }
        }
        for (int j = c; j < 20; j++)
            input[i][j] = '\0';
    }
    for (int i = 0; i < p; i++)
    {
        int ops = 0;
        for (int j = 0; input[i][j] != '\0'; j++)
        {
            if (input[i][j] == '+' || input[i][j] == '-' || input[i][j] == '*' || input[i][j] == '/')
                ops++;
        }
        strcpy(expression, input[i]);
        three_address_code(ops);
    }
    printf("The Three Address Code for the given expressions is: \n");
    for (int i = 0; i < count; i++)
    {
        printf("%s\n", steps[i]);
    }
    value_numbering();
    printf("The Name Table is: \n");
    printf("Namelist | constvalue | constflag \n");
    for (int i = 0; i < sn; i++)
    {
        printf("%d|%d|%d\n", nameTable[i].name, nameTable[i].const_value, nameTable[i].const_flag);
    }
    printf("The ValNum Table is: \n");
    printf("Name \t Value-Number\n");
    for (int i = 0; i < sv; i++)
    {
        printf("%s \t\t", valnumTable[i].name);
        if (valnumTable[i].size == 1)
        {
            printf("%d\n", valnumTable[i].value_num[0]);
        }
        else
        {
            for (int j = 0; j < valnumTable[i].size; j++)
            {
                printf("%d, ", valnumTable[i].value_num[j]);
            }
            printf("\n");
        }
    }
    printf("The Hash Table is: \n");
    printf("Expression \t Value-Number\n");
    for (int i = 0; i < sh; i++)
    {
        printf("%s \t\t %d\n", hashTable[i].exp, hashTable[i].value_num);
    }
    printf("The Three Address Code for the given expressions after Value Numbering is: \n");
    for (int i = 0; i < count; i++)
    {
        printf("%s\n", steps[i]);
    }
    return 0;
}