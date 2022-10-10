# This program is done by CS20B1044 Avinash R Changrani
# importing libraries required for this program
import pandas as pd
import numpy as np
import math

data = pd.read_csv('./diabetes.csv')

end = math.ceil(0.8*len(data))

# using 80% of given data as training data
train_data = data[:end]

# other 20% of data for testing
test_data = data[end:]
test_outcomes = np.array(test_data['Outcome'])
test_data.drop('Outcome', axis=1, inplace=True)

# dividing into 2 sections/clusters based on Outcome
outcome_diabetic = train_data.loc[train_data['Outcome'] == 1]
outcome_non_diabetic = train_data.loc[train_data['Outcome'] == 0]

outcome_diabetic.drop('Outcome', axis=1, inplace=True)
outcome_non_diabetic.drop('Outcome', axis=1, inplace=True)

outcome_diabetic_mean = []
outcome_non_diabetic_mean = []

# Minimum Distance Classifier Algorithm
# Calculating mean for each feature
for i in range(len(outcome_diabetic.columns)):
    outcome_diabetic_mean.append(
        np.mean(outcome_diabetic[outcome_diabetic.columns[i]]))

for i in range(len(outcome_non_diabetic.columns)):
    outcome_non_diabetic_mean.append(
        np.mean(outcome_non_diabetic[outcome_non_diabetic.columns[i]]))

predicted_outcomes = []

for i in range(len(test_data)):
    temp = np.array(test_data.iloc[i])
    # get the 2 distances from the mean features using the given test's features
    dist1 = np.sum((temp - outcome_diabetic_mean)**2)
    dist2 = np.sum((temp - outcome_non_diabetic_mean)**2)
    # if given data is nearer to the diabetic mean then include it into the 1st cluster
    if dist1 <= dist2:
        predicted_outcomes.append(1)
    # else include in the 2nd cluster of non-diabetic
    else:
        predicted_outcomes.append(0)

print("The predicted outcomes from the minimum distance classifier algorithm is: ")
print(np.array(predicted_outcomes))

accuracy1 = 0

for i in range(len(test_outcomes)):
    if predicted_outcomes[i] == test_outcomes[i]:
        accuracy1 += 1

accuracy1 /= len(test_outcomes)

print("The Accuracy of the Minimum Distance Classifier Model is " + str(accuracy1))


# K Means Algorithm
train_data.drop('Outcome', axis=1, inplace=True)
# We use the mean from before as initial centroids and intialise number of elements traversed
cluster1 = 1
cluster2 = 1
# Training the Model with the training data
for i in range(len(train_data)):
    temp = np.array(train_data.iloc[i])
    # get the 2 distances from the mean features using the given test's features
    dist1 = np.sum((temp - outcome_diabetic_mean)**2)
    dist2 = np.sum((temp - outcome_non_diabetic_mean)**2)
    # if given data is nearer to the diabetic mean then include it into the 1st cluster and update the cluster mean
    if dist1 <= dist2:
        outcome_diabetic_mean = (
            outcome_diabetic_mean*cluster1 + temp)/(cluster1 + 1)
        cluster1 += 1
    else:
        outcome_non_diabetic_mean = (
            outcome_non_diabetic_mean*cluster2 + temp)/(cluster2 + 1)
        cluster2 += 1

predicted_outcomes = []

# predict the outcomes for the test data
for i in range(len(test_data)):
    temp = np.array(test_data.iloc[i])
    # get the 2 distances from the mean features using the given test's features
    dist1 = np.sum((temp - outcome_diabetic_mean)**2)
    dist2 = np.sum((temp - outcome_non_diabetic_mean)**2)
    # if given data is nearer to the diabetic mean then include it into the 1st cluster
    if dist1 <= dist2:
        predicted_outcomes.append(1)
    # else include in the 2nd cluster of non-diabetic
    else:
        predicted_outcomes.append(0)


print("The predicted outcomes from the minimum distance classifier algorithm is: ")
print(predicted_outcomes)

accuracy2 = 0

for i in range(len(test_outcomes)):
    if predicted_outcomes[i] == test_outcomes[i]:
        accuracy2 += 1

accuracy2 /= len(test_outcomes)

print("The Accuracy of the Minimum Distance Classifier Model is " + str(accuracy2))
