#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    // Comparing the scores and printing the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Assigning variable for storing score
    int score = 0;
    // TODO: Compute and return score for string
    // Following loop iterates through th given word
    for (int i = 0; i < strlen(word); i++)
    {
        // The following condition ensures that only alphabets are scored
        if (isalpha(word[i]))
        {
            // The following condition ensures case-insensitivity
            if (isupper(word[i]))
            {
                score = score + POINTS[word[i] - 65];
            }
            else if (islower(word[i]))
            {
                score = score + POINTS[word[i] - 97];
            }
        }
        else
        {
            score = score + 0;
        }
    }
    return score;
}