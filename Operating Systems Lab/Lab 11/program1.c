/*
Implement the reader - writer problem’s solution using semaphore. Use atleast three reader threads and two writer threads.  Also, clearly define the reading task and reading task inside the respective functions.
*/

// This program is done by CS20B1044 Avinash R Changrani
// including the required libraries
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t write;
pthread_mutex_t mutex;
int value, reader_count = 0;

// Function for Writer Thread
void *Writer(void *wid)
{
    // decrement the number of writers and lock the semaphore
    sem_wait(&write);
    // do some modification on value
    value += 1;
    int temp = (int)wid;
    printf("Writer %d modified value to %d\n", temp, value);
    // incrment the number of writers and unlock the semaphore
    sem_post(&write);
}

// Function for Reader Thread
void *Reader(void *rid)
{
    // Reader acquires the lock and increases the reader count
    pthread_mutex_lock(&mutex);
    reader_count++;
    // if there is a reader available, make the writer sleep
    if (reader_count == 1)
    {
        sem_wait(&write);
    }
    pthread_mutex_unlock(&mutex);
    // Reading Section
    int temp = (int)rid;
    printf("Reader %d: reads value as %d\n", temp, value);
    // Reader acquires the lock before reading
    pthread_mutex_lock(&mutex);
    // decrement as reader has done the reading
    reader_count--;
    // if no readers available, wake up the writer
    if (reader_count == 0)
    {
        sem_post(&write);
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    int n, m;
    printf("Enter the number of Readers(>=3) you want : ");
    scanf("%d", &n);
    printf("Enter the number of Writers(>=2) you want : ");
    scanf("%d", &m);
    printf("Enter the value you want to initialise with: ");
    scanf("%d", &value);
    // initialising the threads and semaphores
    pthread_t reader[n], writer[m];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&write, 0, 1);
    // creating the thread and assigning them a function
    for (int i = 0; i < n; i++)
    {
        pthread_create(&reader[i], NULL, (void *)Reader, (void *)(i + 1));
    }
    for (int i = 0; i < m; i++)
    {
        pthread_create(&writer[i], NULL, (void *)Writer, (void *)(i + 1));
    }
    // joining threads and waiting for them to complete
    for (int i = 0; i < n; i++)
    {
        pthread_join(reader[i], NULL);
    }
    for (int i = 0; i < m; i++)
    {
        pthread_join(writer[i], NULL);
    }
    // destroying mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&write);
    return 0;
}
