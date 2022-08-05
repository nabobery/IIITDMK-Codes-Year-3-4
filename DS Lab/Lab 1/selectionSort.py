# This program is done by CS20B1044 Avinash R Changrani

def selection_sort(arr):
    n = len(arr)
    for i in range(n-1):
        index = i
        for j in range(i+1, n):
            if(arr[j] < arr[index]):
                index = j
        arr[i], arr[index] = arr[index], arr[i]
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
    print(str(arr[i]), end=" ")

selection_sort(arr)

print("\nThe array Elements after being sorted are: ")

for i in range(n):
    print(str(arr[i]), end=" ")
