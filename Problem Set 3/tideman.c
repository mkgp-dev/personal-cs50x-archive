bool vote(int rank, string name, int ranks[])
{
    // Using from my runoff.c
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // STATUS OK: did not correctly set ranks
            // Hotfix for being stupid
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

void record_preferences(int ranks[])
{
    // Two for loop function to record in preferences
    // First loop for candidate i
    // Second loop for candidate j
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void)
{
    // We will be using pair struct with pairs array
    // Two for loop functions to compare both candidate
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

void sort_pairs(void)
{
    // @mkgp-dev: This sorting function thing isn't my jam.
    // But "it works."
    // Decreasing Order
    for (int i = 0; i < pair_count - 1; i++)
    {
        int n = i;
        // Reverse
        for (int j = i + 1; j < pair_count; j++)
        {
            // Determining the so called strength of victory or shenanigans
            if ((preferences[pairs[j].winner][pairs[j].loser] -
                 preferences[pairs[j].loser][pairs[j].winner]) >
                (preferences[pairs[n].winner][pairs[n].loser] -
                 preferences[pairs[n].loser][pairs[n].winner]))
            {
                n = j;
            }
        }

        pair base = pairs[i];
        pairs[i] = pairs[n];
        pairs[n] = base;
    }
}

// @mkgp-dev: Cycle checking
bool verify_pairs(int a, int b)
{
    if (b == a)
    {
        return true;
    }

    // Recursive
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[b][i] && verify_pairs(a, i))
        {
            return true;
        }
    }

    return false;
}

void lock_pairs(void)
{
    // final pair and middle pair:
    // STATUS OK did not correctly lock all non-cyclical pairs
    // Make boolean to check all angles of pairs, my god.
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;

        locked[w][l] = true;

        // Hotfix, apply boolean
        if (verify_pairs(w, l))
        {
            locked[w][l] = false;
        }
    }
}

void print_winner(void)
{
    // Brain.exe is not working well
    // This is for the edges or so called adjacency matrix
    for (int i = 0; i < candidate_count; i++)
    {
        bool y = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                y = false;
                break;
            }
        }

        if (y)
        {
            printf("%s\n", candidates[i]);
        }
    }
}
