# This program is done by CS20B1044 Avinash R Changrani
# Solve the following Knapsack problem using heuristic search methods.
# Capacity: 400 oz Weight : 1,10,100,200,300 Cost: 5000,1000,2000,5000,4000
# Optimal Cost = 13000 and weight = 311 oz

# dp solution for knapsack problem
def KnapsackSolver(weights, values, capacity):
    n = len(weights)
    dp = [[0 for _ in range(capacity + 1)] for _ in range(n + 1)]
    # dp[i][j] represents the maximum value that can be obtained with a capacity of j
    for i in range(1, n + 1):
        for j in range(1, capacity + 1):
            # if the weight of the item is less than or equal to the capacity
            if weights[i - 1] <= j:
                dp[i][j] = max(
                    dp[i - 1][j], values[i - 1] + dp[i - 1][j - weights[i - 1]]
                )
            # if the weight of the item is greater than the capacity
            else:
                dp[i][j] = dp[i - 1][j]
    return dp[n][capacity]


def main():
    n = int(input("Please enter the number of items: "))
    weights = [0 for _ in range(n)]
    values = [0 for _ in range(n)]
    print("Please enter the weights: ")
    weights = list(map(int, input().split()))
    print("Please enter the values: ")
    values = list(map(int, input().split()))
    capacity = int(input("Please enter the capacity: "))
    print("The maximum value is: ", KnapsackSolver(weights, values, capacity))

if __name__ == "__main__":
    main()

# Input
# Please enter the number of items: 5
# Please enter the weights: 1 10 100 200 300
# Please enter the values: 5000 1000 2000 5000 4000
# Please enter the capacity: 400

# Output
# The maximum value is: 13000
