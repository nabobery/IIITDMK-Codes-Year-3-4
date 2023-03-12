# In the TSP,  given a set of cities and the distance between each pair of cities, a salesman needs to choose the shortest path to visit every city exactly once and return to the city from where he started. Here, the nodes represent cities, and the values in each edge denote the distance between one city to another. Here the shortest path means the sum of the distance between each city travelled by the salesman, and it should be less than any other path. Implement Simulated Annealing (SA) algorithm to solve the above problem. 

# Implement your algorithm based on following points

# Randomly take 15 cities as 2D random points (x,y) on a grid (0<x<10, 0<y<10)
# Distance between two cities is the Euclidean distance between two corresponding points on the grid
# Randomly take one point as the starting city
# Plot the points and show the initial path taken
# Write the SA optimization algorithm. Do not use predefined libraries to perform SA 
# Take the starting temperature as 1e+10 and the temperature schedule as a GP progression of cooling factor 0.97
# Experiment for different starting temperatures and cooling factors
# Plot the iteration vs cost graph during the optimization
# Plot the final solution and corresponding cost
# What will happen if you take the temperature schedule as AP series
# Link: https://towardsdatascience.com/optimization-techniques-simulated-annealing-d6a4785a1de7

# This program is done by CS20B1044 Avinash R Changrani

import math
import random
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation

# class to generate random nodes from 0 to max height and width
class RandomNodes:
    def __init__(self, height, width, n):
        self.height = height
        self.width = width
        self.n = n
        self.nodes = []

    def generate(self):
        while len(self.nodes) < self.n:
            point = (random.randint(0, self.width), random.randint(0, self.height))
            if point not in self.nodes:
                self.nodes.append(point)
        return self.nodes


# function to calculate the distance matrix for all the nodes
def get_distance_matrix(nodes):
    distance_matrix = []
    for i in range(len(nodes)):
        distance_matrix.append([])
        for j in range(len(nodes)):
            distance_matrix[i].append(math.sqrt((nodes[i][0] - nodes[j][0]) ** 2 + (nodes[i][1] - nodes[j][1]) ** 2))
    return distance_matrix

# function to calculate path(initial solution) using nearest neighbour algorithm
def nearest_neighbour_path(distance_matrix):
    # start from a random node
    node = random.randrange(len(distance_matrix))
    result = [node]

    # nodes to visit
    nodes_to_visit = list(range(len(distance_matrix)))
    nodes_to_visit.remove(node)

    while nodes_to_visit:
        # find the nearest node
        nearest_node = min([(distance_matrix[node][j], j) for j in nodes_to_visit], key=lambda x: x[0])
        node = nearest_node[1]
        nodes_to_visit.remove(node)
        result.append(node)

    return result

# function to animate the TSP solution over time using matplotlib
def animate_tsp(history,points):
    fig, ax = plt.subplots()
    ax.set_xlim(0, 10)
    ax.set_ylim(0, 10)
    ax.set_title('TSP Solution')

    # plot the points
    x = [i[0] for i in points]
    y = [i[1] for i in points]
    ax.scatter(x, y, c='r', s=50)

    # plot the lines
    lines = []
    for i in range(len(history[0])):
        line, = ax.plot([], [], 'b')
        lines.append(line)

    def animate(i):
        for j in range(len(history[0])):
            lines[j].set_data([points[history[i][j]][0], points[history[i][(j + 1) % len(history[0])]][0]],
                              [points[history[i][j]][1], points[history[i][(j + 1) % len(history[0])]][1]])
        return lines

    anim = FuncAnimation(fig, animate, frames=len(history), interval=100, blit=True)
    plt.show()

# SA algorithm to find the optimal solution
class simulatedAnnealing:
    def __init__(self, nodes, initial_temperature, cooling_factor, stopping_temperature, stopping_iter):
        self.nodes = nodes
        self.initial_temperature = initial_temperature
        self.cooling_factor = cooling_factor
        self.stopping_temperature = stopping_temperature  
        self.stopping_iter = stopping_iter
        self.distance_matrix = get_distance_matrix(nodes)
        self.iteration = 1
        self.curr_solution = nearest_neighbour_path(self.distance_matrix)
        self.best_solution = self.curr_solution
        self.solution_history = [self.curr_solution]

        self.curr_weight = self.weight(self.curr_solution)
        self.initial_weight = self.curr_weight
        self.min_weight = self.curr_weight
        self.weight_list = [self.curr_weight]
        print('Intial weight: ', self.curr_weight)

    # function to calculate the weight of the path
    def weight(self, path):
        return sum([self.distance_matrix[path[i]][path[i - 1]] for i in range(len(path))])

    # function to calculate the acceptance probability (e^(-delta E)/ T)
    def acceptance_probability(self, candidate_weight):
        return math.exp(-abs(candidate_weight - self.curr_weight) / self.initial_temperature)

    # function to accept the candidate solution
    def accept(self, candidate):
        candidate_weight = self.weight(candidate)
        if candidate_weight < self.curr_weight:
            self.curr_weight = candidate_weight
            self.curr_solution = candidate
            if candidate_weight < self.min_weight:
                self.min_weight = candidate_weight
                self.best_solution = candidate
        else:
            if random.random() < self.acceptance_probability(candidate_weight):
                self.curr_weight = candidate_weight
                self.curr_solution = candidate

    # function for annealing
    def anneal(self):
        while self.initial_temperature >= self.stopping_temperature and self.iteration < self.stopping_iter:
            candidate = list(self.curr_solution)
            l = random.randint(2, len(self.nodes) - 1)
            i = random.randint(0, len(self.nodes) - l)
            candidate[i: (i + l)] = reversed(candidate[i: (i + l)])
            self.accept(candidate)
            self.initial_temperature *= self.cooling_factor
            self.iteration += 1
            self.solution_history.append(self.curr_solution)
            self.weight_list.append(self.curr_weight)
        print('Final weight: ', self.curr_weight)
        print('Minimum weight: ', self.min_weight)
        print('Improvement: ', (self.initial_weight - self.min_weight) / self.initial_weight * 100, '%')

    # function to animate the TSP solution over time using matplotlib
    def animate_tsp_solution(self, history, points):
        animate_tsp(history, points)

    # function to plot the graph of iteration vs cost to show the Learning curve
    def plot_iteration_vs_cost(self):
        plt.plot([i for i in range(len(self.weight_list))], self.weight_list)
        line_init = plt.axhline(y=self.initial_weight, color='r', linestyle='--')
        line_min = plt.axhline(y=self.min_weight, color='g', linestyle='--')
        plt.legend([line_init, line_min], ['Initial weight', 'Optimized weight'])
        plt.xlabel('Iteration')
        plt.ylabel('Cost')
        plt.title('Iteration vs Cost')
        plt.show()

# main function
def main():
    # parameters for the TSP problem using Simulated Annealing
    temp = 10**10
    stopping_temp = 0.000000000001
    alpha = 0.97
    stopping_iter = 100000
    size_width = 10
    size_height = 10
    n = 15

    nodes = RandomNodes(size_height, size_width, n).generate()
    sa = simulatedAnnealing(nodes, temp, alpha, stopping_temp, stopping_iter)
    sa.anneal()
    sa.animate_tsp_solution(sa.solution_history, sa.nodes)
    sa.plot_iteration_vs_cost()


if __name__ == '__main__':
    main()


    