# Write a program in prolog/pytholog to implement following simple facts and Queries
# Shyam likes mango
# Seema is a girl
# Bill likes Cindy
# Rose is red
# John owns gold 

# Clauses
# likes(shyam, mango)
# girl(seema)
# red(rose)
# likes(bill, cindy)
# owns(john ,gold) 

# Goal
# ?- likes (shyam, What) 
#     What = mango

# This program is done by CS20B1044 Avinash R Changrani

import pytholog as pl

kb = pl.KnowledgeBase("facts")

kb(["likes(shyam, mango)", "girl(seema)","red(rose)", "likes(bill, cindy)","owns(john ,gold)"])

what = "mango"

print("?- likes (shyam, What)")
print(kb.query(pl.Expr("likes(shyam, " + str(what) + ")")))