'''
The given diabetes1.csv file has diabetic information about female patients. The features/attributes in the file are as follows,
Pregnancies: Number of times pregnant
Glucose: Plasma glucose concentration 2 hours in an oral glucose tolerance test 
BloodPressure: Diastolic blood pressure (mm Hg) 
SkinThickness: Triceps skin fold thickness (mm) 
Insulin: 2-Hour serum insulin (mu U/mL) 
BMI: Body mass index (weight in kg/(height in m)^2) 
DiabetesPedigreeFunction: Diabetes pedigree function 
Age: Age (years) 
Outcome: Class variable (0 - non-diabetic or 1 - diabetic)
Write a python program (with pandas) to read the given data and display the following:

1. Mean, median, mode, minimum, maximum, and standard deviation for all the attributes excluding the attribute ‘Outcome’. Find the value of the correlation coefficient for ‘Age’ with all other attributes (excluding ‘Outcome’), and ‘BMI’ with all other attributes (excluding ‘Outcome’). Then, obtain the scatter plot between 
a. ‘Age’ and each of the other attributes, excluding ‘Outcome’ 
b. ‘BMI’ and each of the other attributes, excluding ‘Outcome’ (You can use matplotlib library).

2. Plot the histogram for the attributes ‘Pregnancies’ and ‘SkinThickness’ (You may use “hist” function from pandas). Plot the histogram of attribute ‘Pregnancies’ and for each of the 2 Outcomes individually (Use “groupby” function to group the tuples according to their “Outcome”). Obtain the boxplot for all the attributes excluding ‘Outcome’ (Use “boxplot” function).
'''

# This program is done by CS20B1044 Avinash R Changrani

import numpy as np
import pandas as pd
#import statistics as st
import matplotlib.pyplot as plt

df = pd.read_csv("./diabetes1.csv")

# Mean, median, mode, minimum, maximum, and standard deviation for all the attributes excluding the attribute ‘Outcome’.
for i in df.columns:
    if(i != 'Outcome'):
        print("The Mean of " + str(i) + " is " + str(np.mean(np.array(df[i]))))
        print("The Median of " + str(i) + " is " +
              str(np.median(np.array(df[i]))))
        vals, counts = np.unique(np.array(df[i]), return_counts=True)
        index = np.argmax(counts)
        print("The Mode of " + str(i) + " is " + str(vals[index]))
        #print("The Mode of " + str(i) + " is " + str(st.mode(np.array(df[i]))))
        print("The Minimum of " + str(i) +
              " is " + str(np.min(np.array(df[i]))))
        print("The Maximum of " + str(i) +
              " is " + str(np.max(np.array(df[i]))))
        print("The Standard Deviation of " + str(i) +
              " is " + str(np.std(np.array(df[i]))))

# Find the value of the correlation coefficient for ‘Age’ with all other attributes (excluding ‘Outcome’), and ‘BMI’ with all other attributes (excluding ‘Outcome’).
for i in df.columns:
    if(i != 'Outcome'):
        print("The correlation coefficient between Age and " +
              str(i) + " is " + str(df['Age'].corr(df[i])))
        print("The correlation coefficient between BMI and " +
              str(i) + " is " + str(df['BMI'].corr(df[i])))

# Scatterplot
for i in df.columns:
    if(i != 'Outcome'):
        plt.scatter(df['Age'], df[i])
        plt.xlabel('Age')
        plt.ylabel(i)
        plt.show()
        plt.scatter(df['BMI'], df[i])
        plt.xlabel('BMI')
        plt.ylabel(i)
        plt.show()

# Plot the histogram for the attributes ‘Pregnancies’ and ‘SkinThickness’
df.hist(column='Pregnancies')
plt.show()
df.hist(column='SkinThickness')
plt.show()

# lot the histogram of attribute ‘Pregnancies’ and for each of the 2 Outcomes individually
df.hist(column='Pregnancies', by='Outcome')
plt.show()

# Obtain the boxplot for all the attributes excluding ‘Outcome’
for i in df.columns:
    if(i != 'Outcome'):
        plt.boxplot(np.array(df[i]))
        plt.title(i)
        plt.show()
