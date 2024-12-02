bool vote(string name)
{
    // Using for loop
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Add one vote to candidate and return true
            candidates[i].votes += 1;
            return true;
        }
    }

    return false;
}

// @mkgp-dev: Making loop to grab higher vote count
int loop_vote(void)
{
    int v = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > v)
        {
            v = candidates[i].votes;
        }
    }

    return v;
}

void print_winner(void)
{
    // Basic loop to print out who has the higher vote count
    int overall_vote = loop_vote();

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == overall_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
