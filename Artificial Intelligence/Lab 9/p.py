# 8 Puzzle Problem
# Find the most cost-effective path to reach the final state from initial state using A* Algorithm.
# Consider g( n ) = Depth of node n in the state space

# Check your solution for both the following admissible heuristics

# h1( n ) = Number of misplaced tiles
# h2( n ) = Sum of the tile distances from goal

# This program is done by CS20B1044 Avinash R Changrani

# importing the required libraries
from queue import PriorityQueue
from itertools import count
import copy

# class node to store the state of the puzzle
class Node:
    # constructor
    def __init__(self, data, level, f):
        self.parent = None
        self.data = data
        self.level = level
        self.f = f

    # function to find the position of the element in the puzzle
    def find(self, x):
        for i in range(len(self.data)):
            for j in range(len(self.data)):
                if self.data[i][j] == x:
                    return [i,j]

    # function to shuffle the puzzle to generate the child nodes
    def shuffle(self,curr,next):
        if next[0] >= 0 and next[0] < len(self.data) and next[1] >= 0 and next[1] < len(self.data):
            nextNode = copy.deepcopy(self.data)
            temp = nextNode[next[0]][next[1]]
            nextNode[next[0]][next[1]] = nextNode[curr[0]][curr[1]]
            nextNode[curr[0]][curr[1]] = temp
            return nextNode
        else:
            return None

    # function to generate the child nodes
    def childGen(self):
        curr = self.find('-')
        neighbors = [[curr[0], curr[1]+1], [curr[0], curr[1]-1], [curr[0]+1, curr[1]], [curr[0]-1, curr[1]]]
        children = []
        for next in neighbors:
            child = self.shuffle(curr,next)
            if child is not None:
                childNode = Node(child, self.level+1, 0)
                childNode.parent = self
                children.append(childNode)
        return children

# class to solve the puzzle
class Solution:
    # constructor
    def __init__(self, size, initial, final):
        self.size = size
        self.initial = initial
        self.final = final
        self.open = PriorityQueue()
        #self.open  = []
        self.closed = []

    # function to find the position of the element in the puzzle's final state
    def find(self, x):
        for i in range(len(self.final)):
            for j in range(len(self.final)):
                if self.final[i][j] == x:
                    return [i,j]

    # heuristic 1 - number of misplaced tiles
    def h(self, curr):
        counter = 0
        for i in range(self.size):
            for j in range(self.size):
                if self.final[i][j] != curr.data[i][j] and curr.data[i][j] != '-':
                    counter += 1
        return counter

    # heuristic 2 - sum of tile distances from goal
    def h_2(self, curr):
        counter = 0
        for i in range(self.size):
            for j in range(self.size):
                if self.final[i][j] != curr.data[i][j] and curr.data[i][j] != '-':
                    temp = self.find(curr.data[i][j])
                    counter += abs(i - temp[0]) + abs(j - temp[1])
        return counter

    # function to calculate the f(n) = g(n) + h(n) using heuristic 1
    def f(self, curr):
        h_curr =  self.h(curr)
        g_curr = curr.level  
        f_curr = g_curr + h_curr
        #print("h_curr: ", h_curr, " g_curr: ", g_curr, " f_curr: ", f_curr)
        return f_curr  

    # function to calculate the f(n) = g(n) + h(n) using heuristic 2
    def f_2(self, curr):
        h_curr =  self.h_2(curr)
        g_curr = curr.level  
        f_curr = g_curr + h_curr
        #print("h_curr: ", h_curr, " g_curr: ", g_curr, " f_curr: ", f_curr)
        return f_curr

    # function to solve the puzzle using A* Algorithm using heuristic 1
    def aStar(self):
        start = Node(self.initial,0,0)
        start.f = self.f(start)
        unique = count()
        self.open.put((start.f,unique, start))
        while True:
            curr = self.open.get()[2]
            if(self.h(curr) == 0): 
                path = []
                while curr.parent is not None:
                    path.append(curr.data)
                    curr = curr.parent
                path.append(curr.data)
                path.reverse()
                break
            for child in curr.childGen():
                child.f = self.f(child)
                if child not in self.closed: 
                    self.open.put((child.f,next(unique), child))
            self.closed.append(curr)
         # the path from start to goal
        print("The path from start to goal: ")
        for cur in path:
            print("  | ")
            print("  | ")
            print(" \\\'/ \n")  
            for i in cur:
                for j in i:
                    print(j,end=" ")
                print("")

    # function to solve the puzzle using A* Algorithm using heuristic 2
    def aStar2(self):
        start = Node(self.initial,0,0)
        start.f = self.f_2(start)
        unique = count()
        self.open.put((start.f,unique, start))
        while True:
            curr = self.open.get()[2]
            if(self.h(curr) == 0): 
                path = []
                while curr.parent is not None:
                    path.append(curr.data)
                    curr = curr.parent
                path.append(curr.data)
                path.reverse()
                break
            for child in curr.childGen():
                child.f = self.f_2(child)
                if child not in self.closed: 
                    self.open.put((child.f,next(unique), child))
            self.closed.append(curr)
         # the path from start to goal
        print("The path from start to goal: ")
        for cur in path:
            print("  | ")
            print("  | ")
            print(" \\\'/ \n")  
            for i in cur:
                for j in i:
                    print(j,end=" ")
                print("")


    # def aStar(self):
    #     start = Node(self.initial,0,0)
    #     start.f = self.f(start)
    #     self.open.append(start)
    #     while True:
    #         curr = self.open[0]  
    #         if(self.h(curr) == 0):
    #             path = []
    #             while curr.parent is not None:
    #                 path.append(curr.data)
    #                 curr = curr.parent
    #             path.append(curr.data)
    #             path.reverse()
    #             break
    #         for child in curr.childGen():
    #             child.f = self.f(child)
    #             if child not in self.closed: self.open.append(child)
    #         self.closed.append(curr)
    #         del self.open[0]
    #         self.open.sort(key = lambda x:x.f, reverse=False)

    #     # the path from start to goal
    #     print("The path from start to goal: ")
    #     for cur in path:
    #         print("  | ")
    #         print("  | ")
    #         print(" \\\'/ \n")  
    #         for i in cur:
    #             for j in i:
    #                 print(j,end=" ")
    #             print("")


# Driver Code
def main():
    n = int(input("Enter the size of grid: "))
    initial_state = [['-' for i in range(n)] for i in range(n)]
    print("Please enter the initial state of the puzzle: ")
    for i in range(n):
        initial_state[i] = list(map(str, input().split()))
    final_state = [['-' for i in range(n)] for i in range(n)]
    print("Please enter the final state of the puzzle: ")
    for i in range(n):
        final_state[i] = list(map(str, input().split()))
    
    print("Initial state: ", initial_state)
    print("Final state: ", final_state)

    obj = Solution(n, initial_state, final_state)
    # Using Heuristic 1
    print("Solution Using Heuristic 1: ")
    obj.aStar()
    # Using Heuristic 2
    print("Solution Using Heuristic 2: ")
    obj.aStar2()
    

if __name__ == "__main__":
    main()

# Input 3
# Initial State:
# 2 8 3
# 1 6 4
# 7 - 5

# Final State:
# 1 2 3
# 8 - 4
# 7 6 5
