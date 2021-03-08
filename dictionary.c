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
const unsigned int N = 1e9 + 9;

// Hash table
node *table[N];

// Keeps track of no. of words in the dictionary
unsigned int word_num = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char tmp_word[LENGTH + 1];
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
        {
            if (islower(word[i]))
            {
                tmp_word[i] = word[i];
            }
            else if (isupper(word[i]))
            {
                tmp_word[i] = tolower(word[i]);
            }
        }
        else
        {
            tmp_word[i] = word[i];
        }
    }
    tmp_word[strlen(word)] = '\0';
    unsigned int hash_v = hash(tmp_word);
    for (node *cursor = table[hash_v]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(tmp_word, cursor->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
// This hash function is a rolling hash function taken from geeksforgeeks.org
// Original article contributed by 7maestro and improved by SHIVAMSINGH67, amit143katiyar, 29AjayKumar
// This hash function is a modified version by me
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    int p = 1;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
        {
            hash_value += (word[i] - 'a' + 1) * p;
            p *= 31;
        }
        else
        {
            continue;
        }
    }
    return (hash_value % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if(file == NULL)
    {
        return false;
    }
    char tmpword[LENGTH + 1];
    while (fscanf(file, "%s", tmpword) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        n->next = NULL;
        strcpy(n->word, tmpword);
        if (table[hash(n->word)] == NULL)
        {
            table[hash(n->word)] = n;
        }
        else if (table[hash(n->word)] != NULL)
        {
            n->next = table[hash(n->word)];
            table[hash(n->word)] = n;
        }
        free(n);
        word_num++;
    }
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
        while(cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return false;
}
