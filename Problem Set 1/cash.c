#include <cs50.h>
#include <stdio.h>

void cents_calculation(int n);

int main(void)
{
    // Variables
    int cents;

    // Using do while loop to grab user's query
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Calculate cents for its proper change
    cents_calculation(cents);
}

void cents_calculation(int n)
{
    // Default variable
    int calc = 0;

    // Quarter
    // Note for its computation:
    // Let's say we put 70 in n
    // Structure of "calc += n / 25" will be "0 + (70 / 25)", as usual, PEMDAS rule will be applied
    // Normally in calculator, it will result as "2.8" but this is an integer, it will only throw
    // "2". calc now is carrying "2". n needs to change to be passed in dime, nickel, and penny. So
    // we will use modulus, so "n %= 25" will be 70 mod 25, resulting "20". n now is carrying "20".
    calc += n / 25;
    n %= 25;
    // printf("%i, %i\n", calc, n);

    // Dime
    // Extracting the explanation above
    // "calc += n / 10" will be "2 + (20 / 10)" resulting "4"
    // "n %= 10" will be "20 mod 10" resulting "0"
    calc += n / 10;
    n %= 10;
    // printf("%i, %i\n", calc, n);

    // Nickel
    // "calc += n / 5" will be "4 + (0 / 5)" resulting "4"
    // "n %= 5" will be "0 mod 10" resulting "0"
    calc += n / 5;
    n %= 5;
    // printf("%i, %i\n", calc, n);

    // Penny
    // "calc += n / 1" will be "4 + (0 / 1)" resulting "4"
    // Final result => "4"
    calc += n / 1;
    printf("%i\n", calc);
}
