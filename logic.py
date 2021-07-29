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