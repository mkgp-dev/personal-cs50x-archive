#include <cs50.h>
#include <stdio.h>

// Define function of generating bricks
void generate_bricks(int n);

int main(void)
{
    // Variable h for height
    int h;

    // Using do while loop to get user's requested height
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1);

    generate_bricks(h);
}

void generate_bricks(int n)
{
    // Test print
    // printf("prompt: %i\n", n);

    // Using for loop to generate bricks
    for (int i = 0; i < n; i++)
    {
        // Indent bricks to right
        // Note: If you put 8, "j < n - i - 1" will be "0 < 8 - 0 - 1" => 7 spaces
        // As it loops, for example in second sequence "1 < 8 - 1 - 1" => 6 spaces and so on
        for (int j = 0; j < n - i - 1; j++)
        {
            // printf("%i", n - i - 1);
            printf(" ");
        }

        // Print bricks
        // Note: If you put 8, "j <= i" will be 0 <= 0, up until it reaches 8
        // Remember 0 is always "1" or first in programming
        for (int j = 0; j <= i; j++)
        {
            // printf("%i", i);
            printf("#");
        }

        // printf("%i", i);
        printf("\n");
    }
}
