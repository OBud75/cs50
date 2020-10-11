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
        //if input match with a candidate
        if (strcmp(name, candidates[i].name) == 0)
        {
            //add 1 to his votes and return true
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}


// Print the winner (or winners) of the election
void print_winner(void)
{
    //set variable to know the biggest numbers of votes for 1 candidate
    int nb_of_votes_to_win = 0;
    //iterate for each candidate
    for (int i = 0; i <= candidate_count; i++)
    {
        //if candidate in the loop have more votes than previous ones
        if (candidates[i].votes > nb_of_votes_to_win)
        {
            //re asset the variable
            nb_of_votes_to_win = candidates[i].votes;
        }
    }
    //iterate for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //if the candidate reach the nb of votes to win, print his name
        if (candidates[i].votes == nb_of_votes_to_win)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}