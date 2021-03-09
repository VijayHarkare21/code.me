// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000000;

// Hash table
node *table[N];

// Keeps track of no. of words in the dictionary
unsigned int word_num = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // For string word in lowercase
    char tmp_word[LENGTH + 1];
    for (int i = 0; i < strlen(word) + 1; i++)
    {
        // Convert the uppercase to lowercase, else preserve lowercase
        tmp_word[i] = tolower(word[i]);
    }
    // Comparing the word with the words in the linked list at hashed index
    for (node *cursor = table[hash(tmp_word)]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(tmp_word, cursor->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
// This hash function is a rolling hash function
// This hash function was found on the internet but there was no author mentioned
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0 ; word[i] != '\0'; i++)
    {
        hash = 31 * hash + word[i];
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the file
    FILE *file = fopen(dictionary, "r");
    // Check for any discrepancy
    if (file == NULL)
    {
        return false;
    }
    // For temporarily storing words
    char tmpword[LENGTH + 1];
    while (fscanf(file, "%s", tmpword) != EOF)
    {
        // Allocating memory dynamically
        node *n = malloc(sizeof(node));
        // For NULL condition
        if (n == NULL)
        {
            return false;
        }
        // Initially setting for avoiding any discrepancy
        n->next = NULL;
        // Copying the word for further use
        strcpy(n->word, tmpword);
        // Insert word in the respective linked list
        n->next = table[hash(n->word)];
        table[hash(n->word)] = n;
        // To keep word count
        word_num++;
    }
    // Closing the file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_num;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        // Iterating through th linked lists and freeing them one by one
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
