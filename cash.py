# Importing function to make life easy
from cs50 import get_float

# Asking input from user until user cooperates
while True:
    change = round(100 * get_float("Change owed: "))
    if change >= 0:
        break

# Declareing variable to track coin count
coins = 0
while change != 0:
    # Handling change of 25
    while change >= 25:
        coins += 1
        change -= 25
    # Handling change of 10
    while change >= 10:
        coins += 1
        change -= 10
    # Handling change of 5
    while change >= 5:
        coins += 1
        change -= 5
    # Handling change of 1
    while change >= 1:
        coins += 1
        change -= 1

# Printing number of coins
print(f"{coins}")
