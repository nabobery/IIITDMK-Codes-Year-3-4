// Write a program to create five threads using pthread library. Find the sum of first 1000 numbers using five threads, where each thread can calculate sum of 200 numbers in each (parallel counting using threads).
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREAD 5
#define N 1000

int curr_thread = 0;
int sum[MAX_THREAD] = {0};

// function to find sum of numbers in thread
void* sumOfNumbers(void* arg){
    int curr = curr_thread++;
    // storing the sum in sum[thread_no]
    for(int i = curr*(N/MAX_THREAD) + 1; i <= (curr+1)*(N/MAX_THREAD);i++){
        sum[curr] += i;
    }
    return NULL;
}

int main(){
    pthread_t threads[MAX_THREAD];
    // creating threads
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_create(&threads[i],NULL, sumOfNumbers, (void*)NULL);
    // joinging threads and calculating the result
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL);
    int result = 0;
    // adding the sum of all threads
    for (int i = 0; i < MAX_THREAD; i++)
        result += sum[i];
    // printing out the result
    printf("Sum of %d Numbers using %d threads(parallel counting using threads) is %d\n", N, MAX_THREAD, result);
    return 0;
}