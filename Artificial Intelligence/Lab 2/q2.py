# Two Jug Problem
# There is a large bucket B full of water and Two (02) jugs, J1 of volume 3 litre and J2 of volume 5 litre. You are allowed to fill up any empty jug from the bucket, pour all water back to the bucket from a jug or pour from one jug to another (either the jug from which you are pouring the water needs to completely empty after the operation or the jug to which you are pouring the water needs to be completely filled after the operation). The goal is to have jug J1 with exactly one (01) litre of water.

# This program is done by CS20B1044 Avinash R Changrani

import math


def pour(toCap, fromCap, constraint):
    # Initialize current amount of water in source and destination jugs
    fromJ = fromCap
    toJ  = 0
    print(f"Filling Jug J2 with {fromCap} litres of water : <0,0> -> <{toJ},{fromJ}>")

    while (toJ is not constraint):   
        # Find the maximum amount that can be poured
        temp = min(fromJ, toCap-toJ) 
        # Pour 'temp' liter from 'fromJ' to 'toJ'
        print(f"Pouring {temp} litres of water from Jug J2 to Jug J1 <{toJ},{fromJ}> -> <{toJ+temp},{fromJ-temp}>")
        toJ = toJ + temp
        fromJ = fromJ - temp

        # if we satisfy the constraint break
        if (toJ == constraint):
            break
 
        # If first jug becomes empty, fill it
        if fromJ == 0:
            print(f"Filling Jug J2 with {fromCap} litres of water : <{toJ},{fromJ}> -> <{toJ},{fromCap}>")
            fromJ = fromCap
            #step =  step + 1
 
        # If second jug becomes full, empty it
        if toJ == toCap:
            print(f"Pouring {toCap} litres of water of Jug J1 back to bucket : <{toJ},{fromJ}> -> <0,{fromJ}>")
            toJ = 0
            #step =  step + 1
             
    #return step


def main():
    j1, j2 = 3, 5
    constraint1 = 1
    pour(j1, j2, constraint1)



if __name__ == "__main__":
    main()
