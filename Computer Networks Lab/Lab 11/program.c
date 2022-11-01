// Implementation of Distance Vector Routing algorithm

// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define INF INT_MAX

// cell in the routing table
struct cell
{
    int dest, dist, next_hop;
};

int main()
{
    int n, from, to, d, edges;
    printf("Please Enter the number of nodes in the given network (nodes start from 1): ");
    scanf("%d", &n);
    int distance_matrix[n][n];
    printf("Please Enter the number of edges between nodes in the given network: ");
    scanf("%d", &edges);
    // initializing distance to Infinity
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            distance_matrix[i][j] = INF;
        }
        // distance from node to node is 0
        distance_matrix[i][i] = 0;
    }
    // collecting edge information from user
    for (int i = 0; i < edges; i++)
    {
        printf("Please enter the source, destination and edge cost(non negative) of edge %d: ", i + 1);
        scanf("%d %d %d", &from, &to, &d);
        distance_matrix[from - 1][to - 1] = d;
        distance_matrix[to - 1][from - 1] = d;
    }
    struct cell routing_table[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            routing_table[i][j].dest = j + 1;
            routing_table[i][j].dist = distance_matrix[i][j];
            if (routing_table[i][j].dist != INF)
                routing_table[i][j].next_hop = j + 1;
            else
                routing_table[i][j].next_hop = -1;
        }
    }
    printf("INITIAL ROUTING TABLE \n");
    // printing the routing table
    for (int i = 0; i < n; i++)
    {
        printf("Routing Table for Node %d is \n", i + 1);
        printf("Destination\tNext Hop\tDistance\n");
        for (int j = 0; j < n; j++)
        {
            printf("%d\t\t", routing_table[i][j].dest, routing_table[i][j].dist);
            if (routing_table[i][j].next_hop != -1)
                printf("%d\t\t", routing_table[i][j].next_hop);
            else
                printf("--\t\t");
            if (routing_table[i][j].dist != INF)
                printf("%d\n", routing_table[i][j].dist);
            else
                printf("INF\n");
        }
    }
    bool flag;
    do
    {
        flag = false;
        for (int k = 1; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (routing_table[i][k].dist != INF && routing_table[k][j].dist != INF)
                    {
                        if ((routing_table[i][j].dist) > (routing_table[i][k].dist + routing_table[k][j].dist))
                        {
                            routing_table[i][j].dist = (routing_table[i][k].dist + routing_table[k][j].dist);
                            routing_table[i][j].next_hop = k;
                            flag = true;
                        }
                    }
                }
            }
            // printf("ITERATION %d of the Algorithm\n", k);
            // for (int i = 0; i < n; i++)
            // {
            //     printf("Routing Table for Node %d is \n", i + 1);
            //     printf("Destination\tNext Hop\tDistance\n");
            //     for (int j = 0; j < n; j++)
            //     {
            //         printf("%d\t\t", routing_table[i][j].dest, routing_table[i][j].dist);
            //         if (routing_table[i][j].next_hop != -1)
            //             printf("%d\t\t", routing_table[i][j].next_hop);
            //         else
            //             printf("--\t\t");
            //         if (routing_table[i][j].dist != -1)
            //             printf("%d\n", routing_table[i][j].dist);
            //         else
            //             printf("INF\n");
            //     }
            // }
        }
    } while (flag == true);
    printf("FINAL ROUTING TABLE \n");
    for (int i = 0; i < n; i++)
    {
        printf("Routing Table for Node %d is \n", i + 1);
        printf("Destination\tNext Hop\tDistance\n");
        for (int j = 0; j < n; j++)
        {
            printf("%d\t\t", routing_table[i][j].dest, routing_table[i][j].dist);
            if (routing_table[i][j].next_hop != -1)
                printf("%d\t\t", routing_table[i][j].next_hop);
            else
                printf("--\t\t");
            if (routing_table[i][j].dist != -1)
                printf("%d\n", routing_table[i][j].dist);
            else
                printf("INF\n");
        }
    }
    return 0;
}