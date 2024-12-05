from cs50 import get_int


def main():
    n = get_int("Number: ")
    v = validation(n)
    print(v)


def validation(card):
    # Converting my credit.c to Python
    calc, digit = 0, 0

    # Temporary store card to modify in computation
    # for valid Luhn-algorithm
    tmp = card

    while tmp > 0:
        base = tmp % 10
        tmp //= 10
        digit += 1

        calc += (base * 2 - 9 if base * 2 > 9 else base * 2) if (digit % 2 == 0) else base

    if calc % 10 == 0:
        # Get the length of the card
        l = len(str(card))

        # Get the first/two string of card
        # Reference: https://docs.python.org/3/library/re.html
        dbl = int(str(card)[:2])
        sngl = int(str(card)[:1])

        # Credit card definition
        if l == 15 and (dbl == 34 or dbl == 37):
            return "AMEX"
        elif l == 16 and (dbl >= 51 and dbl <= 55):
            return "MASTERCARD"
        elif (l == 13 or l == 16) and sngl == 4:
            return "VISA"
        else:
            return "INVALID"

    else:
        return "INVALID"


main()
