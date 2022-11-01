/*
Implement the dining philosopher's problem’s solution using semaphore. Your solution should allow two philosopher's to eat simultaneously if there are five philosophers thread running simultaneously.  
Also, clearly define the eating task and thinking task inside the respective functions. 
*/

// This program is done by CS20B1044 Avinash R Changrani

// including the required libraries
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdbool.h>

// states for Philosopher
#define NUMBER 6
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (pnum + 5) % NUMBER
#define RIGHT (pnum + 1) % NUMBER

int state[NUMBER];
// int counter = 10;

sem_t mutex;
sem_t phil[NUMBER];

bool eat[NUMBER] = {false, false, false, false, false, false};

// checks if every philospher has eaten
bool Eaten()
{
    for (int i = 0; i < NUMBER; i++)
    {
        if (eat[i] == false)
            return false;
    }
    return true;
}

// see if a philospher can eat or not
void test(int pnum)
{
    // if philospher is hungry and his neighbours aren't eating
    if (state[pnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        // change the state to eating
        state[pnum] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", pnum + 1, LEFT + 1, pnum + 1);
        printf("Philosopher %d is Eating\n", pnum + 1);
        eat[pnum] = true;
        // counter--;
        // used to wake up hungry philosophers during putfork
        sem_post(&phil[pnum]);
    }
}

// take up forks
void take_fork(int pnum)
{
    sem_wait(&mutex);
    // change state to hungry
    state[pnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", pnum + 1);
    // eat if neighbours are not eating
    test(pnum);
    sem_post(&mutex);
    // if unable to eat wait to be signalled
    sem_wait(&phil[pnum]);
    sleep(1);
}

// put down the forks after eating
void put_fork(int pnum)
{
    sem_wait(&mutex);
    // change state to thinking
    state[pnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", pnum + 1, LEFT + 1, pnum + 1);
    printf("Philosopher %d is thinking\n", pnum + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

// philosopher function
void *philosopher(void *pnum)
{
    // exits if all philosophers got a chance to eat
    while (Eaten() == false)
    {
        int* i = (int)pnum;
        sleep(1);
        take_fork(i);
        sleep(0);
        put_fork(i);
    }
}

int main()
{
    pthread_t tid[NUMBER];
    // initialize the semaphores
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NUMBER; i++)
        sem_init(&phil[i], 0, 0);
    // create philosopher threads
    for (int i = 0; i < NUMBER; i++)
    {
        pthread_create(&tid[i], NULL, philosopher, (void *)(i));
        printf("Philosopher %d is thinking\n", i + 1);
    }
    // join the threads and wait for completion
    for (int i = 0; i < NUMBER; i++)
        pthread_join(tid[i], NULL);
    // destroying the semaphores and mutex
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUMBER; i++)
        sem_destroy(&phil[i]);
    return 0;
}