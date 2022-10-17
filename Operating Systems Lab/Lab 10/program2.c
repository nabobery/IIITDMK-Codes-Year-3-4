/*
Implement the producer – consumer problem’s solution using semaphore. Use one producer thread and one consumer thread. Also, clearly define the produce_item() function and consume_item() function.
*/

// This program is done by CS20B1044 Avinash R Changrani
// include the required libraries
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// maximum buffer size defined as 5
#define BUFFER_SIZE 5

int returnstatus, item, counter1 = 0, counter2 = 0, rear = -1, front = -1, queue[BUFFER_SIZE], count = 0;

// Semaphore declaration
sem_t empty, full, mutex;

// Producer function which produces item
void *produce_item(void *arg)
{
    while (counter1 < 2 * BUFFER_SIZE)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        item = rand() % 100;
        if (rear == -1)
        {
            front += 1;
            rear += 1;
            queue[front] = item;
        }
        else
        {
            rear += 1;
            queue[rear] = item;
        }
        printf("Producer produces item %d in buffer at position: %d\n", item, count);
        count++;
        sem_post(&full);
        sem_post(&mutex);
        counter1++;
    }
}

// Consumer function which produces item
void *consume_item(void *arg)
{
    while (counter2 < 2 * BUFFER_SIZE)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        count--;
        printf("Consumer consumes item %d  in buffer at position : %d\n", queue[count], count);
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front += 1;
        }
        sem_post(&empty);
        sem_post(&mutex);
        counter2++;
    }
}

int main(int argv, char *argc[])
{
    srand(time(NULL));
    // thread declaration
    pthread_t producer, consumer;
    // Declaration of attribute......
    pthread_attr_t attr;
    // semaphore initialization
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&mutex, 0, 1);
    // pthread_attr_t initialization
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    // Creating thread and running the produce_item fucntion
    returnstatus = pthread_create(&producer, &attr, produce_item, NULL);
    if (returnstatus)
    {
        printf("Error in creating thread\n");
        exit(-1);
    }
    returnstatus = pthread_create(&consumer, &attr, consume_item, NULL);
    if (returnstatus)
    {
        printf("Error in creating thread\n");
        exit(-1);
    }
    // destroying the pthread_attr
    pthread_attr_destroy(&attr);
    // Joining the thread and waiting for it to complete
    returnstatus = pthread_join(producer, NULL);
    if (returnstatus)
    {
        printf("Error in joining thread\n");
        exit(-1);
    }
    returnstatus = pthread_join(consumer, NULL);
    if (returnstatus)
    {
        printf("Error in joining thread\n");
        exit(-1);
    }
    // Exiting thread
    pthread_exit(NULL);
    return 0;
}