// Write a program to create a thread. The thread is created by passing an array which contains more than two integers as input from the main process. The two or more array elements will be added in the thread and will return the result to the main function. Finally, the main function will print the final sum.
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum = 0,n;

// function to calculate sum of array using thread
void* sumOfArray(void* arg){
    int *ptr = arg;
    for(int i = 0; i < n;i++){
        sum += ptr[i];
    }
    return (void*) sum;
}

int main(){
    pthread_t t_id;
    // get number of elements
    printf("Please enter the Number of elements: ");
    scanf("%d", &n);
    int *arr = malloc(n*sizeof (int));
    // get elements from user
    for(int i = 0; i < n;i++){
        printf("Enter the element %d: ", i+1);
        scanf("%d",&arr[i]);
    }
    // create thread and run the function
    pthread_create(&t_id,NULL, sumOfArray, arr);
    int result;
    // wait for the thread to terminate and get the return value
    pthread_join(t_id, (void **)&result);
    // print the sum of elements
    printf("The sum of the array of %d elements is %d\n",n, result);
    return 0;
}
