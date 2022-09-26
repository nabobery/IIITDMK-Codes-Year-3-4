'''
Write the area and perimeter functions of different shape classes, such as Triangle, Rectangle, Circle and
Ellipse. These shapes share common properties, such as color (string) and is_filled (boolean). Use python
inheritance concept to depict the above. Also, write the set and get functions for all class attributes. Note
for set and get functions
'''
# This program is done by CS20B1044 Avinash R Changrani

import math

# Parent Class is Shape


class Shape():
    # Initialize the Shape Object
    def __init__(self):
        self.color = "White"
        self.is_Filled = False
    # methos to set color of Shapes

    def set_color(self, Color):
        self.color = Color
    # method to set Is-Filled attribute of shape object

    def set_is_filled(self, b):
        self.is_Filled = b
    # method to get color of shape object

    def get_color(self):
        print("The color of the given Shape is : " + self.color)
    # method to get is_filled attribute of shape object

    def get_is_filled(self):
        print("The is_filled attribute of the given Shape is : " +
              str(self.is_Filled))

# Child class Triangle inheriting from Shape


class Triangle(Shape):
    # Initialize the Triangle Object
    def __init__(self):
        # 3 sides of the triangle
        Shape.__init__(self)
        self.a = 0
        self.b = 0
        self.c = 0
        self.perimeter = 0
        self.area = 0
    # set attributes of Triangle Object

    def set_sides(self, s1, s2, s3):
        self.a = s1
        self.b = s2
        self.c = s3
    # get attributes of the Triangle Object

    def get_sides(self):
        print("The Sides of the given Triangle are: " +
              str(self.a) + ", " + str(self.b) + " and " + str(self.c))
    # perimeter = side1 + side2 + side3 =  a + b + c

    def calculate_perimeter(self):
        self.perimeter = self.a + self.b + self.c
        print("The perimeter of the Triangle is: " + str(self.perimeter))
    # area = sqrt((s*(s-a)*(s-b)*(s-c))

    def calculate_area(self):
        s = (self.a + self.b + self.c)/2
        self.area = math.sqrt(s*(s-self.a)*(s-self.b)*(s-self.c))
        print("The area of the Triangle is: " + str(self.area))

# Child class Rectangle inheriting from Shape


class Rectangle(Shape):
    # Initialize the Rectangle Object
    def __init__(self):
        Shape.__init__(self)
        # length of rectangle
        self.l = 0
        # breadth of rectangle
        self.b = 0
    # method to get sides of the Rectangle

    def set_sides(self, length, breadth):
        self.l = length
        self.b = breadth
    # Method to get attributes of the Rectangle

    def get_sides(self):
        print("The length and breadth of the given Rectangle are: " +
              str(self.l) + " and " + str(self.b))
    # perimeter = 2*(l + b)

    def calculate_perimeter(self):
        self.perimeter = 2*(self.l + self.b)
        print("The perimeter of the Rectangle is: " + str(self.perimeter))
    # area = l*b

    def calculate_area(self):
        self.area = self.l*self.b
        print("The area of the Rectangle is: " + str(self.area))

# Child class Circle inheriting from Shape


class Circle(Shape):
    # Initialize the Circle Object
    def __init__(self):
        Shape.__init__(self)
        # radius of circle
        self.radius = 0
    # method to Set the radius of the Circle

    def set_radius(self, r):
        self.radius = r
    # methid to get attributes of circle

    def get_radius(self):
        print("The radius of the given Circle is: " + str(self.radius))
    # perimeter = 2*pi*r

    def calculate_perimeter(self):
        self.perimeter = 2*math.pi*self.radius
        print("The perimeter of the Circle is: " + str(self.perimeter))
    # area = pi*r^2

    def calculate_area(self):
        self.area = math.pi*self.radius*self.radius
        print("The area of the Circle is: " + str(self.area))

# Child class Ellipse inheriting from Shape


class Ellipse(Shape):
    # Initialize the Ellipse Object
    def __init__(self):
        Shape.__init__(self)
        # major axis
        self.a = 0
        # minor axis
        self.b = 0
    # set attributes of Ellipse

    def set_attributes(self, major_axis, minor_axis):
        self.a = major_axis
        self.b = minor_axis
    # get atrributes of Ellipse

    def get_attributes(self):
        print("The major and minor axis of the given Ellipse is: " +
              str(self.a) + " and " + str(self.b))
    # perimeter = 2*pi*sqrt(a^2 + b^2 / 2)

    def calculate_perimeter(self):
        self.perimeter = 2*math.pi*math.sqrt(((self.a)**2 + (self.b)**2)/2)
        print("The perimeter of the Ellipse is: " + str(self.perimeter))
    # area = pi*a*b

    def calculate_area(self):
        self.area = math.pi*self.a*self.b
        print("The area of the Ellipse is: " + str(self.area))


# Tests
T1 = Triangle()
T1.set_sides(2, 2, 2)
T1.calculate_area()
T1.calculate_perimeter()
T1.get_sides()
T1.get_color()
T1.get_is_filled()

print("")

R1 = Rectangle()
R1.set_sides(3, 4)
R1.calculate_perimeter()
R1.calculate_area()
R1.get_sides()
R1.set_color("Blue")
R1.set_is_filled(True)
R1.get_color()
R1.get_is_filled()

print("")

C1 = Circle()
C1.set_radius(3)
C1.calculate_perimeter()
C1.calculate_area()
C1.get_radius()
C1.set_color("Red")
C1.set_is_filled(False)
C1.get_color()
C1.get_is_filled()

print("")

E1 = Ellipse()
E1.set_attributes(6, 8)
E1.calculate_perimeter()
E1.calculate_area()
E1.set_color("Cyan")
E1.set_is_filled(True)
E1.get_color()
E1.get_is_filled()
