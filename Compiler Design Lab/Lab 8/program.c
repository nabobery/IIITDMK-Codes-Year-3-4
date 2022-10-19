/*
Given a real number in bit string representation as input, write a program to evaluate it according to the attribute evaluation strategy and give the output as a real number in decimal representation.
The following things are expected from your program
1. Assuming that the parsing tree is already known, identify the dependence graph and topological order in which the attributes are to be calculated.
2. Finally give the output as a real number in decimal representation.
*/

// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct treeNode
{
    char ch;
    struct treeNode *left;
    struct treeNode *right;
};

struct treeNode *newNode()
{
    struct treeNode *node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->ch = ' ';
    node->left = NULL;
    node->right = NULL;

    return (node);
}

void printCurrentLevel(struct treeNode *root, int level, int h);
int height(struct treeNode *node);

// Function to print level order traversal a tree
void printLevelOrder(struct treeNode *root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
    {
        for (int j = 0; j < pow(2, h - 3) - i; j++)
            printf("  ");
        printCurrentLevel(root, i, h - i);
        printf("\n\n");
    }
}

// Print nodes at a current level
void printCurrentLevel(struct treeNode *root, int level, int h)
{
    if (root == NULL)
    {
        return;
    }
    if (level == 1)
    {

        printf("\033[0;31m%c", root->ch);
    }
    else if (level > 1)
    {
        printCurrentLevel(root->left, level - 1, h);
        printf("  ");
        printCurrentLevel(root->right, level - 1, h);
    }
}

// Compute the "height" of a tree -- the number of nodes along the longest path from the root node down to the farthest leaf node.
int height(struct treeNode *node)
{
    if (node == NULL)
        return 0;
    else
    {
        // compute the height of each subtree
        int lheight = height(node->left);
        int rheight = height(node->right);
        // use the larger one
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

void main()
{
    char input[20];
    printf("Enter the Binary String: ");
    scanf("%s", input);
    // make the parse tree and find the result
    struct treeNode *head = newNode();
    struct treeNode *child1 = newNode();
    struct treeNode *child2 = newNode();
    head->ch = 'S';
    head->left = child1;
    head->right = child2;
    child1->ch = 'l';
    child2->ch = 'l';
    int count = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '.')
        {
            break;
        }
        count++;
    }
    struct treeNode *temp = head->left;
    for (int i = count - 1; i >= 0; i--)
    {
        if (i > 0)
        {
            struct treeNode *c1 = newNode();
            struct treeNode *c2 = newNode();
            temp->left = c1;
            temp->right = c2;
            struct treeNode *value = newNode();
            c2->ch = 'b';
            c2->right = NULL;
            c2->left = value;
            value->ch = input[i];
            value->left = NULL;
            value->right = NULL;
            c1->ch = 'l';
            temp = c1;
        }
        else
        {
            temp->right = NULL;
            struct treeNode *c2 = newNode();
            struct treeNode *value = newNode();
            temp->left = c2;
            c2->ch = 'b';
            c2->left = value;
            c2->right = NULL;
            value->ch = input[0];
            value->left = NULL;
            value->right = NULL;
        }
    }

    temp = head->right;
    int length = strlen(input);
    for (int i = count + 1; i < length; i++)
    {
        if (i != length - 1)
        {
            struct treeNode *c1 = newNode();
            struct treeNode *c2 = newNode();
            temp->left = c2;
            temp->right = c1;
            struct treeNode *value = newNode();
            c2->ch = 'b';
            c2->right = NULL;
            c2->left = value;
            value->ch = input[i];
            value->left = NULL;
            value->right = NULL;
            c1->ch = 'l';
            temp = c1;
        }
        else
        {
            temp->right = NULL;
            struct treeNode *c2 = newNode();
            struct treeNode *value = newNode();
            temp->left = c2;
            c2->ch = 'b';
            c2->left = value;
            c2->right = NULL;
            value->ch = input[0];
            value->left = NULL;
            value->right = NULL;
        }
    }

    printf("Level Order traversal of binary tree is \n");
    printLevelOrder(head);

    double result = 0;
    for (int i = count; i > 0; i--)
    {
        if (input[count - i] == '1')
        {
            result += pow(2, i - 1);
        }
    }
    for (int i = count + 1; i < length; i++)
    {
        if (input[i] == '1')
        {
            result += pow(2, count - i);
        }
    }
    printf("\033[0;36m"
           "\nResult: %lf\n",
           result);
}