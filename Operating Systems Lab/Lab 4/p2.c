/* Write a program to create multiple processes (up to 3/4 Levels) using fork() and display their process IDs
 (getpid()) and parent process ID (getppid()) */
// This program is done by CS20B1044 Avinash R Changrani
#include <unistd.h>
#include <stdio.h>

int main()
{
    int pid = fork();
    if (pid > 0)
    {
        printf("PARENT ProcessID: %d\n", getpid());
        printf("Parent's parent ProcessID: %d\n", getppid());
    }
    if (pid == 0)
    {
        // 1st level
        int pid1 = fork();
        if (pid1 > 0)
        {
            printf("ProcessID of child at 1st level : %d\n", getpid());
            printf("Parent ProcessID: %d\n", getppid());
        }
        if (pid1 == 0)
        {
            // 2nd level
            int pid2 = fork();
            printf("ProcessID of child at 2nd level : %d\n", getpid());
            printf("Parent ProcessID: %d\n", getppid());
            if (pid2 > 0)
            {
                // 3rd level
                printf("ProcessID of child at 3rd level : %d\n", getpid());
                printf("Parent ProcessID: %d\n", getppid());
            }
            if (pid2 == 0)
            {
                // 4th level
                int pid3 = fork();
                printf("ProcessID of child at 4th level : %d\n", getpid());
                printf("Parent ProcessID: %d\n", getppid());
            }
        }
    }
    return 0;
}


