#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

//Checks if the candidate voted does exist in CL argument through string comparison then returns result to the vote function.
int retrieve_index(string n)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], n) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    int candidate_index = retrieve_index(name);
    if (candidate_index != -1)
    {
        ranks[rank] = candidate_index;
        return true;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;  //record each voter's preferences
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences [i][j] > preferences [j][i])
            {
                pair p;
                p.winner = i;
                p.loser = j;
                pairs[pair_count++] = p; //set pair winner and loser using iteration for loops.
            }
        }
    }
    return;
}

int comparison(const void *elem1, const void *elem2)  //Comparison between candidates per loop iteration for quick sort algorithm.
{
    pair f = *((pair *) elem1); //experimented with some pointers to deal with issue. (test test test)
    pair s = *((pair *) elem2);

    int first_m = preferences[f.winner][f.loser] - preferences[f.loser][f.winner];
    int second_m = preferences[s.winner][s.loser] - preferences[s.loser][s.winner];
    return second_m - first_m;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    qsort(pairs, pair_count, sizeof(pair), comparison); //quicksort to arrange candidates in order of strength from strongest to weakest
    return;
}
//feed to main cycle detection function.
bool cycle_detect_assist(int index, bool detected[])
{
    if (detected[index])
    {
        return true;
    }
    detected[index] = true;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[index][i] && cycle_detect_assist(i, detected)) //use Recursion.
        {

            return true;
        }
    }
    return false;
}
//detect cycle and assist lock pair function feed return value with assistive function to pair lock mechanism.
bool cycle_detection(int first_index)
{
    bool detected[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        detected[i] = false;
    }
    return cycle_detect_assist(first_index, detected);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (cycle_detection(pairs[i].winner) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
            continue;
        }
    }
    return;
}
//locate source of the circular graph.
bool find_source(int index)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][index] == true)
        {
            return false;
        }
    }
    return true;
}
//get that source and feed to the print_winner function.
int retrieve_source()
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (find_source(i))
        {
            return i;
        }
    }
    return -1;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int index = retrieve_source();
    if (index != -1)
    {
        printf("%s\n", candidates[index]);
    }
    return;
}

