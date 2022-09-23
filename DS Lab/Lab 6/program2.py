# This program is done by CS20B1044 Avinash R Changrani
import pandas as pd

names = ["Ram", "Sam", "Prabhu"]

account_numbers = ["9893893891", "9893893898", "9893893871"]

account_types = ["SB", "CA", "SB"]

aadhar_numbers = ["959389389173", "959389389179", "959389389159"]

bal = ["8989839", "7690990", "989330"]

dict1 = {'Name': names, 'Account Number': account_numbers,
         'Account Type': account_types, 'Aadhar_No': aadhar_numbers, 'Balance': bal}

# initialize df using dictionary
df1 = pd.DataFrame(dict1)

# df to csv
df1.to_csv("SBIAccountHolder.csv")

contact_no = ["9840787333", "9840787343", "9840787353"]

dob = ["12-2-1990", "12-2-2000", "12-2-2010"]

addresses = ["No 23 Kandigai, Chennai 127",
             "No 73 Melakottaiyu, Chennai 127", "No 43 Anna Nagar, Chennai 102"]

dict2 = {'Name': names, 'Aadhar Number': aadhar_numbers,
         'Contact_No': contact_no, "DOB": dob, "Address": addresses}

# initialize df using dictionary
df2 = pd.DataFrame(dict2)

# df to csv
df2.to_csv("Aadhar_DB.csv")

# merge based on key = Name
result = pd.merge(df1, df2, on="Name")

result.to_csv("result.csv")

print(result)
