# This program is done by CS20B1044 Avinash R Changrani
import pandas as pd

names = ["Ram", "Sam", "Prabhu"]

account_numbers = ["9893893891", "9893893898", "9893893871"]

account_types = ["SB", "CA", "SB"]

aadhar_numbers = ["959389389173", "959389389179", "959389389159"]

bal = ["8989839", "7690990", "989330"]

dict = {'Name': names, 'Account Number': account_numbers,
        'Account Type': account_types, 'Aadhar_No': aadhar_numbers, 'Balance': bal}

df = pd.DataFrame(dict)

df.to_csv("SBIAccountHolder.csv")

flag = True

while flag:
    print("Menu\n1)Append Record \t 2)Delete Record \t 3)Credit \t 4)Debit \t 5)Print Account Details \t 6)Exit")
    choice = int(input("Enter your choice: "))
    if choice == 1:
        name = input("Please enter the Name: ")
        account_no = input("Please enter the Account Number : ")
        try:
            int(account_no)
        except ValueError:
            print("Wrong Value! Please try again!")
            continue
        account_type = input("Please enter the Account Type: ")
        aadhar_no = input("Please enter the Aadhar Number: ")
        try:
            int(aadhar_no)
        except ValueError:
            print("Wrong Value! Please try again!")
            continue
        account_bal = input("Please enter the Balance: ")
        try:
            int(account_bal)
        except ValueError:
            print("Wrong Value! Please try again!")
            continue
        temp_dict = {'Name': name, 'Account Number': account_no,
                     'Account Type': account_type, 'Aadhar_No': aadhar_no, 'Balance': account_bal}
        ind = len(df.index)
        df.loc[ind] = temp_dict
        df.to_csv("SBIAccountHolder.csv")
    elif choice == 2:
        account_no = input("Please enter the Account Number : ")
        try:
            int(account_no)
        except ValueError:
            print("Wrong Value! Please try again!")
            continue
        ind = -1
        for i in range(len(df)):
            if df['Account Number'][i] == account_no:
                ind = i
                break
        if ind == -1:
            print("Record with Account Number : " + account_no +
                  " Doesn't exist. Please try again!")
        else:
            df = df.drop(ind)
            df.reset_index(inplace=True, drop=True)
        # data_with_index = df.set_index("Account Number")
        # data_with_index.head()
        # data_with_index = data_with_index.drop(account_no)
        df.to_csv("SBIAccountHolder.csv")
    elif choice == 3:
        account_no = input(
            "Please enter the Account Number you want to credit to: ")
        try:
            int(account_no)
        except ValueError:
            print("Wrong Value! Please try again!")
            continue
        credit_amount = input("Please enter the amount to be credited: ")
        try:
            int(credit_amount)
        except ValueError:
            print("Wrong Value! Please try again!")
            continue
        ind = -1
        for i in range(len(df)):
            if df['Account Number'][i] == account_no:
                ind = i
                break
        if ind == -1:
            print("Record with Account Number : " + account_no +
                  " Doesn't exist. Please try again!")
        else:
            temp = int(df.loc[ind]["Balance"])
            temp += int(credit_amount)
            df.loc[ind]["Balance"] = temp
            df.to_csv("SBIAccountHolder.csv")
    elif choice == 4:
        account_no = input(
            "Please enter the Account Number you want to debit to: ")
        try:
            int(account_no)
        except ValueError:
            print("Wrong Value! Please try again!")
            continue
        debit_amount = input("Please enter the amount to be debited: ")
        try:
            int(debit_amount)
        except ValueError:
            print("Wrong Value! Please try again!")
            continue
        ind = -1
        for i in range(len(df)):
            if df['Account Number'][i] == account_no:
                ind = i
                break
        if ind == -1:
            print("Record with Account Number : " + account_no +
                  " Doesn't exist. Please try again!")
        else:
            if df.loc[ind]["Account Type"] == "SB":
                temp = int(df.loc[ind]["Balance"])
                if (temp - int(debit_amount)) < 0:
                    print(
                        "There's an error. Account Balance can't be negative. Please try again!")
                else:
                    temp -= int(debit_amount)
                    df.loc[ind]["Balance"] = temp
                    df.to_csv("SBIAccountHolder.csv")
            else:
                temp = df.loc[ind]["Balance"]
                temp -= int(debit_amount)
                df.loc[ind]["Balance"] = temp
                df.to_csv("SBIAccountHolder.csv")
    elif choice == 5:
        account_no = input("Please enter the Account Number you want print: ")
        try:
            int(account_no)
        except ValueError:
            print("Wrong Value! Please try again!")
            continue
        ind = -1
        for i in range(len(df)):
            if df['Account Number'][i] == account_no:
                ind = i
                break
        if ind == -1:
            print("Record with Account Number : " + account_no +
                  " Doesn't exist. Please try again!")
        else:
            print(df.loc[ind])
    elif choice == 6:
        flag = False
        print("Exting the program.....")
    else:
        print("Wrong Choice! Please try again!")
