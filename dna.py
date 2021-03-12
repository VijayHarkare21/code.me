# Importing required modules
import sys
import csv


def main():
    # Checking for valid input(and valid file type)
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    if len(sys.argv[1]) < 4 or len(sys.argv[2]) < 4:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(2)
    if sys.argv[1][len(sys.argv[1]) - 4:len(sys.argv[1])] != '.csv' or sys.argv[2][len(sys.argv[2]) - 4:len(sys.argv[2])] != '.txt':
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(3)

    # Opening and reading the database
    file = open(sys.argv[1])
    databases = csv.DictReader(file)

    # Opening and reading the DNA sequence
    file2 = open(sys.argv[2])
    sequences = file2.read()

    # Declaring variables to keep count of STRs for different patterns
    AGATC = 0
    TTTTTTCT = 0
    AATG = 0
    TCTAG = 0
    GATA = 0
    TATC = 0
    GAAA = 0
    TCTG = 0

    # Checking and matching process starts
    row_len = 0
    for row in databases:
        row_len = len(row)
        # First we check for which database is provided in the command-line argument
        if row_len == 4:
            # Calculating the maximum number of times the given pattern of nucleotides repeats itself consecutively
            AGATC = STR_Repeat(sequences, 'AGATC', 5)
            AATG = STR_Repeat(sequences, 'AATG', 4)
            TATC = STR_Repeat(sequences, 'TATC', 4)

            # Checking the database afor exact match
            if AGATC == int(row["AGATC"]) and AATG == int(row["AATG"]) and TATC == int(row["TATC"]):
                print(row["name"])
                file.close()
                file2.close()
                return 0
            # If exact match is not found, we move on to the next row
            else:
                continue
        elif row_len == 9:
            # Calculating the maximum number of times the given pattern of nucleotides repeats itself consecutively
            AGATC = STR_Repeat(sequences, 'AGATC', 5)
            AATG = STR_Repeat(sequences, 'AATG', 4)
            TATC = STR_Repeat(sequences, 'TATC', 4)
            TTTTTTCT = STR_Repeat(sequences, 'TTTTTTCT', 8)
            TCTAG = STR_Repeat(sequences, 'TCTAG', 5)
            GATA = STR_Repeat(sequences,'GATA', 4)
            GAAA = STR_Repeat(sequences, 'GAAA', 4)
            TCTG = STR_Repeat(sequences, 'TCTG', 4)

            # Checking the database afor exact match
            if AGATC == int(row["AGATC"]) and AATG == int(row["AATG"]) and TATC == int(row["TATC"]) and TTTTTTCT == int(row["TTTTTTCT"]) and TCTAG == int(row["TCTAG"]) and GATA == int(row["GATA"]) and GAAA == int(row["GAAA"]) and TCTG == int(row["TCTG"]):
                print(row["name"])
                file.close()
                file2.close()
                return 0
            # If exact match is not found, we move on to the next row
            else:
                continue

    # Closing the opened files after completion of process
    file.close()
    file2.close()
    # Even after iterating throughout the database, if no match is found, we print out that no match was found
    print("No match")
    return 0

# Defining the function for calculation of consecutive STRs
def STR_Repeat(dna, STR, Len):
    # Finding the first occurence of the given pattern of nucleotides
    index = dna.find(STR, 0)
    count = 0
    # We set the temporary count variable to 1 as at this stage we have already found 1 pattern match
    tmp = 1
    while True:
        # Finding next immediate occurence of the same pattern
        a = dna.find(STR, index + Len)
        # If the next pattern found is adjacent to the previous one, we increment the temporary count variable by 1
        if a == index + Len:
            tmp += 1
            index = a
            continue
        # If the next pattern is not adjacent, then we start building another cycle, till we find the maximum no. of times the pattern repeats itself consecutively
        else:
            if tmp > count:
                count = tmp
            index = dna.find(STR, a)
            tmp = 1
        # If no pattern match is found, we exit from the loop
        if a == -1:
            break
    # Return the max. no. of times the pattern repeats itself consecutively
    return count

main()
