/**
 * Just for fun (Time improvements)
 * LOGS
 * [text] - [@mkgp-dev] - [cs50-staff]
 * holmes.txt - 1.16 - 1.16
 * shakespeare.txt - 1.00 - 1.02
 * lalaland.txt - 0.06 - 0.07
 **/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Increased to 500000 buckets to defeat cs50-staff
const unsigned int N = 500000;

// Hash table
node *table[N];

// Global variable for storing the length of dictionary
int ldict = 0;

bool check(const char *word)
{
    // @mkgp-dev: Check function
    // Grab N value of hash
    int n = hash(word);

    // Referencing node for loop from Mr. Malan, thank you
    for (node *ptr = table[n]; ptr != NULL; ptr = ptr->next)
    {
        // Note: To compare two strings case-insensitively
        // you may find strcasecmp (declared in strings.h) useful
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
    }

    return false;
}

unsigned int hash(const char *word)
{
    // return toupper(word[0]) - 'A';
    // @mkgp-dev Improve hash function
    unsigned int hash = 0;
    unsigned int prime = 37; // 31, 37, 41

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = (hash * prime) ^ toupper(word[i]);
    }

    return hash % N;
}

bool load(const char *dictionary)
{
    // @mkgp-dev: Load function
    // Open a file
    FILE *dict = fopen(dictionary, "r");

    // Check if file exist
    if (dict == NULL)
    {
        return false;
    }

    // Read the file and add to hash table
    char strmtxt[LENGTH + 1];
    while (fscanf(dict, "%s", strmtxt) != EOF)
    {
        // Create temporary allocation
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            // Avoid leak
            fclose(dict);
            return false;
        }

        // Set word to temporary allocation
        // int l = strlen(strmtxt);
        // tmp->word[l] = (char) *strmtxt;
        strcpy(tmp->word, strmtxt);

        // Gain N for hash
        int n = hash(strmtxt);

        // Add text to table[x]
        tmp->next = table[n];
        table[n] = tmp;

        ldict++;
    }

    // Avoid leaks
    fclose(dict);

    return true;
}

unsigned int size(void)
{
    // @mkgp-dev: Simple size function
    // Since we already count how many in loops at load function
    // This should store the length of dictionary
    // else if it doesn't, just return to 0
    if (ldict > 0)
    {
        return ldict;
    }
    else
    {
        return 0;
    }
}

bool unload(void)
{
    // @mkgp-dev: Unload function
    // Create a simple for loop
    for (int i = 0; i < N; i++)
    {
        // Swap method but this time, it needs to unload
        node *mem = table[i];
        while (mem != NULL)
        {
            node *memtmp = mem;
            mem = mem->next;

            // Be free!
            free(memtmp);
        }

        // Clear all
        table[i] = NULL;
    }

    return true;
}
