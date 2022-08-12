"""
Write a python program to implement set operations using menu-driven programming. The menus to be implemented are as follows,
(a) Create Empty Set
(b) Insert
(c) Delete
(d) Search
(e) Print
(f) Union
(g) Intersection
(h) Set Difference
(i) Symmetric Difference
"""
# This program is done by CS20B1044 Avinash R Changrani

print("This is a python program to implement set operations using menu-driven programming: ")
flag = True
flag1 = False
flag2 = False
set1 = set()
set2 = set()
while flag:
    print("Menu\n(a)Create Empty Set\n(b)Insert\n(c)Delete\n(d)Search\n(e)Print\n(f)Union\n(g)Intersection\n(h)Set Difference\n(i)Symmetric Difference\n(j)Exit")
    print("Enter your choice: ")
    choice = input()
    if choice == 'a':
        if not flag1:
            print("Set1 is created!")
            flag1 = True
        elif not flag2:
            print("Set2 is created!")
            flag2 = True
        else:
            print("Both Sets are already created!")
    elif choice == 'b':
        if not flag1 and not flag2:
            print("Please Create a Set and Try Again")
        else:
            print("Enter the set you want to insert into: ")
            set_number = int(input())
            if set_number == 1:
                if not flag1:
                    print("Please Create Set1 and Try Again")
                else:
                    print("Please Enter the element you want to insert: ")
                    element = input()
                    set1.add(element)
            elif set_number == 2:
                if not flag2:
                    print("Please Create Set2 and Try Again")
                else:
                    print("Please Enter the element you want to insert: ")
                    element = input()
                    set2.add(element)
            else:
                print("Enter a proper set Number and try again")
    elif choice == 'c':
        if not flag1 and not flag2:
            print("Please Create a Set and Try Again")
        else:
            print("Enter the set you want to delete the element from: ")
            set_number = int(input())
            if set_number == 1:
                if not flag1:
                    print("Please Create Set1 and Try Again")
                else:
                    print("Please Enter the element you want to delete: ")
                    element = input()
                    if element not in set1:
                        print(
                            "The given element doesn't exist in the set. Enter a element that is present in the set1 and try again")
                    else:
                        set1.remove(element)
                        print("The given element: " +
                              element + " is deleted from set1")
            elif set_number == 2:
                if not flag2:
                    print("Please Create Set2 and Try Again")
                else:
                    print("Please Enter the element you want to delete: ")
                    element = input()
                    if element not in set2:
                        print(
                            "The given element doesn't exist in the set. Enter a element that is present in the set2 and try again")
                    else:
                        set1.remove(element)
                        print("The given element: " +
                              element + " is deleted from set2")
            else:
                print("Enter a proper set Number and try again")
    elif choice == 'd':
        if not flag1 and not flag2:
            print("Please Create a Set and Try Again")
        else:
            print("Enter the set you want to search the element from: ")
            set_number = int(input())
            if set_number == 1:
                if not flag1:
                    print("Please Create Set1 and Try Again")
                else:
                    print("Please Enter the element you want to search: ")
                    element = input()
                    if element not in set1:
                        print("The given element: " + element +
                              " doesn't exist in the set1")
                    else:
                        print("The given element: " +
                              element + " is there in set1")
            elif set_number == 2:
                if not flag2:
                    print("Please Create Set2 and Try Again")
                else:
                    print("Please Enter the element you want to search: ")
                    element = input()
                    if element not in set2:
                        print("The given element: " + element +
                              " doesn't exist in the set2")
                    else:
                        print("The given element: " +
                              element + " is there in set2")
            else:
                print("Enter a proper set Number and try again")
    elif choice == 'e':
        if not flag1 and not flag2:
            print("Please Create a Set and Try Again")
        else:
            print("Enter the set you want to print: ")
            set_number = int(input())
            if set_number == 1:
                if not flag1:
                    print("Please Create Set1 and Try Again")
                else:
                    print(set1)
            elif set_number == 2:
                if not flag2:
                    print("Please Create Set2 and Try Again")
                else:
                    print(set2)
            else:
                print("Enter a proper set Number and try again")
    elif choice == 'f':
        if not flag1 or not flag2:
            print("Please Create enough Sets and Try Again")
        else:
            result = set1.union(set2)
            print("The resultant set after Union is: ")
            print(result)
    elif choice == 'g':
        if not flag1 or not flag2:
            print("Please Create enough Sets and Try Again")
        else:
            result = set1.intersection(set2)
            print("The resultant set after Intersection is: ")
            print(result)
    elif choice == 'h':
        if not flag1 or not flag2:
            print("Please Create enough Sets and Try Again")
        else:
            print("(a) set1 - set2\n(b) set2 - set1")
            ch = input()
            if ch == 'a':
                result = set1.difference(set2)
                print("The resultant set after difference is: ")
                print(result)
            elif ch == 'b':
                result = set2.difference(set1)
                print("The resultant set after difference is: ")
                print(result)
            else:
                print("Enter a correct choice and try again")
    elif choice == 'i':
        if not flag1 or not flag2:
            print("Please Create enough Sets and Try Again")
        else:
            result = set1.symmetric_difference(set2)
            print("The resultant set after symmetric difference is: ")
            print(result)
    elif choice == 'j':
        flag = False
        print("Exiting the Program......")
    else:
        print("Please enter the correct menu choice and try again.")
