// Write two programs (in exec1.c and exec2.c) to demonstrate the usage of exec() system call.

// exec1.c
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    // printing out the exec1 content
    printf("This is Exec1 \n");
    printf("The process id of exec1 is %d \n\n", getpid());
    // executing the object dump file of exec2 using execv
    char *args[]={"./exec2",NULL};
    execvp(args[0],args);
    return 0;
}

// exec2.c
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    // printing out the exec2 content
    printf("This is Exec2 \n");
    printf("The process id of exec2 is %d \n\n", getpid());
    return 0;
}


