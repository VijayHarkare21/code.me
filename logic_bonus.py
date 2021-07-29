n = int(input())
word_count = {}
count = 0

# Following block populates the above defined dictionary
for i in range(n):
    word = str(input())
    if word in word_count:
        word_count[word] += 1
    else:
        word_count[word] = 1
        count += 1

# This prints the total number of distinct entries
print(count)

# This prints number of occurence of each entry
for key in word_count:
    print(f"{word_count[key]}", end = " ")

print()

# Now the bonus part

# Arrange the dictionary of words in descending order
values = dict(sorted(word_count.items(), key = lambda item: item[1], reverse = True))
# Create a list of all values
occur_v = list(values.values())
# Create a list of all keys
occur_k = list(values.keys())
print("Words in descending order of occurence are:", occur_k)
# Create temporary variables to store maximum and minimum values
tmp_v_max = max(occur_v)
tmp_v_min = min(occur_v)
maximum = []
minimum = []
# Populate the above lists with respective elements
for key in values:
    if values[key] == tmp_v_max:
        maximum.append(key)
    elif values[key] == tmp_v_min:
        minimum.append(key)

print(f"Most repeated word/s is/are: {maximum}\nLeast repeated word/s is/are: {minimum}")