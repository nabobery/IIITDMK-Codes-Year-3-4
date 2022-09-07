// This code is done by CS20B1044 Avinash R Changrani
/*
Given a CFG as an input file in which each line is having exactly one production rule and epsilon as #,  (NT-Capital letters, T-small letters).
Also given an input string containing set of terminals (T-small letters).

Write a c program for the LL(1) parsing.

Following things are expected from your program.
1. Constructing LL(1) parsing table based on the already computed first sets of non-terminals in the previous lab (CD LAB5).
2. Identifying whether the given CFG is LL(1) or not.
3. If yes, then implement the LL(1) parsing by making use of stack and LL(1) parsing table as discussed in the class.
4. If the given CFG is not LL(1), then you can print it without parsing.
5. If the given CFG is LL(1), then your program should give the output as whether the given string is accepted or not.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUF 4096
#define PRODSETMAXALLOCSIZE 20
#define PRODMAXALLOCSIZE 10
#define SYMBOLMAXALLOCSIZE 10
#define NUM_CAPITAL_LETTERS ('Z' - 'A' + 1)

// This allows us to address elements of a 26-element array with letters
#define N_INDEX(x) ((x) - 'A')

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

typedef struct FirstRecord
{
    char data;
    int productions[20];
    int productions_top;
} FirstRecord;

typedef struct FirstFollowRecord
{
    FirstRecord first[20];
    int first_top;
    char follow[20];
    int follow_top;
    int visited;
} FirstFollowRecord;

typedef struct FirstFollowTable
{
    FirstFollowRecord ffr[NUM_CAPITAL_LETTERS];
    int size;
} FirstFollowTable;

typedef struct ParsingTable
{
    char symbols[20];
    int num_symbols;
    int num_nonterminals;
    char nonterminals[20];
    int productions[20][20][10];
    int productions_top[20][20];
} ParsingTable;

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

void production_print(Production *p)
{
    if (p->size == 0)
    {
        printf("<epsilon>");
        return;
    }
    for (int symbol = 0; symbol < p->size; symbol++)
    {
        printf("%c", p->symbols[symbol]);
    }
}

void production_print_small(Production *p)
{
    if (p->size == 0)
    {
        printf("@");
        return;
    }
    for (int symbol = 0; symbol < p->size; symbol++)
    {
        printf("%c", p->symbols[symbol]);
    }
}

void grammar_insert_internal(ProductionSet *p, char *rule)
{
    Production *production;
    p->size++;
    production = &p->productions[p->size - 1];
    production_init(production);
    if (rule[0] == '@')
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

// Checks if the grammar has been properly defined or not. Returns less than 0 on failure
int grammar_finish(Grammar *g)
{
    // Cannot proceed without a starting symbol.
    if (g->starting_symbol == '\0')
        return -1;
    grammar_calculate_nullable(g);
    return 0;
}

int grammar_remove_left_recursive_productions(Grammar *g)
{
    // Newly generated nonterminals will start with the following letter.
    char new_nonterminal = 'Z';
    int symbol;
    // Boolean flag describing whether LR exists or not.
    int lr_exists = 0;
    int lrstack[10];
    int lrstack_top = 0;
    int non_lrstack[10];
    int non_lrstack_top = 0;
    // We need not look past the old size, since any new that are inserted are known to be non LR.
    int old_grammar_size = g->size;
    for (int prodset = 0; prodset < old_grammar_size; prodset++)
    {
        // Reset stacks
        lrstack_top = 0;
        non_lrstack_top = 0;
        for (int prod = 0; prod < g->set[prodset].size; prod++)
        {
            // Iterate until we get a symbol
            symbol = 0;
            if (g->set[prodset].productions[prod].symbols[symbol] ==
                g->set[prodset].symbol)
            {
                // LR Produciton detected.
                // Push to stack.
                lr_exists = 1;
                lrstack_top++;
                lrstack[lrstack_top - 1] = prod;
            }
            else
            {
                // Non LR Produciton detected.
                // Push to other stack.
                non_lrstack_top++;
                non_lrstack[non_lrstack_top - 1] = prod;
            }
        }
        // Is recursion nonterminating? i.e. are there no non LR productions?
        if (lrstack_top > 0 && non_lrstack_top == 0)
        {
            printf("Infinite loop detected in productions. Aborting.\n");
            abort();
        }
        if (lrstack_top == 0)
        {
            // No LR productions detected for this nonterminal. Continue.
            continue;
        }
        int new_prodset;
        // Introduce the new nonterminal
        g->size++;
        new_prodset = g->size - 1;
        production_set_init(&g->set[new_prodset], new_nonterminal);
        // Now deal with each LR production
        for (int i = 0; i < lrstack_top; i++)
        {
            // Add a new production to the auxiliary nonterminal
            g->set[new_prodset].size++;
            production_init(&g->set[new_prodset].productions[g->set[new_prodset].size - 1]);
            Production *p = &g->set[new_prodset].productions[g->set[new_prodset].size - 1];
            // Alias for old production
            Production *old_p = &g->set[prodset].productions[lrstack[i]];
            // For each production, copy the second symbol onwards onto the new production in the auxiliary nonterminal
            int first_reached = 0;
            for (int j = 0; j < g->set[prodset].productions[lrstack[i]].size; j++)
            {
                if (!first_reached)
                {
                    // Skip the first symbol, which is the nonterminal that leads to the LR
                    first_reached = 1;
                    continue;
                }
                p->size++;
                p->symbols[p->size - 1] = old_p->symbols[j];
            }
            // Insert the last symbol (which is the nonterminal).
            p->size++;
            p->symbols[p->size - 1] = new_nonterminal;
            // Delete the old LR production.
            old_p->occupied = 0;
        }
        for (int j = 0; j < non_lrstack_top; j++)
        {
            // For each non LR production, push a production to the original production set that replaces the concerned production
            Production *old_r = &g->set[prodset].productions[non_lrstack[j]];
            g->set[prodset].size++;
            production_init(&g->set[prodset].productions[g->set[prodset].size - 1]);
            Production *r = &g->set[prodset].productions[g->set[prodset].size - 1];
            for (int k = 0; k < old_r->size; k++)
            {
                r->size++;
                r->symbols[r->size - 1] = old_r->symbols[k];
            }
            // Insert the last symbol (which is the nonterminal).
            r->size++;
            r->symbols[r->size - 1] = new_nonterminal;
        }
        // Delete the non LR productions
        for (int i = 0; i < non_lrstack_top; i++)
        {
            g->set[prodset].productions[non_lrstack[i]].occupied = 0;
        }
        // Insert the epsilon production. Nothing needs to be done aside from init since here epsilon i simply represented as an empty production.
        g->set[new_prodset].size++;
        production_init(&g->set[new_prodset].productions[g->set[new_prodset].size - 1]);
        // Decrement to a new identifier
        new_nonterminal--;
    }
    // Return whether LR exists or not.
    return lr_exists;
}

int lookup_symbol(FirstRecord *list, int *list_top, char c)
{
    for (int i = 0; i < *list_top; i++)
    {
        if (list[i].data == c)
            return i;
    }
    *list_top += 1;
    return *list_top - 1;
}

int duplicate_exists(FirstRecord *list, int list_top, char c)
{
    for (int i = 0; i < list_top; i++)
    {
        if (list[i].data == c)
            return 1;
    }
    return 0;
}

int duplicate_exists_int(int *list, int list_top, int s)
{
    for (int i = 0; i < list_top; i++)
    {
        if (list[i] == s)
            return 1;
    }
    return 0;
}

int grammar_get_first(Grammar *g, char nonterminal, FirstFollowTable *ft)
{
    int index;
    int first_symbol = 0;
    int epsilon_flag = 0;
    int epsilon_set = -1;
    int child_epsilon_flag = 0;
    int prodset = grammar_find(g, nonterminal);
    int *first_top = &ft->ffr[N_INDEX(nonterminal)].first_top;
    FirstRecord *first = ft->ffr[N_INDEX(nonterminal)].first;
    // We have already dealt with this nonterm before. Return while saying whether it has an epsilon or not.
    if (ft->ffr[N_INDEX(nonterminal)].visited)
    {
        return g->set[prodset].nullable;
    }
    ft->ffr[N_INDEX(nonterminal)].visited = 1;
    for (int prod = 0; prod < g->set[prodset].size; prod++)
    {
        if (!g->set[prodset].productions[prod].occupied)
        {
            continue;
        }
        first_symbol = 0;
        if (g->set[prodset].productions[prod].size == 0)
        {
            // This is an epsilon production
            if (epsilon_set < 0)
            {
                (*first_top)++;
                epsilon_set = *first_top - 1;
                first[epsilon_set].data = '@';
            }
            // printf("Setting Epsilon at for NT '%c'\n", nonterminal);
            if (duplicate_exists_int(first[epsilon_set].productions, first[epsilon_set].productions_top, prod))
            {
                continue;
            }
            first[epsilon_set].productions_top++;
            first[epsilon_set].productions[first[epsilon_set].productions_top - 1] = prod;
            epsilon_flag = 1;
        }
        else if (is_nonterminal(g->set[prodset].productions[prod].symbols[first_symbol]))
        {
            // Recurse until we arrive at a terminal and get all the firsts
            int ret;
            // printf("Recursing\n");
            // The while loop breaks if we get a terminal or non epsilon production nonterminal.
            while (first_symbol < g->set[prodset].productions[prod].size)
            {
                // printf("Iteration at %c of %c\n", g->set[prodset].productions[prod].symbols[first_symbol], nonterminal);
                // If this is a terminal, we stop here and set this.
                if (is_terminal(g->set[prodset].productions[prod].symbols[first_symbol]))
                {
                    child_epsilon_flag = 0;
                    if (duplicate_exists(first, *first_top, g->set[prodset].productions[prod].symbols[first_symbol]))
                    {
                        // printf("Setting first '%c' for NT '%c' but it already exists in set.\n",
                        // g->set[prodset].productions[prod].symbols[first_symbol], nonterminal);
                        break;
                    }
                    index = lookup_symbol(first, first_top, g->set[prodset].productions[prod].symbols[first_symbol]);
                    first[index].data = g->set[prodset].productions[prod].symbols[first_symbol];
                    first[index].productions_top++;
                    first[index].productions[first[index].productions_top - 1] = prod;
                    // printf("Setting first '%c' for NT '%c'\n", g->set[prodset].productions[prod].symbols[first_symbol], nonterminal);
                    break;
                }
                // let's detect whether this is an infinite recursion
                if (g->set[prodset].productions[prod].symbols[first_symbol] == nonterminal)
                {
                    // printf("Right or left recursive production detected. Switching to a non right recursive one.\n");
                    if (g->set[prodset].nullable)
                    {
                        first_symbol++;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                ret = grammar_get_first(g, g->set[prodset].productions[prod].symbols[first_symbol], ft);
                // Then copy over all the firsts of the nonterminal to this one.
                int *i_first_top = &ft->ffr[N_INDEX(g->set[prodset].productions[prod].symbols[first_symbol])].first_top;
                FirstRecord *i_first = ft->ffr[N_INDEX(g->set[prodset].productions[prod].symbols[first_symbol])].first;
                child_epsilon_flag = 0;
                for (int i = 0; i < *i_first_top; i++)
                {
                    if (i_first[i].data == '@')
                    {
                        // skip epsilon
                        child_epsilon_flag = 1;
                        continue;
                    }
                    // printf("Setting first '%c' for NT '%c'\n", i_first[i].data, nonterminal);
                    index = lookup_symbol(first, first_top, i_first[i].data);
                    if (duplicate_exists_int(first[index].productions, first[index].productions_top, prod))
                    {
                        continue;
                    }
                    first[index].data = i_first[i].data;
                    first[index].productions_top++;
                    first[index].productions[first[index].productions_top - 1] = prod;
                }
                if (!ret)
                {
                    break;
                }
                // printf("Epsilon detected. Going Further.\n");
                child_epsilon_flag = 1;
                first_symbol++;
            } // END while
            // This means that we have had a nonterminal at the end of the production which has an epsilon production.We therefore add in an epsilon as a first.
            if (child_epsilon_flag)
            {
                child_epsilon_flag = 0;
                if (epsilon_set < 0)
                {
                    (*first_top)++;
                    epsilon_set = *first_top - 1;
                    first[epsilon_set].data = '@';
                }
                if (duplicate_exists_int(first[epsilon_set].productions, first[epsilon_set].productions_top, prod))
                {
                    continue;
                }
                first[epsilon_set].productions_top++;
                first[epsilon_set].productions[first[epsilon_set].productions_top - 1] = prod;
                epsilon_flag = 1;
            }
        }
        else
        {
            // This is a terminal. Simply add it to the firsts list.
            index = lookup_symbol(first, first_top, g->set[prodset].productions[prod].symbols[first_symbol]);
            if (duplicate_exists_int(first[index].productions, first[index].productions_top, prod))
            {
                continue;
            }
            first[index].data = g->set[prodset].productions[prod].symbols[first_symbol];
            first[index].productions_top++;
            first[index].productions[first[index].productions_top - 1] = prod;
            first_symbol++;
        } // END if
    }     // END for
    return epsilon_flag;
}

int duplicate_exists_char(char *list, int list_top, char c)
{
    for (int i = 0; i < list_top; i++)
    {
        if (list[i] == c)
            return 1;
    }
    return 0;
}

int grammar_get_follow(Grammar *g, FirstFollowTable *ft)
{
    int nonterminal_found;
    int at_last;
    int continue_probing;
    for (int prod_set = 0; prod_set < g->size; prod_set++)
    {
        if (!g->set[prod_set].occupied)
            continue;
        int *follow_top = &ft->ffr[N_INDEX(g->set[prod_set].symbol)].follow_top;
        char *follow = ft->ffr[N_INDEX(g->set[prod_set].symbol)].follow;
        for (int i_prod_set = 0; i_prod_set < g->size; i_prod_set++)
        {
            if (!g->set[i_prod_set].occupied)
                continue;
            for (int prod = 0; prod < g->set[i_prod_set].size; prod++)
            {
                if (!g->set[i_prod_set].productions[prod].occupied)
                    continue;
                nonterminal_found = 0;
                at_last = 1;
                for (int symbol = 0; symbol < g->set[i_prod_set].productions[prod].size; symbol++)
                {
                    if (!nonterminal_found &&
                        g->set[i_prod_set].productions[prod].symbols[symbol] == g->set[prod_set].symbol)
                    {
                        nonterminal_found = 1;
                        continue_probing = 1;
                        continue;
                    }
                    if (!nonterminal_found)
                        continue;
                    at_last = 0;
                    continue_probing = 0;
                    if (is_terminal(g->set[i_prod_set].productions[prod].symbols[symbol]))
                    {
                        // Add terminal as the follow and exit
                        if (!duplicate_exists_char(follow, *follow_top, g->set[i_prod_set].productions[prod].symbols[symbol]))
                        {
                            (*follow_top)++;
                            follow[*follow_top - 1] = g->set[i_prod_set].productions[prod].symbols[symbol];
                        }
                        break;
                    }
                    char target = g->set[i_prod_set].productions[prod].symbols[symbol];
                    for (int i = 0; i < ft->ffr[N_INDEX(target)].first_top; i++)
                    {
                        if (ft->ffr[N_INDEX(target)].first[i].data == '@')
                        {
                            // If epsilon, we need to continue probing
                            continue_probing = 1;
                            continue;
                        }
                        if (duplicate_exists_char(follow, *follow_top, ft->ffr[N_INDEX(target)].first[i].data))
                        {
                            continue;
                        }
                        (*follow_top)++;
                        follow[*follow_top - 1] = ft->ffr[N_INDEX(target)].first[i].data;
                    }
                    if (!continue_probing)
                        break;
                }
                if (nonterminal_found && (at_last || continue_probing))
                {
                    // This means that our nonterminal is the last symbol in this production.
                    // Copy over all follows of this production.
                    char target = g->set[i_prod_set].symbol;
                    // If the production is right linear, this will run till infinity. Hence we stop it here.
                    if (target == g->set[prod_set].symbol)
                    {
                        // printf("= Right linear production detected.\n");
                        // (*follow_top)++;
                        // follow[*follow_top - 1] = '$';
                    }
                    else
                    {
                        for (int i = 0; i < ft->ffr[N_INDEX(target)].follow_top; i++)
                        {
                            if (duplicate_exists_char(follow, *follow_top, ft->ffr[N_INDEX(target)].follow[i]))
                            {
                                continue;
                            }
                            (*follow_top)++;
                            follow[*follow_top - 1] = ft->ffr[N_INDEX(target)].follow[i];
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void print_firstfollow(FirstFollowTable *ft)
{
    printf("NT\tFIRST\tFOLLOW\n");
    for (int i = 0; i < NUM_CAPITAL_LETTERS; i++)
    {
        if (!ft->ffr[i].visited)
            continue;

        printf("%c\t", 'A' + i);
        int j;
        // Comma list
        for (j = 0; j < ft->ffr[i].first_top - 1; j++)
        {
            printf("%c,", ft->ffr[i].first[j].data);
        }
        // End of Comma list
        if (ft->ffr[i].first_top > 0)
            printf("%c", ft->ffr[i].first[j].data);

        printf("\t");
        // Comma list
        for (j = 0; j < ft->ffr[i].follow_top - 1; j++)
        {
            printf("%c,", ft->ffr[i].follow[j]);
        }
        // End of Comma list
        if (ft->ffr[i].follow_top > 0)
            printf("%c", ft->ffr[i].follow[j]);

        printf("\n");
    }
    printf("Here:\n"
           "    '@' is the epsilon symbol.\n"
           "    '$' is the end-of-stream symbol.");
    printf("\n");
}

void grammar_generate_parsing_table(FirstFollowTable *ft, ParsingTable *table, Grammar *g)
{
    int epsilon_flag;
    int epsilon_set;
    for (int prodset = 0; prodset < g->size; prodset++)
    {
        epsilon_flag = 0;
        // printf("Processing %c\n", g->set[prodset].symbol);
        for (int i = 0;
             i < ft->ffr[N_INDEX(g->set[prodset].symbol)].first_top;
             i++)
        {
            // printf("Getting %c\n", ft->ffr[N_INDEX(g->set[prodset].symbol)].first[i].data);
            if (ft->ffr[N_INDEX(g->set[prodset].symbol)].first[i].data == '@')
            {
                // printf("Epsilon. Skipping\n");
                epsilon_flag = 1;
                epsilon_set = i;
                continue;
            }
            int symbol_i;
            // Insert or get terminal index
            for (symbol_i = 0; symbol_i < table->num_symbols; symbol_i++)
            {
                if (table->symbols[symbol_i] == ft->ffr[N_INDEX(g->set[prodset].symbol)].first[i].data)
                {
                    // printf("Found %c\n", ft->ffr[N_INDEX(g->set[prodset].symbol)].first[i].data);
                    break;
                }
            }
            if (symbol_i == table->num_symbols)
            {
                table->num_symbols++;
                table->symbols[table->num_symbols - 1] = ft->ffr[N_INDEX(g->set[prodset].symbol)].first[i].data;
                // printf("Inserting %c\n", ft->ffr[N_INDEX(g->set[prodset].symbol)].first[i].data);
            }
            int nonterminal_i;
            // Insert or get nonterminal symbol index
            for (nonterminal_i = 0; nonterminal_i < table->num_nonterminals; nonterminal_i++)
            {
                if (table->nonterminals[nonterminal_i] == g->set[prodset].symbol)
                {
                    break;
                }
            }
            if (nonterminal_i == table->num_nonterminals)
            {
                table->num_nonterminals++;
                table->nonterminals[table->num_nonterminals - 1] = g->set[prodset].symbol;
            }
            // printf("><><>< %d\n", ft->ffr[N_INDEX(g->set[prodset].symbol)].first[i].production);
            for (int k = 0; k < ft->ffr[N_INDEX(g->set[prodset].symbol)].first[i].productions_top; k++)
            {
                table->productions_top[nonterminal_i][symbol_i]++;
                table->productions[nonterminal_i][symbol_i][table->productions_top[nonterminal_i][symbol_i] - 1] =
                    ft->ffr[N_INDEX(g->set[prodset].symbol)].first[i].productions[k];
            }
        }
        // If epsilon is available, add in the follow terms
        if (epsilon_flag)
        {
            for (int i = 0; i < ft->ffr[N_INDEX(g->set[prodset].symbol)].follow_top; i++)
            {
                int symbol_i;
                // Insert or get terminal index
                for (symbol_i = 0; symbol_i < table->num_symbols; symbol_i++)
                {
                    if (table->symbols[symbol_i] == ft->ffr[N_INDEX(g->set[prodset].symbol)].follow[i])
                    {
                        // printf("Found e %c\n", ft->ffr[N_INDEX(g->set[prodset].symbol)].follow[i]);
                        break;
                    }
                }
                if (symbol_i == table->num_symbols)
                {
                    table->num_symbols++;
                    table->symbols[table->num_symbols - 1] = ft->ffr[N_INDEX(g->set[prodset].symbol)].follow[i];
                    // printf("Inserting e %c\n", ft->ffr[N_INDEX(g->set[prodset].symbol)].follow[symbol_i]);
                }
                int nonterminal_i;
                // Insert or get nonterminal symbol index
                for (nonterminal_i = 0; nonterminal_i < table->num_nonterminals; nonterminal_i++)
                {
                    if (table->nonterminals[nonterminal_i] == g->set[prodset].symbol)
                    {
                        break;
                    }
                }
                if (nonterminal_i == table->num_nonterminals)
                {
                    table->num_nonterminals++;
                    table->nonterminals[table->num_nonterminals - 1] = g->set[prodset].symbol;
                }
                // We simply represent the epsilon production as -1.
                // table->productions[nonterminal_i][symbol_i][table->productions_top[nonterminal_i][symbol_i] - 1] = -1;
                for (int k = 0; k < ft->ffr[N_INDEX(g->set[prodset].symbol)].first[epsilon_set].productions_top; k++)
                {
                    // Check for duplicated
                    for (int m = 0; m < table->productions_top[nonterminal_i][symbol_i]; m++)
                    {
                        if (table->productions[nonterminal_i][symbol_i][m] == ft->ffr[N_INDEX(g->set[prodset].symbol)].first[epsilon_set].productions[k])
                            goto next_thing;
                    }
                    table->productions_top[nonterminal_i][symbol_i]++;
                    table->productions[nonterminal_i][symbol_i][table->productions_top[nonterminal_i][symbol_i] - 1] =
                        ft->ffr[N_INDEX(g->set[prodset].symbol)].first[epsilon_set].productions[k];
                next_thing:
                    continue;
                }
            }
        }
    }
}

int parsing_table_print(Grammar *g, ParsingTable *table)
{
    printf("NT\t");
    char is_ll1 = 1;
    for (int i = 0; i < table->num_symbols; i++)
    {
        printf("%c\t", table->symbols[i]);
    }
    printf("\n");
    for (int i = 0; i < table->num_nonterminals; i++)
    {
        printf("%c\t", table->nonterminals[i]);
        for (int j = 0; j < table->num_symbols; j++)
        {
            if (table->productions_top[i][j] == 0)
            {
                printf("_");
            }
            else
            {
                if (table->productions_top[i][j] > 1)
                {
                    is_ll1 = 0;
                }
                // printf("(%d)", table->productions[i][j]);
                for (int k = 0; k < table->productions_top[i][j] - 1; k++)
                {
                    production_print_small(&g->set[grammar_find(g, table->nonterminals[i])].productions[table->productions[i][j][k]]);
                    printf(",");
                }
                production_print_small(&g->set[grammar_find(g, table->nonterminals[i])].productions[table->productions[i][j][table->productions_top[i][j] - 1]]);
            }
            printf("\t");
        }
        printf("\n");
    }
    printf("Here:\n    '@' is the epsilon symbol."
           "\n    '$' is the end-of-stream symbol."
           "\n    '_' indicates a lack of a production.");
    if (!is_ll1)
    {
        printf("\n\nGrammar is NOT an LL1 Grammar.\nMultiple Deriviations are shown separated by commas.");
    }
    else
    {
        printf("\n\nGrammar is an LL1 Grammar.");
    }
    printf("\n");
    return is_ll1;
}

Production *get_prediction(Grammar *g, ParsingTable *p, char nonterminal, char symbol)
{
    int nt_index = -1;
    int s_index = -1;
    int prod = -1;
    int prodset = grammar_find(g, nonterminal);
    if (prodset == -1)
    {
        printf("Nonterminal does not exist.\n");
    }
    for (int i = 0; i < p->num_nonterminals; i++)
    {
        if (p->nonterminals[i] == nonterminal)
        {
            nt_index = i;
            break;
        }
    }
    if (nt_index == -1)
    {
        printf("NT not found\n");
        return NULL;
    }
    for (int i = 0; i < p->num_symbols; i++)
    {
        if (p->symbols[i] == symbol)
        {
            s_index = i;
            break;
        }
    }
    if (s_index == -1)
    {
        printf("Symbol not found\n");
        return NULL;
    }
    if (p->productions_top[nt_index][s_index] != 1)
    {
        printf("No valid prediction exists for the given symbol.\n");
        return NULL;
    }
    prod = p->productions[nt_index][s_index][0];
    return &g->set[prodset].productions[prod];
}

int mystrlen(char *p)
{
    int c = 0;
    while (*p != '\0')
    {
        c++;
        *p++;
    }
    return (c);
}

void grammar_input_check(Grammar *g, ParsingTable *p, char *input)
{
    // Stack
    char pred_stack[MAXBUF];
    int pred_stack_top = 0;
    // Current symbol.
    char curr_symbol = '\0';
    int input_offset = 0, size = mystrlen(input);
    // Iteration number of the loop. Just for cosmetic purposes.
    int iter_count = 1;
    // Production pointer
    Production *prod_ptr;
    // Push the starting symbol to the stack.
    pred_stack_top++;
    pred_stack[pred_stack_top - 1] = g->starting_symbol;
    if (input[0] == '\0')
    {
        printf("Empty String. Exiting.\n");
        return;
    }
    while (pred_stack_top > 0)
    {
        // Print iteration Number
        printf("ITERATION NO.: %d\n", iter_count);
        // Print Stack Number
        printf("STACK        : ");
        printf("[ ");
        for (int i = 0; i < pred_stack_top; i++)
        {
            printf("%c ", pred_stack[i]);
        }
        printf("]\n");
        // Because of fgets, we assume input ends on a '\n'
        if (input[input_offset] == '\n' || input[input_offset] == '\0')
        {
            printf("INPUT SYMBOL : Input Exhausted ('$')\n");
        }
        else
        {
            printf("INPUT SYMBOL : '%c'\n", input[input_offset]);
        }
        // Pop stack and put in current symbol
        curr_symbol = pred_stack[pred_stack_top - 1];
        pred_stack_top--;
        if (is_nonterminal(curr_symbol))
        {
            printf("Nonterminal '%c' expected.\n", curr_symbol);
            // Because of fgets, we assume input ends on a '\n'
            if (input[input_offset] == '\n' || input[input_offset] == '\0')
            {
                printf("(Input has been exhausted. This will be represented as the '$' symbol)\n");
                prod_ptr = get_prediction(g, p, curr_symbol, '$');
            }
            else
            {
                prod_ptr = get_prediction(g, p, curr_symbol, input[input_offset]);
            }
            if (prod_ptr == NULL)
            {
                printf("No matching production found for input symbol. Input Rejected.\n");
                return;
            }
            if (prod_ptr->size == 0)
            {
                printf("Epsilon Production predicted. No input consumed. Nothing added to stack.\n");
            }
            else
            {
                printf("Expanding to predicted production '");
                production_print_small(prod_ptr);
                printf("'.\n");
                // Put elements in stack in reverse order
                for (int i = prod_ptr->size - 1; i >= 0; i--)
                {
                    pred_stack_top++;
                    pred_stack[pred_stack_top - 1] = prod_ptr->symbols[i];
                }
            }
        }
        else
        {
            printf("Terminal '%c' expected.\n", curr_symbol);

            if (curr_symbol != input[input_offset])
            {
                printf("Input symbol is not equal to expected terminal symbol. Input Rejected.\n");
                return;
            }
            printf("Input symbol matches with expected terminal symbol. Proceeding.\n");
            input_offset++;
        }
        printf("\n");
        iter_count++;
    }
    if (input_offset == size - 1)
        printf("Stack Empty. Input Accepted.\n");
    else
        printf("Input Rejected \n");
}

// Input Flush
void flush()
{
    int c;
    while (((c = getchar()) != EOF) && (c != '\n'))
        ;
}

int main()
{
    Grammar g;
    ParsingTable table;
    FirstFollowTable ft = {0};
    char ch;
    char prod[MAXBUF];
    char buf[MAXBUF];
    grammar_init(&g);
    printf("To enter the productions of your grammar:\n");
    printf("Enter a nonterminal (capital letter), then a space followed by the contents of its production, then press Enter when done. Enter each alternate production on a separate line. \nEnter any letter aside from A - Z followed by a newline to stop.\n");
    printf("Use the @ symbol after a nonterminal to denote an epsilon production:\n\n");
    while (1)
    {
        ch = getchar();
        if (ch < 'A' || ch > 'Z')
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
    if (grammar_finish(&g) < 0)
    {
        printf("Error: Grammar not properly defined.");
        return 1;
    }
    printf("\nInput Grammar Contents:\n=======================\n");
    grammar_print(&g);
    printf("\n");
    int lr_exists = grammar_remove_left_recursive_productions(&g);
    if (lr_exists)
    {
        printf("\nGrammar After Removing Left Recursions:\n=======================================\n");
        grammar_print(&g);
    }
    for (int i = 0; i < g.size; i++)
    {
        if (g.set[i].occupied)
            grammar_get_first(&g, g.set[i].symbol, &ft);
    }
    ft.ffr[N_INDEX(ch)].follow_top++;
    ft.ffr[N_INDEX(ch)].follow[ft.ffr[N_INDEX(ch)].follow_top - 1] = '$';
    grammar_get_follow(&g, &ft);
    grammar_get_follow(&g, &ft);
    grammar_generate_parsing_table(&ft, &table, &g);
    printf("\nFirst-Follow Set Table:\n========================\n");
    print_firstfollow(&ft);
    printf("\nLL1 Parsing Table:\n"
           "=================\n");
    int is_ll1 = parsing_table_print(&g, &table);
    if (!is_ll1)
    {
        printf("Cannot perform LL1 parsing with given grammar. Exiting.\n");
        return 0;
    }
    printf("\nEnter an expression to parse: ");
    fgets(buf, MAXBUF, stdin);
    grammar_input_check(&g, &table, buf);
    return 0;
}