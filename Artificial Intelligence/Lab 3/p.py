# In the TSP,  given a set of cities and the distance between each pair of cities, a salesman needs to choose the shortest path to visit every city exactly once and return to the city from where he started. Here, the nodes represent cities, and the values in each edge denote the distance between one city to another. Here the shortest path means the sum of the distance between each city travelled by the salesman, and it should be less than any other path. Implement Depth First Search (DFS), Breadth First Search (BFS) and Iterative Deepening Search (ids_helper) to implement the above.

# This program is done by CS20B1044 Avinash R Changrani

n = 0
visited = []
costs = []

# dfs function to find the minimum cost of the TSP


def dfs(graph, curr, count, cost):
    global n, visited, costs
    # base case to check if all the nodes are visited and the path is complete
    if count == n and graph[curr][0]:
        costs.append(cost + graph[curr][0])
        return
    # recursive case to check for all the nodes
    for i in range(n):
        if not visited[i] and graph[curr][i]:
            visited[i] = True
            dfs(graph, i, count + 1, cost + graph[curr][i])
            visited[i] = False

# bfs helper function to find total cost of the path


def distance(path, graph):
    result = 0
    if(len(path) == 1):
        return result
    else:
        for i in range(len(path) - 1):
            result += graph[path[i]][path[i + 1]]
    return result

# bfs function to find the minimum cost of the TSP


def bfs(graph):
    global n
    min_cost = 10**20
    best_route = []
    path = [0]
    queue = [(0, path)]
    while queue:
        # get the front element in the queue
        (curr, path) = queue.pop(0)
        # check for all the nodes
        for i in range(n):
            # check if the node is not visited and there is a path between the nodes
            if graph[curr][i]:
                # check if the path is complete and the path is the best path
                if len(path) == n and i == 0:
                    temp = path + [i]
                    temp_dist = distance(temp, graph)
                    if temp_dist < min_cost:
                        min_cost = temp_dist
                        best_route = temp
                # check if the path is not complete and the node is not visited
                elif i not in path:
                    queue.append((i, path + [i]))
    print("The minimum cost of Travelling Salesman Problem using BFS is: " + str(min_cost))
    print("The best route using BFS is: " + str(best_route))


# ids_helper function which goes till depth limit and then returns
def ids_helper(graph, curr, count, cost, limit):
    global n, visited, costs
    # base case to check if all the nodes are visited and the path is complete
    if count == n and graph[curr][0]:
        costs.append(cost + graph[curr][0])
        return

    # base case to check if the depth limit is reached
    if limit <= 0:
        return

    # recursive case to check for all the nodes
    for i in range(n):
        # check if the node is not visited and there is a path between the nodes
        if not visited[i] and graph[curr][i]:
            visited[i] = True
            ids_helper(graph, i, count + 1, cost + graph[curr][i], limit - 1)
            visited[i] = False

# ids function to find the minimum cost of the TSP


def ids(graph):
    global n
    for i in range(n):
        ids_helper(graph, 0, 1, 0, i)


# main function
def main():
    global n, visited, costs
    # input the number of nodes and the distance matrix
    print("Please enter the number of nodes: ")
    n = int(input())
    dist = [[0 for i in range(n)] for i in range(n)]
    print("Please enter the distance matrix: ")
    for i in range(n):
        dist[i] = list(map(int, input().split()))
    visited = [False for i in range(n)]
    dfs(dist, 0, 1, 0)
    print("The minimum cost of Travelling Salesman Problem using DFS is: " + str(min(costs)))
    bfs(dist)
    costs = []
    ids(dist)
    print("The minimum cost of Travelling Salesman Problem using IDS is: " + str(min(costs)))


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
