"""
Write a python script to implement student details using a dictionary. The roll number of the student 
will be the key, the value will be a list containing the name, CGPA, and mobile number of the respective student. 
The program should be implemented as a menu-driven program with the following menus,
(a) Insert
(b) Delete
(c) Search
(d) Exit
"""
# This program is done by CS20B1044 Avinash R Changrani

print("This is a python program to implement student details using a dictionary: ")
student_details = {}
flag = True
while flag:
    print("Menu\n(a)Insert\n(b)Delete\n(c)Search\n(d)Exit")
    print("Enter your choice: ")
    choice = input()
    if choice == 'a':
        print("Please enter the Roll Number of the Student: ")
        roll_number = input()
        values = []
        print("Please enter the Name of the given Student: ")
        x = input()
        values.append(x)
        print("Please enter the CGPA of the Student: ")
        x = input()
        values.append(x)
        print("Please enter the mobile number of the Student: ")
        x = input()
        values.append(x)
        student_details[roll_number] = values
    elif choice == 'b':
        print(
            "Please enter the Roll Number of the Student whose record you want to delete: ")
        roll_number = input()
        if roll_number in student_details:
            del student_details[roll_number]
            print("The Student Details with the Roll Number " +
                  roll_number + " has been deleted.")
        else:
            print(
                "The Roll Number does not exist in the Student Details dictionary. Please try again.")
    elif choice == 'c':
        print(
            "Please enter the Roll Number of the Student whose record you want to search: ")
        roll_number = input()
        if roll_number in student_details:
            print("The student details of the student with the Roll Number " +
                  roll_number + " is: ")
            print(student_details[roll_number])
        else:
            print(
                "The Roll Number does not exist in the Student Details dictionary. Please try again.")
    elif choice == 'd':
        flag = False
        print("Exiting the Program......")
    else:
        print("Please enter the correct menu choice and try again.")
