# 1) Generate a random data set x1 , . . . , xm of size m for
# (a) Exponential Distribution,
# (b) Uniform Distribution (self-study),
# (c) Bernoulli Distribution.
# Plot the sample mean (x1 + . . . + xm )/m for m = 10, 100, 500, 1000, 5000, 10000, 50000 for (a), (b), (c). This way, verify the weak law of large numbers (WLLN).
# 2) Generate a random data set of size 1000 for each independent and identically distributed
# (a) n Exponential Distribution,
# (b) n Uniform Distribution (self-study),
# (c) n Bernoulli Distribution.
# Numerically compute and plot the distribution of the sample mean (X1 +. . .+Xn )/n and corresponding “normal” approximation for n = 1, 2, 4, 8, 16, 32 for (a), (b), (c). This way, verify the Central Limit Theorem (CLT).
# Notes:
# 1. While generating data sets, consider the number (to be with the precision of) decimal place of 1. That is, if the random number generated is 1.4789 then consider it as 1.4.
# Optional: To get smoother results in Problems 1 and 2, consider the number (to be with the precision of) decimal place of 2. Also, in Problem 2, you may consider the sample size of 10000.
# 2. You may use in-built functions/libraries to generate samples from desired underlying distributions.
# 3. In Problem 1, the plot's x-axis should be the sample size m and the y-axis should be the sample mean.
# 4. In problem 2, numerically compute the distribution of Xi ’s from a data set of size 1000 and then plot. (In reality, the distribution of Xi is exactly exponential, uniform, or Bernoulli depending upon the subproblem (a), (b), or (c). But in this problem, you will be working with numerical data and finding distribution from this numerical data.)

# This program is done by CS20B1044 Avinash R Changrani

import numpy as np
import matplotlib.pyplot as plt
import random

m = [10, 100, 500, 1000, 5000, 10000, 50000]
d = {}

# 1 (a) Exponential Distribution

for i in m:
    sample = np.random.exponential(0.33, i)
    d[str(i)] = (np.mean(sample))

plt.bar(list(d.keys()), list(d.values()), color='cyan', width=0.4)

plt.xlabel("Sample Size")
plt.ylabel("Sample Mean")
plt.title("Exponential Distribution")
plt.show()

# Weak Law of Large Numbers => mean tends to expectation = scale = 1/lambda = 1/0.33

# 1 (b) Uniform Distribution

for i in m:
    sample = np.random.uniform(0, 1, i)
    d[str(i)] = (np.mean(sample))

plt.bar(list(d.keys()), list(d.values()), color='cyan', width=0.4)

plt.xlabel("Sample Size")
plt.ylabel("Sample Mean")
plt.title("Uniform Distribution")
plt.show()

# Weak Law of Large Numbers => mean tends to expectation = (a+b)/2 = (0+1)/2 = 0.5

# 1 (c) Bernoulli Distribution

for i in m:
    sample = np.random.binomial(1, 0.5, i)
    d[str(i)] = (np.mean(sample))

plt.bar(list(d.keys()), list(d.values()), color='cyan', width=0.4)

plt.xlabel("Sample Size")
plt.ylabel("Sample Mean")
plt.title("Bernoulli Distribution")
plt.show()

# Weak Law of Large Numbers => mean = expectation = p = 0.5

# 2 (a) n Exponential Distribution

n = [1, 2, 4, 8, 16, 32]

sample = np.random.exponential(0.33, 10000)
for i in n:
    d = {}
    for j in range(i):
        d[str(j+1)] = np.mean(random.choices(sample, k=1000))
    plt.rcParams["figure.figsize"] = [10, 7]
    plt.xlabel("Number of Samples = " + str(i))
    plt.ylabel("Sample Mean")
    plt.title("Exponential Distribution")
    plt.plot(d.keys(), d.values(), 'go-')
    plt.show()

# 2 (b) n Uniform Distribution

sample = np.random.uniform(0, 1, 10000)
for i in n:
    d = {}
    for j in range(i):
        d[str(j+1)] = np.mean(random.choices(sample, k=1000))
    plt.rcParams["figure.figsize"] = [10, 7]
    plt.xlabel("Number of Samples = " + str(i))
    plt.ylabel("Sample Mean")
    plt.title("Uniform Distribution")
    plt.plot(d.keys(), d.values(), 'go-')
    plt.show()


# 2 (c) n Bernoulli Distribution

sample = np.random.binomial(1, 0.5, 10000)
for i in n:
    d = {}
    for j in range(i):
        d[str(j+1)] = np.mean(random.choices(sample, k=1000))
    plt.rcParams["figure.figsize"] = [10, 7]
    plt.xlabel("Number of Samples = " + str(i))
    plt.ylabel("Sample Mean")
    plt.title("Bernoulli Distribution")
    plt.plot(d.keys(), d.values(), 'go-')
    plt.show()
