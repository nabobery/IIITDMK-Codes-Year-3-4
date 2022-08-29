/*
You are provided with a series of 1 to n (Take Input from User) natural numbers. Write a program where parent process will display the
sum of the even numbers (EVEN_SUM) present between 1 to n and the child process will display the sum of odd numbers (ODD_SUM) present
between 1 to n.
 */
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <unistd.h>

// main driver program
int main()
{
    int n, oddSum = 0, evenSum = 0, pid, i;
    printf("Please enter the number of natural numbers \n");
    scanf("%d", &n);
    // get pid from fork, if pid = 0 it's child else parent process
    pid = fork();
    // parent process to find sum of even natural numbers
    if (pid > 0)
    {
        for (i = 2; i <= n; i++)
        {
            // if even
            if (i % 2 == 0)
                evenSum += i;
        }
        // print parent process process id
        printf("Parent process with pid %d\n", getpid());
        printf("Sum of even natural numbers till %d is %d\n", n, evenSum);
    }
        // child process to find sum of odd natural numbers
    else
    {
        for (i = 1; i <= n; i++)
        {
            // if odd
            if (i % 2 != 0)
                oddSum += i;
        }
        // print child process process id
        printf("Child process with pid %d\n", getpid());
        printf("Sum of odd natural numbers till %d is %d\n", n, oddSum);
    }
    return 0;
}

