'''
Write a python program to perform matrix operations on an M x N matrix and solve a system of linear equations. Use inbuilt functions to implement the operations. Get two matrices from the user. The program should support the following Menus,
    1) Matrix Addition
    2) Matrix Subtraction
    3) Scalar Matrix Multiplication
    4) Elementwise Matrix Multiplication
    5) Matrix Multiplication
    6) Matrix Transpose
    7) Trace of a Matrix
    8) Solve System of Linear Equations
    9) Determinant
    10) Inverse
    11) Singular Value Decomposition
    12) Eigen Value
    13) Search an Element
    14) Difference of Sum of Upper and Lower Triangular Matrix
    15) Exit
'''

# This program is done by CS20B1044 Avinash R Changrani
import numpy as np

print("This is a python program to perform matrix operations on an M x N matrix and solve a system of linear equations")
m = int(input("Please enter M: "))
n = int(input("Please enter N: "))

l1 = []
l2 = []

print("Please enter elements for matrix 1:")
for i in range(m):
    temp = []
    for j in range(n):
        x = int(input("Please enter the column element " +
                str(j+1) + " of row " + str(i+1) + ": "))
        temp.append(x)
    l1.append(temp)


matrix1 = np.array(l1)

print("Please enter elements for matrix 2:")
for i in range(m):
    temp = []
    for j in range(n):
        x = int(input("Please enter the column element " +
                str(j+1) + " of row " + str(i+1) + ": "))
        temp.append(x)
    l2.append(temp)

matrix2 = np.array(l2)

flag = True

while flag:
    print("\nThe given matrices are: ")
    print("Matrix 1 is ")
    print(matrix1)
    print("Matrix 2 is ")
    print(matrix2)
    print("Menu\n1) Matrix Addition\n2) Matrix Subtraction\n3) Scalar Matrix Multiplication\n4) Elementwise Matrix Multiplication\n5) Matrix Multiplication\n6) Matrix Transpose\n7) Trace of a Matrix\n8) Solve System of Linear Equations\n9) Determinant\n10) Inverse\n11) Singular Value Decomposition\n12) Eigen Value\n13) Search an Element\n14) Sum of Difference of Upper and Lower Triangular Matrix\n15) Exit")
    choice = int(input("Please enter your choice: "))
    if choice == 1:
        print("Addition of the 2 matrices gives ")
        print(matrix1 + matrix2)
    elif choice == 2:
        print("Subtraction of the 2 matrices gives (M1 - M2) ")
        print(matrix1 - matrix2)
    elif choice == 3:
        scalar = int(
            input("Enter the scalar you want multiply with the matrix "))
        option = int(
            input("Enter the matrix you want to scalar multiply with: (1 or 2)"))
        if option == 1:
            print("Scalar Matrix Multiplication of " +
                  str(scalar) + " with Matrix 1 gives ")
            print(matrix1*scalar)
        elif option == 2:
            print("Scalar Matrix Multiplication of " +
                  str(scalar) + " with Matrix 2 gives ")
            print(matrix2*scalar)
        else:
            print("Wrong Choice! Please try again")
    elif choice == 4:
        print("Elementwise Matrix Multiplication of the 2 matrices gives ")
        print(np.multiply(matrix1, matrix2))
    elif choice == 5:
        print("Matrix Multiplication of the 2 matrices gives ")
        print(np.dot(matrix1, matrix2))
    elif choice == 6:
        option = int(input("Enter the matrix you want to transpose: (1 or 2)"))
        if option == 1:
            print("Matrix Transpose of the Matrix 1 is ")
            print(np.transpose(matrix1))
        elif option == 2:
            print("Matrix Transpose of the Matrix 2 is ")
            print(np.transpose(matrix2))
        else:
            print("Wrong Choice! Please try again")
    elif choice == 7:
        if n != m:
            print("Can't find trace as it's not a square matrix")
        else:
            option = int(input(
                "Enter the matrix you want to get the trace(sum of diagonal elements) of : (1 or 2)"))
            if option == 1:
                print("Trace of Matrix 1 is ")
                print(np.trace(matrix1))
            elif option == 2:
                print("Trace of Matrix 2 is ")
                print(np.trace(matrix2))
            else:
                print("Wrong Choice! Please try again")
    elif choice == 8:
        q = int(
            input("Please enter the number of variables in system of linear equations: "))
        t1 = []
        t2 = []
        for i in range(q):
            tmp = []
            for j in range(q):
                x = int(input("Please enter the variable " +
                        str(j+1) + " in equation " + str(i+1) + ": "))
                tmp.append(x)
            t1.append(tmp)
        for i in range(q):
            x = int(input("Please enter the RHS of equation: " + str(i+1) + " "))
            t2.append(x)
        A = np.array(t1)
        b = np.array(t2)
        print("Solution of System of Linear Equations is ")
        print(np.linalg.solve(A, b))
    elif choice == 9:
        if n != m:
            print("Can't find determinant as it's not a square matrix")
        else:
            option = int(
                input("Enter the matrix you want to find determinant of : (1 or 2)"))
            if option == 1:
                print("Determinant of Matrix 1 is ")
                print(int(np.linalg.det(matrix1)))
            elif option == 2:
                print("Determinant of Matrix 2 is ")
                print(int(np.linalg.det(matrix2)))
            else:
                print("Wrong Choice! Please try again")
    elif choice == 10:
        if n != m:
            print("Can't find inverse as it's not a square matrix")
        else:
            option = int(
                input("Enter the matrix you want to find inverse of : (1 or 2)"))
            if option == 1:
                print("Inverse of Matrix 1 is ")
                print(np.linalg.inv(matrix1))
            elif option == 2:
                print("Inverse of Matrix 2 is ")
                print(np.linalg.inv(matrix2))
            else:
                print("Wrong Choice! Please try again")
    elif choice == 11:
        option = int(
            input("Enter the matrix you want to find eigen value of : (1 or 2)"))
        if option == 1:
            print("Singular Value Decomposition of Matrix 1 is ")
            print(str(np.linalg.svd(matrix1)))
        elif option == 2:
            print("Singular Value Decomposition of Matrix 2 is ")
            print(str(np.linalg.svd(matrix2)))
        else:
            print("Wrong Choice! Please try again")
    elif choice == 12:
        if n != m:
            print("Can't find eigen Value as it's not a square matrix")
        else:
            option = int(
                input("Enter the matrix you want to find eigen value of : (1 or 2)"))
            if option == 1:
                print("EigenValue of Matrix 1 is ")
                print(np.linalg.eig(matrix1)[0])
            elif option == 2:
                print("EigenValue of Matrix 2 is ")
                print(np.linalg.eig(matrix2)[0])
            else:
                print("Wrong Choice! Please try again")
    elif choice == 13:
        option = int(
            input("Enter the matrix you want to find element in : (1 or 2)"))
        if option == 1:
            element = int(input("Enter the element you want to search for: "))
            temp = np.where(matrix1 == element)
            listOfCoordinates = list(zip(temp[0], temp[1]))
            if len(temp[0]) > 0:
                print("The Element can be found at: ")
                for coordinates in listOfCoordinates:
                    print(coordinates)
            else:
                print("Element " + str(element) +
                      " not found in the Matrix 1")
        elif option == 2:
            element = int(input("Enter the element you want to search for: "))
            temp = np.where(matrix2 == element)
            listOfCoordinates = list(zip(temp[0], temp[1]))
            if len(temp[0]) > 0:
                print("The Element can be found at: ")
                for coordinates in listOfCoordinates:
                    print(coordinates)
            else:
                print("Element " + str(element) +
                      " not found in the Matrix 2")
        else:
            print("Wrong Choice! Please try again")
    elif choice == 14:
        if n != m:
            print("There's no triangular matrix if it's not a square matrix")
        else:
            option = int(
                input("Enter the matrix you want to find difference of sum of Upper and Lower Triangular Matrix elements of : (1 or 2)"))
            if option == 1:
                upper_sum = 0
                lower_sum = 0
                for i in range(n):
                    for j in range(n):
                        if j <= i:
                            lower_sum += matrix1[i][j]
                        if j >= i:
                            upper_sum += matrix1[i][j]
                print("Difference of Sum of Upper and Lower Triangular Matrix 1 is " +
                      str(upper_sum - lower_sum))
            elif option == 2:
                upper_sum = 0
                lower_sum = 0
                for i in range(n):
                    for j in range(n):
                        if j <= i:
                            lower_sum += matrix2[i][j]
                        if j >= i:
                            upper_sum += matrix2[i][j]
                print("Difference of Sum of Upper and Lower Triangular Matrix 2 is " +
                      str(upper_sum - lower_sum))
            else:
                print("Wrong Choice! Please try again")
    elif choice == 15:
        flag = False
        print("Exiting the program....")
    else:
        print("Wrong Choice! Please try again")
