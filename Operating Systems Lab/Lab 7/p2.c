/*
A parent process creates a child process and the child process creates a grandchild process. The parent creates a pipe that is shared between the parent and the child. The parent writes a message to the pipe and the child reads it from the pipe. The child creates another pipe which is shared between the child and the grandchild.
Note that this pipe is not available to the parent and is not the same as the one shared by the parent and the child. The grandchild writes another message to the pipe and the child reads it from the pipe. After obtaining the two messages from the pipes, the child prints the difference in lengths of the two messages. Moreover,
each of the three processes prints the PID of its respective parent process. The contents of the two messages must be taken as user inputs.
*/
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int pipefds1[2], pipefds2[2];
    int returnstatus1, returnstatus2;
    int pid, pid1;
    char message1[100], message2[100];
    char readmessage[100];
    char writemessage[100];
    // create pipe1
    returnstatus1 = pipe(pipefds1);
    if (returnstatus1 == -1)
    {
        printf("Unable to create pipe 1 \n");
        return 1;
    }
    pid = fork();
    // Parent Process
    if (pid != 0)
    {
        // closing read in pipe 1
        close(pipefds1[0]);
        printf("Parent Process of pid = %d whose parent process id = %d\nPlease enter a input string: \n", getpid(), getppid());
        fgets(message1, 100, stdin);
        printf("Parent Process of pid = %d whose parent process id = %d\nWriting to pipe1 - Message sent is %s\n", getpid(), getppid(), message1);
        // write message to pipe 1 using fd 1
        write(pipefds1[1], message1, sizeof(message1));
        wait(NULL);
    }
    // Child Process
    else
    {
        // create pipe2
        returnstatus2 = pipe(pipefds2);
        if (returnstatus2 == -1)
        {
            printf("Unable to create pipe 2 \n");
            return 1;
        }
        pid1 = fork();
        if (pid1 != 0)
        {
            sleep(2);
            // closing write in pipe 1
            close(pipefds1[1]);
            // read message from pipe 1 using fd 0
            read(pipefds1[0], readmessage, sizeof(readmessage));
            printf("Child Process  of pid = %d whose parent process id = %d\nMessage received after reading from pipe 1 is %s\n", getpid(), getppid(), readmessage);
            // length of message from parent
            int len1 = strlen(readmessage);
            sleep(5);
            // closing write in pipe 2
            close(pipefds2[1]);
            // read message from pipe 2 using fd 0
            read(pipefds2[0], readmessage, sizeof(readmessage));
            printf("Child Process  of pid = %d whose parent process id = %d\nMessage received after reading from pipe 2 is %s\n", getpid(), getppid(), readmessage);
            // length of message from grandchild
            int len2 = strlen(readmessage);
            printf("Child Process  of pid = %d whose parent process id = %d\nDifference between length of two messages is %d\n", getpid(), getppid(), len1 - len2);
        }
        // GrandChild Process
        else
        {
            // closing read in pipe 2
            sleep(6);
            close(pipefds2[0]);
            printf("Grandchild Process of pid = %d whose parent process id = %d\nPlease enter a input string: \n", getpid(), getppid());
            fgets(message2, 100, stdin);
            printf("GrandChild Process of pid = %d whose parent process id = %d\nWriting to pipe2 - Message sent is %s\n", getpid(), getppid(), message2);
            // write message to pipe 2 using fd 1
            write(pipefds2[1], message2, sizeof(message2));
        }
    }
    return 0;
}