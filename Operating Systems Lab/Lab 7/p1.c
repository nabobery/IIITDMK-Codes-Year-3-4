/*
Write a program using pipe() and fork() in which parent process takes one string as input. The same is sent to the child using pipe1 and child will reverse it. After the reversing is complete, the child process will send it (reversed string) to parent process using pipe2. Subsequently, parent process will read the string and displays it.
*/
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipefds1[2], pipefds2[2];
    int returnstatus1, returnstatus2;
    int pid;
    char messageInput[100];
    char readmessage[100];
    char writemessage[100];
    // create pipe1
    returnstatus1 = pipe(pipefds1);
    if (returnstatus1 == -1)
    {
        printf("Unable to create pipe 1 \n");
        return 1;
    }
    // create pipe2
    returnstatus2 = pipe(pipefds2);
    if (returnstatus2 == -1)
    {
        printf("Unable to create pipe 2 \n");
        return 1;
    }
    pid = fork();
    // Parent Process
    if (pid != 0)
    {
        // closing read in pipe 1 and write in pipe 2
        close(pipefds1[0]);
        close(pipefds2[1]);
        printf("Please enter a input string: \n");
        fgets(messageInput, 100, stdin);
        printf("Parent Process\nWriting to pipe1 - Message sent is %s\n", messageInput);
        // write message to pipe 1 using fd 1
        write(pipefds1[1], messageInput, sizeof(messageInput));
        // read message from pipe 2 using fd 0
        read(pipefds2[0], readmessage, sizeof(readmessage));
        printf("\nParent Process\nMessage received from Child is %s\n", readmessage);
    }
    // Child Process
    else
    {
        // closing write in pipe 1 and read in pipe 2
        close(pipefds1[1]);
        close(pipefds2[0]);
        // read message from pipe 1 using fd 0
        read(pipefds1[0], readmessage, sizeof(readmessage));
        printf("Child Process\nMessage received after reading from pipe 1 is %s\n", readmessage);
        int size = strlen(readmessage) - 1, j = size - 1;
        // reversing the string
        for (int i = 0; i < size; i++)
        {
            writemessage[i] = readmessage[j];
            j--;
        }
        printf("Child Process\nMessage sent by writing through pipe 2 is %s\n", writemessage);
        // write message to pipe 2 using fd 1
        write(pipefds2[1], writemessage, sizeof(writemessage));
    }
    return 0;
}