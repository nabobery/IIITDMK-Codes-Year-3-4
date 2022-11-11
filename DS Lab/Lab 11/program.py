# This program is done by CS20B1044 Avinash R Changrani

import pandas as pd
import numpy as np
import math
import matplotlib.pyplot as plt

# 1 (a) Plot a graph of the attribute names (x-axis) with the number of missing values in them (y-axis)
df = pd.read_csv("./landslide_data3_miss.csv")

x = []

for i in df.columns:
    x.append(i)

y = []

for i in df.columns:
    y.append(df[i].isnull().sum())

dict = {'Attributes': x, 'Missing Values': y}

temp_df = pd.DataFrame(dict)

# temp_df.plot.bar(x='Attributes', y='Missing Values', rot=0)

# plt.show()

# 1 (b) Target attribute is “stationid”, Drop the tuples (rows) having missing values in the target attribute. Print the total number of tuples deleted. Delete (drop) the tuples (rows) having equal to or more than one third of attributes with missing values. Print the total number of tuples deleted.
df1 = df.dropna(axis=0, subset=['stationid'])

result = len(df) - len(df1)

print("Number of tuples deleted after dropping rows having missing values in stationid is: " + str(result))

df2 = df1.dropna(thresh=df1.shape[1] + 1 - df1.shape[1]/3, axis=0)

result = len(df1) - len(df2)

print("Number of tuples deleted after dropping rows having equal to or more than one third of attributes with missing values is: " + str(result))

# 1 (c) After (b), count and print the number of missing values in each attributes. Also find and print the total number of missing values in the file (after the deletion of tuples).
result = 0
for i in df2.columns:
    print("Missing Values in " + i + " is " + str((df2[i].isnull().sum())))
    result += (df2[i].isnull().sum())

print("The total number of missing values in the file (after the deletion of tuples) is " + str(result))


# 2 (a) Replace the missing values by mean of their respective attribute.

# print(df2.head())
df3 = pd.read_csv("./landslide_data3_original.csv")
df4 = df.copy()

for i in df.mean(numeric_only=True).keys():
    if df[i].isnull().sum() > 0:
        df[i].fillna(np.mean(df[i]), inplace=True)

# Compute the mean, median, mode and standard deviation for each attributes and compare the same with that of the original file.
print()
for i in df.mean(numeric_only=True).keys():
    print("Original Mean of " + i + " is " + str(df3.mean(numeric_only=True)
          [i]) + " and Current Mean is " + str(df.mean(numeric_only=True)[i]))
    print("Original Median of " + i + " is " + str(df3.median(numeric_only=True)
          [i]) + " and Current Median is " + str(df.median(numeric_only=True)[i]))
    print("Original Mode of " + i + " is " + str(df3.mode(numeric_only=True)
          [i][0]) + " and Current Mode is " + str(df.mode(numeric_only=True)[i][0]))
    print("Original Standard Deviation of " + i + " is " + str(df3.std(numeric_only=True)
          [i]) + " and Current Standard Deviation is " + str(df.std(numeric_only=True)[i]))
    print()


# print(df3.tail())

# Calculate the root mean square error (RMSE) between the original and replaced values for each attribute. (Get original values from original file provided). Compute RMSE given by the equation at the end of the question. Plot these RMSE with respect to the attributes
rsme = []
x = []
for i in df4.mean(numeric_only=True).keys():
    result = 0
    temp = np.mean(df4[i])
    x.append(i)
    for j in range(len(df4[i])):
        if pd.isna(df4[i][j]):
            result += (temp - df3[i][j])**2
    result /= df4[i].isnull().sum()
    result = math.sqrt(result)
    rsme.append(result)
    print("The RSME for " + i + " is " + str(result))

print()

dict1 = {'Attributes': x, 'RSME': rsme}

temp_df1 = pd.DataFrame(dict1)

# temp_df1.plot.bar(x='Attributes', y='RSME', rot=0)

# plt.show()

# 2 (b) Replace the missing values in each attribute using the linear interpolation technique. Use df.interpolate() with suitable arguments.
df5 = df4.copy()
df4.interpolate(method='linear', inplace=True)

# for i in df4.columns:
#     print("Missing Values in " + i + " is " + str((df4[i].isnull().sum())))

# Compute the mean, median, mode and standard deviation for each attributes and compare with that of the original file.
for i in df4.mean(numeric_only=True).keys():
    print("Original Mean of " + i + " is " + str(df3.mean(numeric_only=True)
          [i]) + " and Current Mean is " + str(df4.mean(numeric_only=True)[i]))
    print("Original Median of " + i + " is " + str(df3.median(numeric_only=True)
          [i]) + " and Current Median is " + str(df4.median(numeric_only=True)[i]))
    print("Original Mode of " + i + " is " + str(df3.mode(numeric_only=True)
          [i][0]) + " and Current Mode is " + str(df4.mode(numeric_only=True)[i][0]))
    print("Original Standard Deviation of " + i + " is " + str(df3.std(numeric_only=True)
          [i]) + " and Current Standard Deviation is " + str(df4.std(numeric_only=True)[i]))
    print()


# Calculate the root mean square error (RMSE) between the original and replaced values for each attributes. (Get original values from the original file provided). Compute RMSE given by the equation at the end of the question. Plot this RMSE with respect to the attributes.
rsme = []
x = []
for i in df5.mean(numeric_only=True).keys():
    result = 0
    x.append(i)
    for j in range(len(df5[i])):
        if pd.isna(df5[i][j]):
            result += (df4[i][j] - df3[i][j])**2
    result /= df5[i].isnull().sum()
    result = math.sqrt(result)
    rsme.append(result)
    print("The RSME for " + i + " is " + str(result))

print()


dict2 = {'Attributes': x, 'RSME': rsme}

temp_df2 = pd.DataFrame(dict2)

# temp_df2.plot.bar(x='Attributes', y='RSME', rot=0)

# plt.show()

# c) Outlier detection
# After replacing the missing values by interpolation method, find and list the outliers in the attributes “temperature” and “rain”. Outliers are the values that do not satisfy the condition (Q1 – (1.5 * IQR)) < x < (Q3 + (1.5 * IQR)), where x is the value of the attribute, IQR is the interquartile range, Q1 and Q3 are the first and third quartiles. Obtain the boxplot for these attributes.
Q1_1 = np.percentile(df4['temperature'], 25, interpolation='midpoint')

Q3_1 = np.percentile(df4['temperature'], 75, interpolation='midpoint')

IQR_1 = Q3_1 - Q1_1

upper = df4['temperature'] >= (Q3_1+1.5*IQR_1)
lower = df4['temperature'] <= (Q1_1-1.5*IQR_1)

res = list(np.where(upper)[0]) + list(np.where(lower)[0])
print("The outliers of temperature belong to the row numbers: ")
print(res)

Q1_2 = np.percentile(df4['rain'], 25, interpolation='midpoint')

Q3_2 = np.percentile(df4['rain'], 75, interpolation='midpoint')

IQR_2 = Q3_2 - Q1_2

upper = df4['rain'] >= (Q3_2+1.5*IQR_2)
lower = df4['rain'] <= (Q1_2-1.5*IQR_2)

res = list(np.where(upper)[0]) + list(np.where(lower)[0])
print("The outliers of rain belong to the row numbers: ")
print(res)


plt.boxplot(np.array(df4['temperature']))
plt.title("BoxPlot for Temperature")
plt.show()

plt.boxplot(np.array(df4['rain']))
plt.title("BoxPlot for Rain")
plt.show()

# Replace these outliers with the median of the attribute. Plot the boxplot again and observe the difference with that of the boxplot from the previous box in (i). Do you still get outliers? Why?
median = df4.median()['temperature']
df4['temperature'].loc[(df4['temperature'] >= (
    Q3_1+1.5*IQR_1)) | (df4['temperature'] <= (Q1_1-1.5*IQR_1))] = np.nan
df4['temperature'].fillna(median, inplace=True)

median = df4.median()['rain']
df4['rain'].loc[(df4['rain'] >= (Q3_2+1.5*IQR_2)) | (df4['rain'] <=
                                                     (Q1_2-1.5*IQR_2))] = np.nan
df4['rain'].fillna(median, inplace=True)

plt.boxplot(np.array(df4['temperature']))
plt.title("BoxPlot for Temperature after replacing Outliers")
plt.show()

plt.boxplot(np.array(df4['rain']))
plt.title("BoxPlot for Rain after replacing Outliers")
plt.show()
