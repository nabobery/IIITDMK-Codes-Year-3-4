#This program is done by CS20B1044 Avinash R Changrani

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0,n-1):
            if(arr[j+1] < arr[j]): arr[j], arr[j+1] = arr[j+1], arr[j]  
    return

arr = []

print("Please Enter the number of Elements: ")
n = int(input())
for i in range(n):
    print("Enter Element " + str(i+1))
    x = int(input())
    arr.append(x)

print("The array Elements before being sorted are: ")
for i in range(n):
    print(str(arr[i]), end = " ")

bubble_sort(arr)

print("\nThe array Elements after being sorted are: ")

for i in range(n):
    print(str(arr[i]), end = " ")
