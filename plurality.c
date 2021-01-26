#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // This step calculates the maximum no. of votes any candidate got
    int max_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // The following steps ensure that all types of combinations get included
            if (candidate_count != 1)
            {
                if (i != j)
                {
                    if (candidates[i].votes == 0 || candidates[j].votes == 0)
                    {
                        if (candidates[i].votes > candidates[j].votes && candidates[i].votes > max_count)
                        {
                            max_count = candidates[i].votes;
                        }
                    }
                    else if (candidates[i].votes > 0 && candidates[j].votes > 0)
                    {
                        if (candidates[i].votes >= candidates[j].votes && candidates[i].votes > max_count)
                        {
                            max_count = candidates[i].votes;
                        }
                    }
                }
            }
            // This step ensures that the algorithm works even when only one name is provided as command-line argument
            else
            {
                if (candidates[i].votes > 0)
                {
                    max_count = candidates[i].votes;
                }
            }
        }
    }
    // This step prints out the names of all the candidates who got maximum votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (max_count == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
