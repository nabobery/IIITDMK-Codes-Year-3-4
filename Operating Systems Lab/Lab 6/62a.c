// This program is done by CS20B1044 Avinash R Changrani
/*
Write two different programs (SenderNew and ReceiverNew) in C to demonstrate IPC using shared memory.
Process "SenderNew.c" will sets-up a string (take input from user) and writes it on to the shared memory.
"ReceiverNew.c" will read the string from the shared memory, checks whether the string is palindrome or not (in the same process itself) and writes either 0 (not palindrome) or 1 (palindrome) to the same shared memory.
Then, "SenderNew.c" will read the number (0/1) and displays whether the input string given by the user is palindrome or not.
*/

// SenderNew.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>

// size of shared memory
#define SHMSIZE 101

int main()
{
    char input[100];
    printf("Please enter a string to check if it's a palindrome\n");
    fgets(input, 100, stdin);
    char c;
    // value returned by shmget
    int shmid;
    // key for uniquely identifying the shared memory
    key_t key;
    char *shm, *s;
    key = 4989;
    printf("Sender is sending data\n");
    // Creating Segment
    if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0)
    {
        printf("Error in shmget\n");
        exit(1);
    }
    // segment is attached to shared memory space
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        printf("Error in shmat\n");
        exit(1);
    }
    s = shm;
    // putting string into shared memory
    for (int i = 0; input[i] != '\0'; i++)
    {
        *s++ = input[i];
    }
    *s = 0;
    // wait for the other process to complete
    sleep(5);
    // Creating Segment
    if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0)
    {
        printf("Error in shmget\n");
        exit(1);
    }
    // segment is attached to shared memory space
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        printf("Error in shmat\n");
        exit(1);
    }
    printf("Sender is receiving data\n");
    // getting result from shared memory
    char result;
    result = *shm;
    if (result == '0')
        printf("Given string is not a palindrome \n");
    else
        printf("Given string is a palindrome \n");
    exit(0);
}