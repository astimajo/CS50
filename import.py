# TO DO: program that imports data from a CSV spreadsheet.
import sys
import csv
import cs50

# Command line arguments check. exit as 1 if not correct.
if len(sys.argv) != 2:
    print("Usage: python import.py characters.csv")
    sys.exit(1)

# loading the students db to sqlite3 and sqlite3 to python.
db = cs50.SQL("sqlite:///students.db")

# Open csv file as file.
with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)
    
    # extract names using csv reader and add spacing
    for row in reader:
        n = row["name"]
        names = n.split()

        # Taking account of lacking middle name
        if len(names) == 2:
            first_name = names[0]
            last_name = names[1]
            
            # SQL query to add data to students.db (based on .schema)
            db.execute('INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)', first_name, None, last_name, row["house"], row["birth"]) # No need for special conditions for house and birth.

        # If the Data is complete (including the middle name)
        elif len(names) == 3:
            first_name = names[0]
            middle_name = names[1]
            last_name = names[2]

            # SQL query to add data to students.db
            db.execute('INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)', first_name, middle_name, last_name, row["house"], row["birth"])

    sys.exit(0)
        
    
