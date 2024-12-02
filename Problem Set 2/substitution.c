#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool letter(string k);
string caesar_x_substitute(string p, string k);

int main(int argc, string argv[])
{
    if (argc != 2 || !letter(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Key as default string
    string key = argv[1];

    // Straight to the bucket again
    string ptxt = get_string("plaintext: ");
    printf("ciphertext: %s\n", caesar_x_substitute(ptxt, key));

    return 0;
}

string caesar_x_substitute(string p, string k)
{
    // small modification from caesar
    // instead of using a formula, we just substitute
    // reference from offset structure
    for (int i = 0; p[i] != '\0'; i++)
    {
        if (isalpha(p[i]))
        {
            char offset = isupper(p[i]) ? 'A' : 'a';
            int base = p[i] - offset;
            p[i] = isupper(p[i]) ? toupper(k[base]) : tolower(k[base]);
        }
    }

    return p;
}

bool letter(string k)
{
    // Duplication hotfix
    int alphabet[26] = {0};

    // Checking if string pass are letter/s
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (!isalpha(k[i]))
        {
            return false;
        }

        // Duplication hotfix
        int base = toupper(k[i]) - 'A';
        if (alphabet[base] > 0)
        {
            return false;
        }

        alphabet[base]++;
    }

    return true;
}
