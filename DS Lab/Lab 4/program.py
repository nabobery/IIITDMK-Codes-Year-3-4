# This program is done by CS20B1044 Avinash R Changrani
'''
Write a python program to handle books in a library management system. The information available in a book are book ISSN, 
book title, price, edition, year, and author name. The library management system should support the following menus,
Write, Read, Search and Exit.
The write option takes ‘n’ book information from the user and writes it into a file. The read option reads all the 
information stored in a file. The search option allows the search of books based on the book title (assume there are 
no duplicates).
'''
file_name = "library.txt"
file_flag = False


class Book(object):
    def __init__(self, ISSN, book_title, price, edition, year, author_name):
        self.ISSN = ISSN
        self.book_title = book_title
        self.price = price
        self.edition = edition
        self.year = year
        self.author_name = author_name

    def write_to_file(self, file_name):
        file = open(file_name, 'a')
        book = "ISSN: " + self.ISSN + " Book Title: " + self.book_title + " Book price: " + self.price + \
            " Book edition: " + self.edition + " Published Year: " + \
            self.year + " Author: " + self.author_name + "\n"
        file.write(book)
        file.close()


flag = True
print("This is a python program to implement library management system!")
while flag:
    print("Menu\n(a)Write\n(b)Read\n(c)Search\n(d)Exit")
    choice = input()
    if choice == 'a':
        if not file_flag:
            file_flag = True
        print("Please enter the book information you want to write into the library")
        ISSN = input("Please enter the ISSN number of the book: ")
        book_title = input("Please enter the book title of the book: ")
        price = input("Please enter the price of the book: ")
        edition = input("Please enter the edition of the book: ")
        year = input("Please enter the publishing year of the book: ")
        author_name = input("Please enter the name of the book's author: ")
        temp = Book(ISSN, book_title, price, edition, year, author_name)
        temp.write_to_file(file_name)
    elif choice == 'b':
        if file_flag:
            file = open(file_name, 'r')
            print("The books in the library are: ")
            info = file.read()
            print(info)
            file.close()
        else:
            print("The library is Empty. Please write into the library and try again.")
    elif choice == 'c':
        if file_flag:
            book_title = input(
                "Please enter the book title you want to search: ")
            f = True
            with open(file_name, "r") as file:
                data = file.readlines()
                for line in data:
                    if book_title in line:
                        print("Book found in Library\nThe details are: ")
                        print(line)
                        f = False
                        break
            if f:
                print("Book with the given title: " +
                      book_title + " not found in library")
        else:
            print("The library is Empty. Please write into the library and try again.")
    elif choice == 'd':
        print("Exiting the program.....")
        flag = False
    else:
        print("Wrong Choice. Please try again!")
