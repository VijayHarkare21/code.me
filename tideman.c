#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int voters = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                preferences[ranks[i]][ranks[j]] = 0;
            }
            if (j > i)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int k = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (j > i)
            {
                if (preferences[i][j] != preferences[j][i])
                {
                    if (preferences[i][j] > preferences[j][i])
                    {
                        pairs[k].winner = i;
                        pairs[k].loser = j;
                    }
                    else if (preferences[i][j] < preferences[j][i])
                    {
                        pairs[k].winner = j;
                        pairs[k].loser = i;
                    }
                    pair_count++;
                    k++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int max = 0;
    int k = 0;
    int old_winner = 0;
    int old_loser = 0;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (j >= i)
            {
                // Checking for greates element happens here
                if (preferences[pairs[j].winner][pairs[j].loser] >= max)
                {
                    max = preferences[pairs[j].winner][pairs[j].loser];
                    k = j;
                }
            }
        }
        // Swapping happens here
        old_winner = pairs[i].winner;
        old_loser = pairs[i].loser;
        pairs[i].winner = pairs[k].winner;
        pairs[i].loser = pairs[k].loser;
        pairs[k].winner = old_winner;
        pairs[k].loser = old_loser;
        max = 0;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    bool cycle(int winner, int loser, int winner3);
    for (int i = 0; i < pair_count; i++)
    {
        // This step checks for cycles
        if (!cycle(pairs[i].winner, pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int num_falses = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (!locked[i][j])
            {
                num_falses++;
            }
        }
        if (num_falses == candidate_count)
        {
            printf("%s\n", candidates[j]);
        }
        // This step ensures that each candidate is properly searched for edges
        num_falses = 0;
    }
    return;
}

// Determine whether a cycle is being formed during locking of pairs
// The three variables ensure that variables are not confused, and proper cycle is identified
bool cycle(int winner, int loser, int winner3)
{
    // The base case terminates the cycle
    if (loser == winner3)
    {
        return true;
    }
    // Here actual recursion occurs
    for (int i = 0; i < candidate_count; i++)
    {
        // These steps ensure that bigger cycles are also identified
        if (locked[loser][i])
        {
            if (cycle(loser, i, winner3))
            {
                return true;
            }
        }
    }
    return false;
}
