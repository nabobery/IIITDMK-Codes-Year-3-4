// This code is done by CS20B1044 Avinash R Changrani
/*
Given a CFG as an input file in which each line is having exactly one production rule and epsilon as #,  (NT-Capital letters, T-small letters).
Also given an input string containing a set of terminals (T-small letters).

Write a C program for printing the Left Most Derivation and Right Most Derivation in sequence.

The following things are expected from your program
You can use the previous lab programs.
1. Printing whether the given string is accepted or not.
2. If yes, then print both LMD and RMD in sequence.
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXBUF 4096
#define PRODSETMAXALLOCSIZE 20
#define SYMBOLMAXALLOCSIZE 10

// The symbol set of a production for a given nonterminal
typedef char ProductionSymbol;

typedef struct Production Production;
typedef struct ProductionSet ProductionSet;

// Decides the type of a symbol. If it is a nonterminal, the symbol will point to the appropriate ProductionSet
typedef enum ProductionSymbolType
{
    TYPE_TERMINAL = 0,
    TYPE_NONTERMINAL = 1
} ProductionSymbolType;

typedef char ProductionSymbolData;

// Productions of a production set for a given nonterminal
typedef struct Production
{
    ProductionSymbol symbols[SYMBOLMAXALLOCSIZE];
    int size;
    char occupied;
} Production;

// Production sets of nonterminals of a Grammar
typedef struct ProductionSet
{
    Production productions[PRODSETMAXALLOCSIZE];
    int size;
    char symbol;
    char occupied;
    char nullable;
} ProductionSet;

// The Main User-Facing Data Struct
typedef struct Grammar
{
    ProductionSet set[PRODSETMAXALLOCSIZE];
    int size;
    int starting_symbol;
    unsigned int stack_top;
} Grammar;

// For storing transitions for LMD and RMD
int len, lmdpointer = 0, rmdpointer = 0;
char lmd[100][MAXBUF], lmdnonterminal[100], rmd[100][MAXBUF], rmdnonterminal[100];

// Initialises the grammar
void grammar_init(Grammar *g)
{
    g->starting_symbol = '\0';
    g->stack_top = 0;
    g->size = 0;
}

void production_set_init(ProductionSet *p, char symbol)
{
    p->size = 0;
    p->occupied = 1;
    p->nullable = 0;
    p->symbol = symbol;
}

void production_init(Production *p)
{
    p->size = 0;
    p->occupied = 1;
}

// Prints the grammar
void grammar_print(Grammar const *const g)
{
    for (int prod_set = 0; prod_set < g->size; prod_set++)
    {
        if (!g->set[prod_set].occupied)
            continue;
        printf("%c -> ", g->set[prod_set].symbol);
        for (int prod = 0; prod < g->set[prod_set].size; prod++)
        {
            if (!g->set[prod_set].productions[prod].occupied)
                continue;
            if (prod != 0)
                printf("  | ");
            if (g->set[prod_set].productions[prod].size == 0)
            { // Epsilon/Empty production?
                printf("<epsilon>");
            }
            for (int symbol = 0; symbol < g->set[prod_set].productions[prod].size; symbol++)
            {
                printf("%c", g->set[prod_set].productions[prod].symbols[symbol]);
            }
        }
        printf("\n");
    }
    printf("'%c' is the starting symbol.\n", g->starting_symbol);
}

int is_nonterminal(char symbol)
{
    return isupper(symbol);
}

int is_terminal(char symbol)
{
    return !isupper(symbol);
}

// Finds a nonterminal. NULL on failure.
int grammar_find(Grammar *g, char symbol)
{
    for (int prodset = 0; prodset < g->size; prodset++)
    {
        if (!g->set[prodset].occupied)
            continue;
        if (g->set[prodset].symbol == symbol)
            return prodset;
    }
    return -1;
}

void grammar_insert_internal(ProductionSet *p, char *rule)
{
    Production *production;
    p->size++;
    production = &p->productions[p->size - 1];
    production_init(production);
    if (rule[0] == '#')
    {
        // We are done here because this is an epsilon production. Simply set the nullable fag.
        p->nullable = 1;
        return;
    }
    for (int i = 0; rule[i] != '\0'; i++)
    {
        // Skip Whitespace
        if (rule[i] == ' ' ||
            rule[i] == '\t' ||
            rule[i] == '\n')
        {
            continue;
        }
        p->productions[p->size - 1].size++;
        p->productions[p->size - 1].symbols[p->productions[p->size - 1].size - 1] = rule[i];
    }
}

// Insert a production rule for a given nonterminal
void grammar_insert_rule(Grammar *g, char nonterminal, char *rule)
{
    int set = 0;
    // Is set nonempty?
    if (g->size > 0)
    {
        // search the set for nonterminal
        for (set = 0; set < g->size; set++)
        {
            if (g->set[set].symbol == nonterminal) // Found the nonterminal. Break.
                break;
        }
        // Nonterminal not in set?
        if (set == g->size)
        {
            g->size++;
            production_set_init(&g->set[set], nonterminal);
        }
    }
    else
    {
        g->size++;
        set = g->size - 1;
        production_set_init(&g->set[g->size - 1], nonterminal);
    }
    // Actual Insertion now will take place now that production set has been determined.
    grammar_insert_internal(&g->set[set], rule);
}

void grammar_calculate_nullable(Grammar *g)
{
    int null_flag;
    int target;
    for (int prod_set = 0; prod_set < g->size; prod_set++)
    {
        null_flag = 1;
        if (!g->set[prod_set].occupied)
            continue;
        if (g->set[prod_set].nullable)
            continue;
        for (int prod = 0; prod < g->set[prod_set].size; prod++)
        {
            if (!g->set[prod_set].productions[prod].occupied)
                continue;
            if (g->set[prod_set].productions[prod].size == 0)
            {
                g->set[prod_set].nullable = 1;
                break;
            }
            for (int symbol = 0; symbol < g->set[prod_set].productions[prod].size; symbol++)
            {
                if (is_nonterminal(g->set[prod_set].productions[prod].symbols[symbol]))
                {
                    target = grammar_find(g, g->set[prod_set].productions[prod].symbols[symbol]);
                    if (g->set[target].nullable)
                    {
                        // Nullable. Continue till end
                        continue;
                    }
                    else
                    {
                        // Non nullable nonterminal
                        null_flag = 0;
                        break;
                    }
                }
                else
                {
                    // nonterminal
                    null_flag = 0;
                    break;
                }
            }
            if (null_flag == 1)
            {
                // nullable. Set null flag and break.
                g->set[prod_set].nullable = 1;
                printf(">>> %c is nullable\n", g->set[prod_set].symbol);
                break;
            }
        }
    }
}

// Sets starting symbol on grammar
void grammar_set_starting_symbol(Grammar *g, char symbol)
{
    int prodset = grammar_find(g, symbol);
    if (prodset < 0)
    {
        printf("Error: Nonterminal %c does not exist.\n", symbol);
        return;
    }
    g->starting_symbol = g->set[prodset].symbol;
}

// Checks if the grammar has been properly defined or not. Returns less than 0 on failure
int grammar_finish(Grammar *g)
{
    // Cannot proceed without a starting symbol.
    if (g->starting_symbol == '\0')
        return -1;
    grammar_calculate_nullable(g);
    return 0;
}

// Input Flush
void flush()
{
    int c;
    while (((c = getchar()) != EOF) && (c != '\n'))
        ;
}

// store the Left Most Derivations
void lmdappend(char ch, char *str)
{
    lmdnonterminal[lmdpointer] = ch;
    for (int i = 0; i < strlen(str); i++)
    {
        lmd[lmdpointer][i] = str[i];
    }
    lmdpointer++;
}

// Function to find Left Most Derivation of a string
char *LMD(char *sentinel, char *buf, int len, Grammar const *const g)
{
    if (strlen(sentinel) > len)
    {
        return "dead";
    }

    if (strcmp(buf, sentinel) == 0)
    {
        return "Done";
    }
    else
    {
        int index = 0;
        while (!isupper(sentinel[index]))
        {
            index++;
        }
        char temp[MAXBUF];
        for (int i = 0; i < MAXBUF; i++)
            temp[i] = '\0';
        for (int i = 0; sentinel[i] != '\0'; i++)
        {
            temp[i] = sentinel[i];
        }
        for (int prod_set = 0; prod_set < g->size; prod_set++)
        {
            if (!g->set[prod_set].occupied)
                continue;
            if (temp[index] == g->set[prod_set].symbol)
            {
                for (int prod = 0; prod < g->set[prod_set].size; prod++)
                {
                    if (!g->set[prod_set].productions[prod].occupied)
                        continue;
                    if (g->set[prod_set].productions[prod].size == 0)
                    {
                        for (int i = 0; i < MAXBUF; i++)
                            temp[i] = '\0';
                        for (int i = 0; i < index; i++)
                        {
                            temp[i] = sentinel[i];
                        }
                        for (int i = index; sentinel[i + 1] != '\0'; i++)
                        {
                            temp[i] = sentinel[i + 1];
                        }
                    }
                    else
                    {
                        for (int i = 0; i < MAXBUF; i++)
                            temp[i] = '\0';
                        for (int i = 0; i < index; i++)
                        {
                            temp[i] = sentinel[i];
                        }
                        int j = index;
                        for (int symbol = 0; symbol < g->set[prod_set].productions[prod].size; symbol++)
                        {
                            temp[j] = g->set[prod_set].productions[prod].symbols[symbol];
                            j++;
                        }
                        for (int i = index + 1; sentinel[i] != '\0'; i++)
                        {
                            temp[j] = sentinel[i];
                            j++;
                        }
                    }
                    if (strlen(temp) - 1 > len)
                        continue;
                    if (LMD(temp, buf, len, g) == "Done")
                    {
                        if (g->set[prod_set].productions[prod].size == 0)
                        {
                            lmdappend(g->set[prod_set].symbol, "");
                        }
                        else
                        {
                            char str[MAXBUF];
                            for (int symbol = 0; symbol < g->set[prod_set].productions[prod].size; symbol++)
                            {
                                str[symbol] = g->set[prod_set].productions[prod].symbols[symbol];
                            }
                            lmdappend(g->set[prod_set].symbol, str);
                        }
                        return "Done";
                    }
                    else
                        continue;
                }
            }
        }
        return "dead";
    }
}

// store the Right Most Derivations
void rmdappend(char ch, char *str)
{
    rmdnonterminal[rmdpointer] = ch;
    for (int i = 0; i < strlen(str); i++)
    {
        rmd[rmdpointer][i] = str[i];
    }
    rmdpointer++;
}

// Function to find Right Most Derivation of a string
char *RMD(char *sentinel, char *buf, int len, Grammar const *const g)
{
    if (strlen(sentinel) > len)
    {
        return "dead";
    }
    if (strcmp(buf, sentinel) == 0)
    {
        return "Done";
    }
    else
    {
        int index = strlen(sentinel) - 1;
        while (!isupper(sentinel[index]))
        {
            index--;
            if (index < 0)
                return "dead";
        }
        char temp[MAXBUF];
        for (int i = 0; i < MAXBUF; i++)
            temp[i] = '\0';
        for (int i = 0; sentinel[i] != '\0'; i++)
        {
            temp[i] = sentinel[i];
        }
        for (int prod_set = 0; prod_set < g->size; prod_set++)
        {
            if (!g->set[prod_set].occupied)
                continue;
            if (temp[index] == g->set[prod_set].symbol)
            {
                for (int prod = 0; prod < g->set[prod_set].size; prod++)
                {
                    if (!g->set[prod_set].productions[prod].occupied)
                        continue;
                    if (g->set[prod_set].productions[prod].size == 0)
                    {
                        for (int i = 0; i < MAXBUF; i++)
                            temp[i] = '\0';
                        for (int i = 0; i < index; i++)
                        {
                            temp[i] = sentinel[i];
                        }
                        for (int i = index; sentinel[i + 1] != '\0'; i++)
                        {
                            temp[i] = sentinel[i + 1];
                        }
                    }
                    else
                    {
                        for (int i = 0; i < MAXBUF; i++)
                            temp[i] = '\0';
                        for (int i = 0; i < index; i++)
                        {
                            temp[i] = sentinel[i];
                        }
                        int j = index;
                        for (int symbol = 0; symbol < g->set[prod_set].productions[prod].size; symbol++)
                        {
                            temp[j] = g->set[prod_set].productions[prod].symbols[symbol];
                            j++;
                        }
                        for (int i = index + 1; sentinel[i] != '\0'; i++)
                        {
                            temp[j] = sentinel[i];
                            j++;
                        }
                    }
                    if (strlen(temp) - 1 > len)
                        continue;
                    if (RMD(temp, buf, len, g) == "Done")
                    {
                        if (g->set[prod_set].productions[prod].size == 0)
                        {
                            rmdappend(g->set[prod_set].symbol, "");
                        }
                        else
                        {
                            char str[MAXBUF] = {'\0'};
                            for (int symbol = 0; symbol < g->set[prod_set].productions[prod].size; symbol++)
                            {
                                str[symbol] = g->set[prod_set].productions[prod].symbols[symbol];
                            }
                            rmdappend(g->set[prod_set].symbol, str);
                        }
                        return "Done";
                    }
                    else
                        continue;
                }
            }
        }
        return "dead";
    }
}

// to replace the first occuring character with a substring
void firstReplace(char *old, char toReplace, char *new)
{
    char t[MAXBUF];
    int index;
    for (index = 0; old[index] != '\0'; index++)
    {
        if (old[index] == toReplace)
            break;
    }
    for (int i = 0; i < index; i++)
        t[i] = old[i];
    int j = index;
    for (int i = 0; new[i] != '\0'; i++)
    {
        t[j] = new[i];
        j++;
    }
    for (int i = index + 1; old[i] != '\0'; i++)
    {
        t[j] = old[i];
        j++;
    }
    for (int i = 0; i < j; i++)
    {
        old[i] = t[i];
    }
}

// to replace the last occuring character with a substring
void lastReplace(char *old, char toReplace, char *new)
{
    char t[MAXBUF];
    int index, counter = 0;
    for (int i = 0; old[i] != '\0'; i++)
    {
        counter++;
    }
    for (index = counter - 1; index >= 0; index--)
    {
        if (old[index] == toReplace)
            break;
    }
    for (int i = 0; i < index; i++)
        t[i] = old[i];
    int j = index;
    for (int i = 0; new[i] != '\0'; i++)
    {
        t[j] = new[i];
        j++;
    }
    for (int i = index + 1; old[i] != '\0'; i++)
    {
        t[j] = old[i];
        j++;
    }
    for (int i = 0; i < j; i++)
    {
        old[i] = t[i];
    }
}

int main()
{
    Grammar g;
    char ch;
    char prod[MAXBUF];
    char buf[MAXBUF];
    char sentinel[MAXBUF], temp[MAXBUF], tmp[MAXBUF];
    grammar_init(&g);
    setbuf(stdout, 0);
    printf("To enter the productions of your grammar:\n");
    setbuf(stdout, 0);
    printf("Enter a nonterminal (capital letter), then a space followed by the contents of its production, then press Enter when done. Enter each alternate production on a separate line. \nEnter ! followed by a newline to stop.\n");
    setbuf(stdout, 0);
    printf("Use the # symbol after a nonterminal to denote an epsilon production:\n\n");
    while (1)
    {
        ch = getchar();
        if (ch == '!')
        {
            break;
        }
        scanf("%s", prod);
        grammar_insert_rule(&g, ch, prod);
        // Flush input
        flush();
    }
    // Flush input
    flush();
    printf("\nEnter the starting symbol: ");
    scanf("%c", &ch);
    // Flush input
    flush();
    grammar_set_starting_symbol(&g, ch);
    sentinel[0] = ch;
    temp[0] = ch;
    if (grammar_finish(&g) < 0)
    {
        printf("Error: Grammar not properly defined.");
        return 1;
    }
    printf("\nInput Grammar Contents:\n=======================\n");
    grammar_print(&g);
    printf("\nEnter a string to parse using the given CFG: ");
    fgets(buf, MAXBUF, stdin);
    len = strlen(buf) - 1;
    buf[len] = '\0';
    bool flag = false;
    for (int prod_set = 0; prod_set < g.size; prod_set++)
    {
        if (!g.set[prod_set].occupied)
            continue;
        for (int prod = 0; prod < g.set[prod_set].size; prod++)
        {
            if (!g.set[prod_set].productions[prod].occupied)
                continue;
            if (g.set[prod_set].productions[prod].size == 0)
            {
                len += 15;
                flag = true;
                break;
            }
        }
        if (flag == true)
            break;
    }
    LMD(sentinel, buf, len, &g);
    RMD(sentinel, buf, len, &g);
    // if not accepted
    if (lmdpointer == 0 && rmdpointer == 0)
    {
        printf("String not accepted by the Grammar.\n");
    }
    // if accepted, print the LMD and RMD
    else
    {
        printf("LMD is :\n%c => ", ch);
        for (int i = lmdpointer - 1; i >= 0; i--)
        {
            firstReplace(temp, lmdnonterminal[i], lmd[i]);
            printf("%s", temp);
            if (i != 0)
            {
                printf(" => ");
            }
        }
        printf("\nRMD is :\n%c => ", ch);
        tmp[0] = ch;
        for (int i = rmdpointer - 1; i >= 0; i--)
        {
            lastReplace(tmp, rmdnonterminal[i], rmd[i]);
            printf("%s", tmp);
            if (i != 0)
            {
                printf(" => ");
            }
        }
    }
    return 0;
}