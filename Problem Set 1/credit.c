#include <cs50.h>
#include <stdio.h>

void card_validation(long long credit_card);

int main(void)
{
    // Get user's query for credit card
    long long credit_card = get_long("Number: ");

    // Validate credit card
    card_validation(credit_card);
}

// Credits to @vinaayak03, just modified for its best approach
// Reference: https://github.com/vinaayak03/Credit-Card-Identifier-Using-C/
void card_validation(long long credit_card)
{
    int calc = 0, digit = 0, length = 0;
    long long card = credit_card, bin = 0, single_bin = 0;

    while (credit_card > 0)
    {
        int base = credit_card % 10;
        credit_card /= 10;
        digit++;

        // Note:
        // If "digit" is even, multiple by 2
        // If "digit" is greater than 9, adjusting by minus 9
        // If "digit" is odd, then we add directly to calc
        calc += (digit % 2 == 0) ? (base * 2 > 9 ? base * 2 - 9 : base * 2) : base;
    }

    if (calc % 10 == 0)
    {
        // Length and BIN
        while (card >= 100)
        {
            card /= 10;
            length++;
        }

        // Define each from while loop result
        bin = card;
        length += 2;

        // Single BIN for Visa
        single_bin = bin / 10;

        // printf("%i\n", length);
        // printf("%lli\n", bin);

        // Definition of Cards
        if (length == 15 && (bin == 34 || bin == 37))
        {
            printf("AMEX\n");
        }
        else if (length == 16 && (bin >= 51 && bin <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((length == 13 || length == 16) && single_bin == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
