// This program is done by CS20B1044 Avinash R Changrani
/*
Write two different programs (SenderNew and ReceiverNew) in C to demonstrate IPC using shared memory.
Process "SenderNew.c" will sets-up a string (take input from user) and writes it on to the shared memory.
"ReceiverNew.c" will read the string from the shared memory, checks whether the string is palindrome or not (in the same process itself) and writes either 0 (not palindrome) or 1 (palindrome) to the same shared memory.
Then, "SenderNew.c" will read the number (0/1) and displays whether the input string given by the user is palindrome or not.
*/

// ReceiverNew.c
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
    char c;
    // value returned by shmget
    int shmid;
    // key for uniquely identifying the shared memory
    key_t key;
    char *shm, *s;
    key = 4989;
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
    printf("Receiver is receiving data\nThe Received string is ");
    char output[100];
    int k = 0;
    for (s = shm; *s != 0; s++)
    {
        output[k] = *s;
        putchar(*s);
        k++;
    }
    k--;
    putchar('\n');
    char flag = '1';
    // checking if the given string is a palindrome
    for (int i = 0; i < k / 2; i++)
    {
        if (output[i] != output[k - i - 1])
        {
            flag = '0';
            break;
        }
    }
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
    printf("Receiver is sending data\n");
    // sending flag to receiver
    s = shm;
    *s++ = flag;
    printf("Data sent is %c", flag);
    sleep(2);
    return 0;
}