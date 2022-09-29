// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int A[5], B[5], C[5], readmessage[5], writemessage[5];

int main()
{
    // file descriptors for reading and writing in pipe1, pipe2 and pipe3
    int pipefds1[2], pipefds2[2], pipefds3[2];
    // return status after creation of pipe1, pipe2 and pipe3
    int returnstatus1, returnstatus2, returnstatus3;
    int pid, pid1;
    // create pipe1
    returnstatus1 = pipe(pipefds1);
    // Abbormal Termination
    if (returnstatus1 == -1)
    {
        printf("Unable to create pipe 1 \n");
        return 1;
    }
    // create pipe2
    returnstatus2 = pipe(pipefds2);
    // Abbormal Termination
    if (returnstatus2 == -1)
    {
        printf("Unable to create pipe 2 \n");
        return 1;
    }
    // create pipe3
    returnstatus3 = pipe(pipefds3);
    // Abbormal Termination
    if (returnstatus3 == -1)
    {
        printf("Unable to create pipe 3 \n");
        return 1;
    }
    printf("In Parent Process: %d\n", getpid());
    printf("Please enter the elements of A: \n");
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &A[i]);
        writemessage[i] = A[i];
    }
    pid = fork();
    // Parent Process
    if (pid != 0)
    {
        // close pipe1 read and pipe2 write
        close(pipefds1[0]);
        close(pipefds2[1]);
        // write to pipe1 to  GrandChild
        write(pipefds1[1], writemessage, sizeof(writemessage));
        // Wait for child process to terminate
        wait(NULL);
        // read from pipe2 from grandchild
        read(pipefds2[0], readmessage, sizeof(readmessage));
        printf("In Parent Process: %d\n", getpid());
        printf("Message received from GrandChild is: ");
        for (int i = 0; i < 5; i++)
        {
            C[i] = readmessage[i];
            printf("%d ", C[i]);
        }
        printf("\n");
    }
    // Child Process
    else
    {
        printf("In Child Process: %d\n", getpid());
        printf("Please enter the elements of B: \n");
        for (int i = 0; i < 5; i++)
        {
            scanf("%d", &B[i]);
            writemessage[i] = B[i];
        }
        pid1 = fork();
        if (pid1 != 0)
        {
            // close pipe3 read
            close(pipefds3[0]);
            // write to pipe3 to  GrandChild
            write(pipefds3[1], writemessage, sizeof(writemessage));
            // wait for grandchild to terminate
            wait(NULL);
        }
        // GrandChild Process
        else
        {
            // close pipe1 write, pipe2 read and pipe3 write
            close(pipefds1[1]);
            close(pipefds2[0]);
            close(pipefds3[1]);
            printf("In GrandChild Process: %d\n", getpid());
            int a[5], b[5];
            // read from pipe1 from Parent
            read(pipefds1[0], readmessage, sizeof(readmessage));
            printf("Message received from Parent is: ");
            for (int i = 0; i < 5; i++)
            {
                a[i] = readmessage[i];
                printf("%d ", readmessage[i]);
            }
            printf("\n");
            // read from pipe3 from Child
            read(pipefds3[0], readmessage, sizeof(readmessage));
            printf("Message received from Child is: ");
            for (int i = 0; i < 5; i++)
            {
                b[i] = readmessage[i];
                printf("%d ", readmessage[i]);
            }
            printf("\n");
            for (int i = 0; i < 5; i++)
            {
                writemessage[i] = a[i] + b[i];
            }
            // write to pipe2 to Parent
            write(pipefds2[1], writemessage, sizeof(writemessage));
            exit(0);
        }
    }
    return 0;
}