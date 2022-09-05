// This program is done by CS20B1044 Avinash R Changrani
/*
Write two different programs (Sender and Receiver) in C to demonstrate IPC using shared memory. Process "Sender.c" will write atleast 100 bytes of data to the shared memory and process "Receiver.c" will read from the shared memory and displays it. Then, "Receiver.c" will write atleast 100 bytes of
data to the same shared memory and  "Sender.c" will read and displays it.
*/
// Sender.c
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
    key_t key;
    char *shm, *s;
    // key to uniquely identify shared memory
    key = 4789;
    printf("Sender is sending data\n");
    // Creating Segment
    if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0)
    {
        printf("Error in shmget\n");
        // Abnormal termination
        exit(1);
    }
    // Attaching segment to data space
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        printf("Error in shmat\n");
        // Abnormal termination
        exit(1);
    }
    // putting something into shared memory
    s = shm;
    for (c = 'a'; c <= 'j'; c++)
    {
        *s++ = c;
    }
    for (int i = 36; i < 127; i++)
    {
        c = i;
        *s++ = c;
    }
    *s = 0;
    // wait for the other process to complete
    sleep(5);
    // Creating Segment
    if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0)
    {
        printf("Error in shmget\n");
        // Abnormal termination
        exit(1);
    }
    // Attaching segment to data space
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        printf("Error in shmat\n");
        // Abnormal termination
        exit(1);
    }
    printf("Sender is receiving data\n");
    // getting from shared memory
    for (s = shm; *s != 0; s++)
    {
        putchar(*s);
    }
    putchar('\n');
    *shm = '#';
    exit(0);
}