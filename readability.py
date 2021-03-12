from cs50 import get_string

# Taking input from user
text = get_string("Text: ")
# Declaring variables to store corresponding count
letters = 0
words = 0
sentences = 0
for i in range(len(text)):
    # Checking for letters
    if text[i].isalpha():
        letters += 1
    # Checking for words
    elif text[i] == " ":
        words += 1
    # Checking for sentences
    elif text[i] in ['?', '!', '.']:
        sentences += 1

# Considering the last word of the sentence
words += 1

# Calculating number of letters and sentences per 100 words
L = (letters / words) * 100
S = (sentences / words) * 100

# Calculating level using Coleman-Liau formula
level = round(0.0588 * L - 0.296 * S - 15.8)

# Printing appropriate level
if level < 1:
    print("Before Grade 1")
elif level > 16:
    print("Grade 16+")
else:
    print(f"Grade {level}")
