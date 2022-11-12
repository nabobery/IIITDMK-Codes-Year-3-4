/*
Question : Given the network with 'n' nodes (n > 4) and "e" weighted edges. Simulate the "Link State Routing Algorithm", 
to find the shortest path between nodes.
*/

// This program is done by CS20B1044 Avinash R Changrani

// including the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Nodes are from 1,2,.... n
int n;

// function for printing Matrix
void printMatrix(int mat[n+1][n+1]){
    for(int i = 1; i <= n;i++){
        for(int j = 1; j <= n;j++){
            if(mat[i][j] < INT_MAX) printf("%d ", mat[i][j]);
            else printf("INF ");
        }
        printf("\n");
    }
}

// function for getting the node which is unvisited and is the current nearest node
int getmindistancenode(bool visited[], int distance[]){
    int min = INT_MAX, ind;
    for(int i = 1; i <= n;i++){
        // update the min distance and node
        if(visited[i] ==  false && distance[i] < min){
            min = distance[i];
            ind = i;
        }
    }
    // return the node which is nearest
    return ind;
}

// link state routing algorithm which uses dijsktra to find the shortest distance between source and other nodes
void lsr(int src, int weight[n+1][n+1]){
    bool visited[n+1];
    int dist[n+1];
    // fill the visited and distance array
    for(int i = 1; i <= n;i++){
        visited[i] = false;
        dist[i] = weight[src][i];
    }
    // set visited(src) as true
    visited[src] = true;
    for(int i = 2; i <= n;i++){
        // find the shortest current edge and proceed greedily
        int k = getmindistancenode(visited,dist);
        visited[k] = true;
        // check if after visiting the nearest node, we can get any shortest path between src and other nodes and update the distance
        for(int j = 1; j <= n;j++){
            if(visited[j] == false && weight[k][j] != INT_MAX && (dist[j] > (dist[k] + weight[k][j]))){
                dist[j] = weight[k][j] + dist[k];
            }
        }
    }
    // printing the shortest distance between source and nodes
    for(int i = 1; i <= n;i++){
        printf("Shortest Distance from node %d to node %d is %d\n", src, i, dist[i]);
        weight[src][i] = dist[i];
    }
    printf("The Weight Matrix after starting from Node %d after LSR is: \n", src);
    printMatrix(weight);
}

// main function
int main(){
    // getting input from user
    printf("Please enter the number of nodes in the network: ");
    scanf("%d", &n);
    int e,a,b,cost;
    printf("Please enter the number of edges between nodes in the network: ");
    scanf("%d", &e);
    int weight[n+1][n+1];
    // initialising weight matrix
    for(int i = 1; i <= n;i++){
        for(int j = 1; j <= n;j++){
            weight[i][j] = INT_MAX;
        }
        weight[i][i] = 0;
    }
    // getting weight matrix from user
    for(int i = 0; i < e;i++){
        printf("Please enter the Source, Destination and Cost of the Edge %d: ", i+1);
        scanf("%d %d %d", &a, &b, &cost);
        weight[a][b] = cost;
        weight[b][a] = cost;
    }
    printf("The Initial Weight Matrix before Link State Routing Algorithm is: \n");
    printMatrix(weight);
    // printing the weight matrix after each iteration of lsr
    for(int i = 1; i <= n;i++){
        lsr(i,weight);
    }
    // printing the final weight matrix
    printf("The Final Weight Matrix after Link State Routing Algorithm is: \n");
    printMatrix(weight);
    return 0;
}