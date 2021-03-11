# Importing function for ease of operation
from cs50 import get_int

# Prompting the user for input
while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# Printing the required pyramid of height "height"
for i in range(height):
    print(" " * (height - (i + 1)) + "#" * (i + 1) + "  " + "#" * (i + 1))
