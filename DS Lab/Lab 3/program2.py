# This code is done by CS20B1044 Avinash R Changrani
'''
Write a python program using classes to implement a queue with the following menu options,
(a) Enqueue
(b) dequeue
(c) Peek (Note: Displays the front value but does not remove it)
(d) Print (Note: Displays all the elements of a queue but does not remove the elements)
(e) Exit
'''


class Node(object):
    def __init__(self, val):
        self.val = val
        self.next = None


class Queue(object):
    def __init__(self):
        self.head = None

    def enqueue(self, x):
        node = Node(x)
        if self.is_empty():
            self.head = node
        else:
            curr = self.head
            while curr.next:
                curr = curr.next
            curr.next = node

    def dequeue(self):
        if self.is_empty():
            print("The given queue is Empty!")
        else:
            temp = self.head
            self.head = self.head.next
            print("The element which is removed from queue is " + str(temp.val))
            del temp

    def peek(self):
        if self.is_empty():
            print("The given queue is Empty!")
        else:
            print("The element at the front of the queue is " + str(self.head.val))

    def is_empty(self):
        return self.head == None

    def print(self):
        if self.is_empty():
            print("The given queue is Empty!")
        else:
            curr = self.head
            result = ""
            while curr:
                result += (str(curr.val) + " ")
                curr = curr.next
            print("The elements in the queue are " + result)


print("This is a python program using classes to implement a queue ")
flag = True
q = Queue()
while flag:
    print("Menu\n(a)Enqueue\n(b)dequeue\n(c)Peek\n(d)Print\n(e)Exit")
    print("Enter your choice: ")
    choice = input()
    if choice == 'a':
        print("Enter the element you want to enqueue ")
        element = int(input())
        q.enqueue(element)
    elif choice == 'b':
        q.dequeue()
    elif choice == 'c':
        q.peek()
    elif choice == 'd':
        q.print()
    elif choice == 'e':
        flag = False
        print("Exiting the Program......")
    else:
        print("Please enter the correct menu choice and try again.")
