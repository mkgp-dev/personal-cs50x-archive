bool vote(int voter, int rank, string name)
{
    // Using from my plurality.c
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            // candidates[i].votes += 1;
            return true;
        }
    }

    return false;
}

void tabulate(void)
{
    // Generate two loops
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Grab index set from bool vote
            int index = preferences[i][j];

            // Check if candidate is eliminated
            if (!candidates[index].eliminated)
            {
                candidates[index].votes++;
                break;
            }
        }
    }
}

bool print_winner(void)
{
    // "If any candidate has more than half of the vote"
    int calc_v = voter_count / 2;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > calc_v)
        {
            printf("%s\n", candidates[i].name);

            return true;
        }
    }

    return false;
}

int find_min(void)
{
    // Assuming voters with defined MAX_VOTERS
    int v = MAX_VOTERS;

    for (int i = 0; i < candidate_count; i++)
    {
        // @mkgp-dev: Grab from plurality, instead greater than
        // We will use less than to grab minimum votes
        if (candidates[i].votes < v && !candidates[i].eliminated)
        {
            v = candidates[i].votes;
        }
    }

    return v;
}

bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if a candidate ties by having the same variable with min
        if (candidates[i].votes != min && !candidates[i].eliminated)
        {
            return false;
        }
    }

    return true;
}

void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If its the same with min variable, eliminate.
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
