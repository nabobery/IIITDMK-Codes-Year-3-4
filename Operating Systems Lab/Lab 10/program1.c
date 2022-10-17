/*
Given 2 threads, schedule the order of execution in such a way that Thread A has to wait for Thread B and vice versa. In other words, given the code below you must guarantee that Statement A1 happens before Statement B2 and Statement B1 happens before Statement A2.

Thread A
//Statement A1
//Statement A2

Thread B
//Statement B1
//Statement B2

Note: Your solution should not enforce too many constraints. For ex: there is no mention about the order of execution of A1 and B1. Therefore, either order should be possible.

*/
// This program is done by CS20B1044 Avinash Changrani
// including the required libarraries
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

// creating 2 thread ids and 2 locks
pthread_t tid[2];
pthread_mutex_t lock[2];

// thread function for the 2 threads
void *thread_function(void *arg)
{
    // finding which thread it is, if it is t1 it prints A and if it's thread1 it prints B
    int temp = (int)arg;
    char ch = 'A' + temp;
    // if thread 1 it locks lock1, if thread2 it locks lock2
    pthread_mutex_lock(&lock[temp]);
    printf("Statement %c 1 is executed\n", ch);
    // if thread 1 it unlocks lock2, if thread2 it unlocks lock1
    pthread_mutex_unlock(&lock[1 - temp]);
    // if thread 1 it locks lock1, if thread2 it locks lock2
    pthread_mutex_lock(&lock[temp]);
    printf("Statement %c 2 is executed\n", ch);
    // if thread 1 it unlocks lock2, if thread2 it unlocks lock1
    pthread_mutex_unlock(&lock[1 - temp]);
    return NULL;
}

int main()
{
    // initialising the 2 locks
    for (int i = 0; i < 2; i++)
    {
        if (pthread_mutex_init(&lock[i], NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return 1;
        }
    }
    // creating the 2 threads and running the functions
    for (int i = 0; i < 2; i++)
    {
        int error = pthread_create(&(tid[i]), NULL, &thread_function, (void *)i);
        if (error != 0)
            printf("\nThread can't be created :[%s]", strerror(error));
    }
    // waiting for both threads to complete
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    // destroying the locks
    for (int i = 0; i < 2; i++)
        pthread_mutex_destroy(&lock[i]);
    return 0;
}