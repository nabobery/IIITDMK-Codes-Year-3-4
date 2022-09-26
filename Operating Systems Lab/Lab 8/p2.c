// Write a program to create a thread. The thread prints numbers from 0 to n, where value of n is passed from the main process to the thread.
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// function to print numbers from 0 to n using thread
void *printNumber(void *arg)
{
    int *ptr = arg;
    printf("Inside the Thread printing numbers from 0 to %d\n", *ptr);
    for (int i = 0; i <= *ptr; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    return NULL;
}

int main()
{
    pthread_t t_id;
    int n;
    // get n from user input
    printf("Please enter the Number you want to print upto: ");
    scanf("%d", &n);
    int *ptr = malloc(sizeof(int));
    ptr = &n;
    // create thread
    pthread_create(&t_id, NULL, printNumber, ptr);
    // wait for the thread to terminate
    pthread_join(t_id, NULL);
    return 0;
}