#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int scrabble_point_mechanism(string letter);
string who_won(int a, int b);

int main(void)
{
    string player_one = get_string("Player 1: ");
    int result_one = scrabble_point_mechanism(player_one);

    string player_two = get_string("Player 2: ");
    int result_two = scrabble_point_mechanism(player_two);

    printf("%s\n", who_won(result_one, result_two));
}

int scrabble_point_mechanism(string letter)
{
    // 1 - A, E, I, L, N, O, R, S, T, U
    // 2 - D, G
    // 3 - B, C, M, P
    // 4 - F, H, V, W, Y
    // 5 - K
    // 8 - J, X
    // 10 - Q, Z

    char *alphabet[] = {"AEILNORSTU", "DG", "BCMP", "FHVWY", "K", "JX", "QZ"};
    int score[] = {1, 2, 3, 4, 5, 8, 10};
    int calc = 0;

    for (int i = 0, n = strlen(letter); i < n; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            // strchr functions to check if letter exist
            // if letter exist, score will decide what row in array to throw
            if (strchr(alphabet[j], toupper(letter[i])))
            {
                calc += score[j];
                break;
            }
        }
    }

    return calc;
}

string who_won(int a, int b)
{
    if (a > b)
    {
        return "Player 1 wins!";
    }
    else if (a < b)
    {
        return "Player 2 wins!";
    }
    else
    {
        return "Tie";
    }
}
