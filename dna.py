import sys
import csv
import pandas as pd
import re

# Command-line Argument for name of CSV file containing STR and text file containing DNA sequence.
if len(sys.argv) != 3:
    print("Usage: python dna.py databases/small.csv sequences/1.txt")
    sys.exit(1)

# open the TEXT file and read its contents into memory(list). (this style is to avoid file close)
with open(sys.argv[2]) as dna_text:
    dna_reader_function = csv.reader(dna_text)
    for row in dna_reader_function:
        dna_list = row

# store dna sequence inside a string
DNA = dna_list[0]  # This is to remove brackets that are produced in read
# print(dna) # - debugger to check string

# key-value pair dictionary for STRs (like node)
STR_dictionary = {}

# open the CSV file and read its contents into memory(list). (this style is to avoid file close)
with open(sys.argv[1]) as subjects_csv:
    subjects_function = csv.reader(subjects_csv)
    for row in subjects_function:
        dna_seq_list = row
        # print(row[0]) - debugger to track index
        dna_seq_list.pop(0)
        break

# make keys for dictionary wherein STR patterns are keys
for unit in dna_seq_list:
    STR_dictionary[unit] = 1

    # print(STR_dictionary[unit]) - debugger

# iterate through DNA sequence.

for key in STR_dictionary:
    length = len(key)

    final_count = 0
    count = 0

    # count = count - 1 to avoid duplicates!
    for i in range(len(DNA)):
        while count > 0:
            count = count - 1
            continue
        # counter function

        # ERROR lies in the length computation.
        if DNA[i: i + length] == key:
            # if iteration finds same STR during movement count.
            while DNA[i - length: i] == DNA[i: i + length]:
                # DNA string [i + n or i - n character up to (:) i + n or i - n character]
                count = count + 1
                i = i + length
            if count > final_count:
                final_count = count

    # dna sequence is stored in Dictionary with matching key
    STR_dictionary[key] = STR_dictionary[key] + final_count
    # print(STR_dictionary[key])
    # print(count)
    # print(final_count)

# Open database then scan through database of subject names to compare.

with open(sys.argv[1], newline='') as subjects_file:
    subjects = csv.DictReader(subjects_file)

    for subject in subjects:

        # iterate to find STR pattern matches
        dna_matches = 0
        for DNA in STR_dictionary:
            if STR_dictionary[DNA] == int(subject[DNA]):
                dna_matches = dna_matches + 1
            # if found
        if dna_matches == len(STR_dictionary):
            print(subject['name'])
            # return 0
            sys.exit(0)
    # If no matches are found out No Match to the screen. return (1)
    print("No Match")
    sys.exit(1)
