/*
You are provided with 10 numbers (Input Given by User). Write a program where parent process will display the sorted sequence of
those 10 numbers in ascending order whereas the child process will display the sorted sequence of those numbers in descending order.
*/

// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// comparator function for sorting elements in ascending order
int comparator1(const void *p, const void *q)
{
    int l = *(const int *)p;
    int r = *(const int *)q;
    return (l - r);
}

// comparator function for sorting elements in descending order
int comparator2(const void *p, const void *q)
{
    int l = *(const int *)p;
    int r = *(const int *)q;
    return (r - l);
}

int main()
{
    int arr[10];
    // get 10 elements
    printf("Please enter 10 array elements \n");
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &arr[i]);
    }
    // if child
    if (fork() == 0)
    {
        printf("Child process with pid %d\n", getpid());
        printf("The array elements in descending order is \n");
        qsort((void *)arr, 10, sizeof(arr[0]), comparator2);
        // print elements
        for (int i = 0; i < 10; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        exit(0);
    }
        // if parent
    else
    {
        // wait until child is done
        wait(NULL);
        printf("Parent process with pid %d\n", getpid());
        printf("The array elements in ascending order is \n");
        qsort((void *)arr, 10, sizeof(arr[0]), comparator1);
        // print elements
        for (int i = 0; i < 10; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    return 0;
}
