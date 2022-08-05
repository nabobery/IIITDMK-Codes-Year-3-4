#This program is done by CS20B1044 Avinash R Changrani

def binary_search(arr,x):
    low = 0 
    high = len(arr)-1
    flag = True
    while low <= high:
        mid = (low + high)//2
        if arr[mid] ==  x:
            print("Element found!\n")
            flag = False
            break;
        if arr[mid] > x: high = mid-1
        if arr[mid] < x: low = mid+1
    if flag: 
        print("Element not Found!\n")
    return;

arr = []

print("Please Enter the number of Elements: ")
n = int(input())
for i in range(n):
    print("Enter Element " + str(i+1))
    x = int(input())
    arr.append(x)

arr.sort()

print("Please Enter the element you want to find using Binary Search: ")
x = int(input())

binary_search(arr,x)