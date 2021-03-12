import sys
import csv


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    if len(sys.argv[1]) < 4 or len(sys.argv[2]) < 4:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(2)
    if sys.argv[1][len(sys.argv[1]) - 4:len(sys.argv[1])] != '.csv' or sys.argv[2][len(sys.argv[2]) - 4:len(sys.argv[2])] != '.txt':
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(3)

    file = open(sys.argv[1])
    databases = csv.DictReader(file)

    file2 = open(sys.argv[2])
    sequences = file2.read()

    AGATC = 0
    TTTTTTCT = 0
    AATG = 0
    TCTAG = 0
    GATA = 0
    TATC = 0
    GAAA = 0
    TCTG = 0

    row_len = 0
    for row in databases:
        row_len = len(row)
        if row_len == 4:
            AGATC = STR_Repeat(sequences, 'AGATC', 5)
            AATG = STR_Repeat(sequences, 'AATG', 4)
            TATC = STR_Repeat(sequences, 'TATC', 4)

            if AGATC == int(row["AGATC"]) and AATG == int(row["AATG"]) and TATC == int(row["TATC"]):
                print(row["name"])
                file.close()
                file2.close()
                return 0
            else:
                continue

        elif row_len == 9:
            AGATC = STR_Repeat(sequences, 'AGATC', 5)
            AATG = STR_Repeat(sequences, 'AATG', 4)
            TATC = STR_Repeat(sequences, 'TATC', 4)
            TTTTTTCT = STR_Repeat(sequences, 'TTTTTTCT', 8)
            TCTAG = STR_Repeat(sequences, 'TCTAG', 5)
            GATA = STR_Repeat(sequences,'GATA', 4)
            GAAA = STR_Repeat(sequences, 'GAAA', 4)
            TCTG = STR_Repeat(sequences, 'TCTG', 4)

            if AGATC == int(row["AGATC"]) and AATG == int(row["AATG"]) and TATC == int(row["TATC"]) and TTTTTTCT == int(row["TTTTTTCT"]) and TCTAG == int(row["TCTAG"]) and GATA == int(row["GATA"]) and GAAA == int(row["GAAA"]) and TCTG == int(row["TCTG"]):
                print(row["name"])
                file.close()
                file2.close()
                return 0
            else:
                continue

    file.close()
    file2.close()
    print("No match")
    return 0


def STR_Repeat(dna, STR, Len):
    index = dna.find(STR, 0)
    count = 0
    tmp = 1
    while True:
        a = dna.find(STR, index + Len)
        if a == index + Len:
            tmp += 1
            index = a
            continue
        else:
            if tmp > count:
                count = tmp
            index = dna.find(STR, a)
            tmp = 1
        if a == -1:
            break
    return count

main()
