# Importing various libraries and modules
import re
from cs50 import get_string
import sys

# Checking for proper numeric input by user
while True:
    number = get_string("Number: ")
    a = re.compile('[0-9]+')
    b = a.match(number)
    if b == None:
        continue
    m = b.group()
    if len(m) == len(number):
        # Validating the length of credit card
        if len(number) == 14 or len(number) < 13 or len(number) > 16:
            print("INVALID")
            sys.exit(1)
        else:
            break

# The checksum process starts here
# converting given string to integer list for calculations sake
num = []
for i in range(len(number)):
    num.append(int(number[i]))

# Calculating the sum of all alternate digits starting from second last digit, after multiplying them by 2
mult = []
for i in range(len(num) - 2, -1, -2):
    mult.append(str(num[i] * 2))

add = 0
for i in range(len(mult)):
    for j in range(len(mult[i])):
        add += int(mult[i][j])

# Calculating the sum of all alternate digits starting from last digit
add1 = 0
for i in range(len(num) - 1, -1, -2):
    add1 += int(num[i])

# Taking sum of add and add1 and converting it to string
s = str(add + add1)

# Checking whether last digit of above sum is 0 or not, and thus completing the validation of the given credit card number
if s[len(s) - 1] != str(0):
    print("INVALID")
    sys.exit(2)

# Checking for credit card company
if num[0] == 4:
    print("VISA")
    sys.exit(0)
elif num[0] == 3 and (num[1] in [4, 7]):
    print("AMEX")
    sys.exit(0)
elif num[0] == 5 and (num[1] in [1, 2, 3, 4, 5]):
    print("MASTERCARD")
    sys.exit(0)
# If the credit card number does not belong to any of the above companies, we declare it invalid
else:
    print("INVALID")
    sys.exit(3)
