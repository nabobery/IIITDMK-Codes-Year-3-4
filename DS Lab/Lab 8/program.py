# This program is done by CS20B1044 Avinash R Changrani
import pandas as pd

df = pd.read_csv("diabetes.csv")

diabetes = 0

for b in df['Outcome']:
    diabetes += b

p = diabetes/len(df)

print("The probability of diabetes in the given dataset is: " + str(p))

Flag = True

while Flag:
    print("Menu\na)Probability of Diabetes given age above 50\nb)Probability of Diabetes given age between 40 and 50\nc)Probability of Diabetes given age between 30 and 40\nd)Probability of Diabetes given aless than 30\ne)Probability of diabetes with a glucose level of more than 120 + blood pressure of more than 90 + skin thickness of more than 30 + insulin above 150 + BMI above 25\nf)Exit")
    choice = input("Please enter your choice: ")
    if choice == 'a':
        denominator = len(df.loc[df['Age'] > 50])
        numerator = len(df.loc[(df['Age'] > 50) & (df['Outcome'] == 1)])
        p = numerator/denominator
        print("The probability of diabetes is: " + str(p))
    elif choice == 'b':
        denominator = len(df.loc[(df['Age'] < 50) & (df['Age'] > 40)])
        numerator = len(df.loc[((df['Age'] < 50) & (df['Age'] > 40)) & (df['Outcome'] == 1)])
        p = numerator/denominator
        print("The probability of diabetes is: " + str(p))
    elif choice == 'c':
        denominator = len(df.loc[(df['Age'] < 40) & (df['Age'] > 30)])
        numerator = len(df.loc[((df['Age'] < 40) & (df['Age'] > 30)) & (df['Outcome'] == 1)])
        p = numerator/denominator
        print("The probability of diabetes is: " + str(p))
    elif choice == 'd':
        denominator = len(df.loc[df['Age'] < 30])
        numerator = len(df.loc[(df['Age'] < 30) & (df['Outcome'] == 1)])
        p = numerator/denominator
        print("The probability of diabetes is: " + str(p))
    elif choice == 'e':
        denominator = len(df.loc[(df['Glucose'] > 120) & (df['BloodPressure'] > 90) & (df['SkinThickness'] > 30) & (df['Insulin'] > 150) & (df['BMI'] > 25)])
        numerator = len(df.loc[((df['Glucose'] > 120) & (df['BloodPressure'] > 90) & (df['SkinThickness'] > 30) & (df['Insulin'] > 150) & (df['BMI'] > 25)) & (df['Outcome'] == 1)])
        p = numerator/denominator
        print("The probability of diabetes is: " + str(p))
    elif choice == 'f':
        Flag = False
        print("Exiting the program....")
    else:
        print("Wrong Choice! Please try again!")