# The travelling salesman problem (also called the travelling salesperson problem or TSP) asks the following question: "Given a list of cities and the distances between each pair of cities, what is the shortest possible route that visits each city exactly once and returns to the origin city?"
# This program is done by CS20B1044 Avinash R Changrani

path = []

def helper(i, mask, dist, dp):
    if mask == ((1 << i) | 3):
        return dist[1][i]
    if dp[i][mask]:
        return dp[i][mask]
    ans = 10**20
    for k in range(1, len(dist)):
        if mask & (2**k) and k != i and k != 1:
            ans = min(ans, helper(k,  mask & (~(1 << i)), dist, dp) + dist[k][i])
    
    dp[i][mask] = ans
    return ans  

def tsp(n,distance):
    res = 10**20 
    dp = [[0 for i in range(2**(n+1))] for i in range(n+1)]
    for i in range(1,n+1):
        res = min(res, helper(i, 2**(n+1) - 1, distance,dp) + distance[i][1])

    print("The cost for the shortest route is " + str(res))  
    
def main():
    print("Please enter the number of nodes: ")
    n = int(input())
    dist = [[0 for i in range(n+1)] for i in range(n+1)]
    path = [0 for i in range(n)]
    print("Please enter the distance matrix: ")
    for i in range(1,n+1):
        str = input()
        j = 1
        for k in range(n):
            dist[i][j] = list(map(int, str.split()))[k]
            j += 1
    #print(dist)
    tsp(n, dist)


if __name__ == '__main__':
    main()


# sample input:
# 4
# 0 10 15 20
# 10 0 25 25
# 15 25 0 30
# 20 25 30 0

# given input :
# 5
# 0 12 10 19 8
# 12 0 3 7 6
# 10 3 0 2 20
# 19 7 2 0 4
# 8 6 20 4 0

# E -> D -> C -> B -> A