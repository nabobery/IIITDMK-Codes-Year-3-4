# In the TSP,  given a set of cities and the distance between each pair of cities, a salesman needs to choose the shortest path to visit every city exactly once and return to the city from where he started. Here, the nodes represent cities, and the values in each edge denote the distance between one city to another. Here the shortest path means the sum of the distance between each city travelled by the salesman, and it should be less than any other path. Implement A* or DFBB or IDA* algorithm to solve the above problem. 

# The heuristic function is as follows:

# h( n ) = COST OF MINIMUM COST SPANNING TREE OF REMAINING NODES (As discussed in the class)

# Link: https://www.public.asu.edu/~huanliu/AI04S/project1.htm
# This program is done by CS20B1044 Avinash R Changrani
import sys
from queue import PriorityQueue
from copy import deepcopy
from itertools import count

n = 0
nodes = []

# Graph class to implement Prim's MST algorithm
class Graph:
    # Constructor
    def __init__(self, graph, start):
        global n
        self.graph = graph
        self.start = start
        self.key = [sys.maxsize] * n
        self.parent = [-1] * n
        self.mstSet = [False] * n
        self.key[start] = 0
        self.parent[start] = -1
        self.mstweight = 0

    # Function to print MST
    def printMST(self):
        global n
        print("Edge \tWeight")
        for i in range(n):
            if self.parent[i] != -1 and i != self.start:
                print(nodes[i], "-", nodes[self.parent[i]],
                      "\t", self.graph[i][self.parent[i]])

    # Function to implement Prim's MST algorithm
    def primMST(self):
        global n
        pq = PriorityQueue()
        pq.put((0, 0))
        # Loop until priority queue is empty
        while not pq.empty():
            # Get the minimum key vertex from priority queue
            u = pq.get()[1]
            self.mstSet[u] = True
            # Update key value and parent index of the adjacent vertices of the picked vertex.
            for v in range(n):
                # Update the key only if graph[u][v] is smaller than key[v]
                if self.graph[u][v] > 0 and self.mstSet[v] == False and self.graph[u][v] < self.key[v]:
                    self.key[v] = self.graph[u][v]
                    pq.put((self.key[v], v))
                    self.parent[v] = u
        # Get the cost of the constructed MST
        for i in range(n):
            if self.parent[i] != -1 and i != self.start:
                self.mstweight += self.graph[i][self.parent[i]]
        return self.mstweight

# Node class to store the current node, parent node, depth, cost till now and visited nodes


class node:
    def __init__(self, currnode, parent, depth, g, visited):
        self.currnode = currnode
        self.parent = parent
        self.depth = depth
        self.g = g
        self.visited = visited

# TSP class to implement A* algorithm
class TSP:
    # Constructor
    def __init__(self, graph, start=0):
        self.graph = Graph(graph, 0)
        initnode = node(start, None, 0, 0, set())
        self.startNode = start
        self.curr = initnode
        self.pq = PriorityQueue()
        self.unique = count()
        self.pq.put((0, next(self.unique), self.curr))
        self.unvisited = deepcopy(self.graph.graph)

    # Function to print the path
    def printPath(self, Node: node):
        if Node is None:
            return
        self.printPath(Node.parent)
        print("At Level: ", Node.depth, " Visited: ",
              Node.visited, " Cost till now: ", Node.g)

    # Function to generate child nodes
    def childGen(self, parentnode: node, childnode, wt, h):
        g = parentnode.g + wt
        f = g + h
        childvisited = parentnode.visited.copy()
        child = node(childnode, parentnode,
                     parentnode.depth + 1, g, childvisited)
        self.pq.put((f, next(self.unique), child))

    # Function to check if the current node is the goal node
    def goalTest(self):
        global n
        if self.curr.depth + 1 == n and len(self.curr.visited) == n:
            return True
        return False

    # Function to implement A* algorithm
    def successor(self):
        global n, nodes
        while not self.pq.empty():
            self.curr = self.pq.get()[2]
            self.curr.visited.add(self.curr.currnode)
            if self.goalTest():
                self.printPath(self.curr)
                backtostart = self.graph.graph[0][self.curr.currnode]
                print("Going back to start (", nodes[self.curr.currnode], " to ",
                      nodes[self.startNode], ") Cost: ", self.curr.g + backtostart)
                print("Total Cost: ", self.curr.g + backtostart)
                return
            else:
                self.unvisited = deepcopy(self.graph.graph)
                for i in range(n):
                    for j in self.curr.visited:
                        self.unvisited[i][j] = sys.maxsize
                        self.unvisited[j][i] = sys.maxsize

                for c, wt in enumerate(self.graph.graph[self.curr.currnode]):
                    if wt != 0 and c not in self.curr.visited:
                        unvisitedGraph = Graph(self.unvisited, c)
                        h = unvisitedGraph.primMST()
                        self.childGen(self.curr, c, wt, h)
        return


# main function
def main():
    global n
    # get the number of nodes
    print("Please enter the number of nodes: ")
    n = int(input())
    dist = [[0 for i in range(n)] for i in range(n)]
    # get the distance matrix
    print("Please enter the distance matrix: ")
    for i in range(n):
        dist[i] = list(map(int, input().split()))
    for i in range(n):
        nodes.append(chr(65 + i))

    # print(nodes)
    obj = TSP(dist)
    obj.successor()


if __name__ == "__main__":
    main()


# Input
# 5
# 0 12 10 19 8
# 12 0 3 7 6
# 10 3 0 2 20
# 19 7 2 0 4
# 8 6 20 4 0

# 0 - A, 1 - B, 2 - C, 3 - D, 4 - E

# Output : 29
