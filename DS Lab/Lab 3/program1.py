# This code is done by CS20B1044 Avinash R Changrani
'''
Write a python program using classes to implement a stack with the following menu options,
(a) Push
(b) Pop
(c) Peek (Note: Displays the top value but does not remove it)
(d) Print (Note: Displays all the elements of a stack but does not remove the elements)
(e) Exit
'''


class Node(object):
    def __init__(self, val):
        self.val = val
        self.next = None


class Stack(object):
    def __init__(self):
        self.top = Node("Top")
        self.size = 0

    def push(self, x):
        node = Node(x)
        node.next = self.top.next
        self.top.next = node
        self.size += 1

    def pop(self):
        if self.is_empty():
            print("Can't pop from the Stack as the stack is Empty. Please try again")
        else:
            temp = self.top.next
            self.top.next = self.top.next.next
            self.size -= 1
            print("The element popped from stack is " + str(temp.val))
            del temp

    def peek(self):
        if self.is_empty():
            print("Can't peek as the Stack is Empty. Please try again")
        else:
            print("The element at the top of the stack is " +
                  str(self.top.next.val))

    def print(self):
        if self.is_empty():
            print("The given stack is empty")
        else:
            curr = self.top.next
            result = ""
            while curr:
                result += (str(curr.val) + " ")
                curr = curr.next
            print("The elements in the stack are " + result)

    def is_empty(self):
        return self.size == 0


print("This is a python program using classes to implement a stack ")
flag = True
stk = Stack()
while flag:
    print("Menu\n(a)Push\n(b)Pop\n(c)Peek\n(d)Print\n(e)Exit")
    print("Enter your choice: ")
    choice = input()
    if choice == 'a':
        print("Enter the element you want to push ")
        element = int(input())
        stk.push(element)
    elif choice == 'b':
        stk.pop()
    elif choice == 'c':
        stk.peek()
    elif choice == 'd':
        stk.print()
    elif choice == 'e':
        flag = False
        print("Exiting the Program......")
    else:
        print("Please enter the correct menu choice and try again.")
