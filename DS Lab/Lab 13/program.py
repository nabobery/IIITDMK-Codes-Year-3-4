'''
You are given the Steel Plates Faults Data Set as a csv file (SteelPlateFaults-2class.csv). This dataset comes from research by Semeion, Research Center of Sciences of Communication. The original aim of the research was to correctly classify the type of surface defects in stainless steel plates, with six types of possible defects (plus "other"). The Input vector is made up of 27 indicators that approximately describe the geometric shape of the defect and its outline. As Semeion was commissioned by the Centro Sviluppo Materiali (Italy) for this task and therefore the details of the nature of the 27 indicators used as input vectors or the types of the 6 classes of defects are confidential.
The dataset used for this assignment contains features extracted from the steel plates of types A300 and A400 to predict whether the image of the surface of the steel plate contains two types of faults such as Z_Scratch and K-Scratch. It consists of 1119 tuples each having 27 attributes which are indicators representing the geometric shape of the fault. The last attribute (28 th attribute) for every tuple signifies the class label (0 for K_Scratch fault and 1 for Z_Scratch fault). It is a two-class problem.
Attribute Information:
The fault description is constituted of 27 indicators representing the geometric shape of the fault and its contour.
1. X_Minimum
2. X_Maximum
3. Y_Minimum
4. Y_Maximum
5. Pixels_Areas
6. X_Perimeter
7. Y_Perimeter
8. Sum_of_Luminosity
9. Minimum_of_Luminosity
10. Maximum_of_Luminosity
11. Length_of_Conveyer
12. TypeOfSteel_A300
13. TypeOfSteel_A400
14. Steel_Plate_Thickness
15. Edges_Index
16. Empty_Index
17. Square_Index
18. Outside_X_Index
19. Edges_X_Index
20. Edges_Y_Index
21. Outside_Global_Index
22. LogOfAreas
23. Log_X_Index
24. Log_Y_Index
25. Orientation_Index
26. Luminosity_Index
27. SigmoidOfAreas
1. Write a python program to split the data of each class from SteelPlateFaults-2class.csv into train data and test data. Train data contain 70% of tuples from each of the class and test data contain remaining 30% of tuples from each class. Store the train data and test data in separate NumPy arrays
Note: Use the command train_test_split from scikit-learn given below to split the data (keep random_state=42 to get the same random values for every students).
Example:
[X_train, X_test, X_label_train, X_label_test] = train_test_split(X, X_label, test_size=0.3, random_state=42, shuffle=True)
Classify every test tuple using K-nearest neighbor (KNN) method for the different values of K=1, 3, and 5. Perform the following analysis:
a. Find the confusion matrix (use 'confusion_matrix' function from scikit-learn) for each K.
b. Find the classification accuracy (You can use 'accuracy_score' function) for each K. Note the value of K for which the accuracy is high.
2. Normalize all the attributes (except class attribute) of train and test NumPy arrays using Min-Max normalization to transform the data in the range [0-1]. Store the result in a separate NumPy array. Classify every test tuple using K-nearest neighbor (KNN) method for the different values of K=1, 3, and 5. Perform the following analysis:
a. Find confusion matrix for each K.
b. Find the classification accuracy for each K. Note the value of K for which the accuracy is high.
What is your overall inference? Write your answer as a comment or doc string at the beginning of your python script.
Best Practice:
It is always a good practice to save your train and test splits as csv files for future use. You can avoid rerunning the split part of your code saving computation resources (very useful for large data). As writing to csv file in moodle is not well-supported, we are storing the resulting files in NumPy arrays.
'''

# This program is done by CS20B1044 Avinash R Changrani

# include the required libraries
import numpy as np
import pandas as pd
import sklearn
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import MinMaxScaler

# store the csv data in a dat frame
df = pd.read_csv("./SteelPlateFaults-2class.csv")

# we choose odd values of k to avoid tie between the 2 classes
k_values = [1, 3, 5]

y = df['Class']
X = df.drop('Class', axis=1)
# split the training and testing data
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.3, random_state=42, shuffle=True)

for k in k_values:
    knn = KNeighborsClassifier(n_neighbors=k)
    knn.fit(X_train, y_train)
    y_pred = knn.predict(X_test)
    # 1 a) confusion matrix
    print("Confusion matrix for  k = " + str(k) + " : ")
    cm = confusion_matrix(y_test, y_pred)
    # 1 b) model accuracy score
    print("Accuracy for k = " + str(k) + ": ", accuracy_score(y_test, y_pred))
    print(cm)

# The value of K for which the accuracy is high is k=5 (without Normalization)

# Normalizing the data using MinMaxScaler
min_max = MinMaxScaler()
# normalizing the data without the class Attribute
N_X = min_max.fit_transform(X)
# now split it into  training and testing data
X_train, X_test, y_train, y_test = train_test_split(
    N_X, y, test_size=0.3, random_state=42, shuffle=True)

for k in k_values:
    knn = KNeighborsClassifier(n_neighbors=k)
    knn.fit(X_train, y_train)
    y_pred = knn.predict(X_test)
    # 2 a) confusion matrix
    print("Confusion matrix for  k = " + str(k) + " after Normalization : ")
    cm = confusion_matrix(y_test, y_pred)
    # 2 b) model accuracy score
    print("Accuracy for k = " + str(k) + " after Normalization : ",
          accuracy_score(y_test, y_pred))
    print(cm)

# The value of K for which the accuracy is high is k=3 (with Normalization)

# Normalisation increases model accuracy for all k across the board. Using Normalisation we're limiting the range of the data between 0 to 1. So it's not being affected much by any outliers.Therefore, improves the model accuracy.
#  Normalization gives equal weights/importance to each variable so that no single variable steers model performance in one direction just because they are bigger numbers.
