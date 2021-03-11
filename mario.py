# Importing the function from cs50 library
from cs50 import get_int

# Prompting the user for an input till they enter an integer
while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# Printing out the pyramid on the basis of input given by user
for i in range(height):
    print(" " * (height - (i + 1)) + "#" * (i + 1))
