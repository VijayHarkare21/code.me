#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int main(void)
{
    // Prompt the user for text
    string s = get_string("Text: ");
    int letter = 0;
    int word = 0;
    int sentence = 0;
    // Calculate number of letters, words and sentences
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))
        {
            letter++;
        }
        else if (isspace(s[i]))
        {
            word++;
        }
        else if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            sentence++;
        }
    }
    word++;
    // Calculate average no. of letters per 100 words and average number of sentences per 100 words
    float L;
    L = ((float) letter / word) * 100;
    float S;
    S = ((float) sentence / word) * 100;
    // Use the Coleman-Liau formula to calculate grade of the text
    float index;
    index = 0.0588 * L - 0.296 * S - 15.8;
    int X = round(index);
    // Printing the appropriate grade
    if (X < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (X >= 1 && X < 16)
    {
        printf("Grade %i\n", X);
    }
    else if (X >= 16)
    {
        printf("Grade 16+\n");
    }
}
