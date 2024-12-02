#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool digit(string n);
string caesar_algo(string p, int k);

int main(int argc, string argv[])
{
    if (argc != 2 || !digit(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert string to int
    int key = atoi(argv[1]);

    // Straight to the bucket
    string ptxt = get_string("plaintext: ");
    printf("ciphertext: %s\n", caesar_algo(ptxt, key));

    return 0;
}

string caesar_algo(string p, int k)
{
    // (p ^(i ^th) + k) % 26
    // hated this format but it works
    for (int i = 0; p[i] != '\0'; i++)
    {
        if (isalpha(p[i]))
        {
            char offset = isupper(p[i]) ? 'A' : 'a';
            p[i] = (p[i] - offset + k) % 26 + offset;
        }
    }

    return p;
}

bool digit(string k)
{
    // Checking if string pass is digit/s
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (!isdigit(k[i]))
        {
            return false;
        }
    }

    return true;
}
