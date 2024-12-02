#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int readability_mechanism(string p);

int main(void)
{
    string paragraph = get_string("Text: ");
    int level = readability_mechanism(paragraph);

    // Rough definition
    if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (level == 2 || level <= 16)
    {
        printf("Grade %i\n", level);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int readability_mechanism(string p)
{
    // index = 0.0588 * L - 0.296 * S - 15.8
    // L is the average number of letters per 100 words in the text
    // S is the average number of sentences per 100 words in the text

    int lttr = 0, sntc = 0, wrd = 1;

    // Abusing strchr function to detect strings
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        // Detect only letters
        if (isalpha(p[i]))
        {
            lttr++;
        }

        // Detect only sentences
        if (strchr(".!?", p[i]))
        {
            sntc++;
        }

        // Detect words using spaces
        // wrd is default to 1, as we always start one word in sentences
        if (strchr(" ", p[i]))
        {
            wrd++;
        }
    }

    // Computation
    float letters = (lttr / (float) wrd) * 100;
    float sentences = (sntc / (float) wrd) * 100;
    double cl_index = 0.0588 * letters - 0.296 * sentences - 15.8;
    int glvl = round(cl_index);

    return glvl;
}
