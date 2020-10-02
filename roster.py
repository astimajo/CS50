# TO DO: program that prints a list of students for a given house in alphabetical order.
import sys
import csv
import cs50

# Command line arguments check. exit as 1 if not correct.
if len(sys.argv) != 2:
    print("Usage: python roster.py Slytherin")
    sys.exit(1)

# loading the students db to sqlite3 and sqlite3 to python.
db = cs50.SQL("sqlite:///students.db")

# execute SQL query to SELECT roster from house list.
houses = db.execute("SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first", sys.argv[1])

for row in houses:
    # Take account lack of middle name for some students.
    if row["middle"] == None:
        print(row["first"] + " " + row["last"] + ", born " + str(row["birth"]))

    # If Data is complete.
    else:
        print(row["first"] + " " + row["middle"] + " " + row["last"] + ", born " + str(row["birth"]))

sys.exit(0)



    


