// This program is done by CS20B1044 Avinash R Changrani

/* Write a program to display address of an integer variable using pointer. In the same program access
the entries of an integer array using another pointer and display the address for each elements of the array.
 */
#include<stdio.h>

int main(){
    int x,n;
    // getting the number from user
    printf("Please give a number : \n");
    scanf("%d", &x);
    // pointer to save the address of the number
    int* ptr;
    ptr = &x;
    // print the number and the address of the number using pointer
    printf("Given number is %d and the address of integer using pointer is %p \n", x, ptr);
    // getting the size and elements of array  from user
    printf("Please give the size of the array: \n");
    scanf("%d", &n);
    int arr[n];
    printf("Please give elements of the array: \n");
    for(int i = 0; i < n;i++){
        scanf("%d", &arr[i]);
    }
    // making the pointer point to array's base address (first element of the array)
    int* p = &arr[0];
    // printing the array elements using pointer
    for(int i = 0; i < n;i++){
        printf("array element is %d and address is %p \n", *(p+i), (p+i));
    }
    return 0;
}

