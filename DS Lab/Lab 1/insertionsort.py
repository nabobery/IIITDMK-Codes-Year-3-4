#This program is done by CS20B1044 Avinash R Changrani

def insertion_sort(arr):
    for i in range(1,len(arr)):
        for j in range(i-1,-1,-1):
            if(arr[j] > arr[j+1]): arr[j],arr[j+1] = arr[j+1],arr[j]
            else: break
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

insertion_sort(arr)

print("\nThe array Elements after being sorted are: ")

for i in range(n):
    print(str(arr[i]), end = " ")
