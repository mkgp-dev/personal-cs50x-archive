from cs50 import get_float


def main():
    # Using my mario-less.py
    while True:
        c = get_float("Change: ")
        if c >= 0:
            break

    # If c complied, call function
    change = cents_calculation(c)
    print(change)


def cents_calculation(n):
    calc = 0

    # Note: you should assume that the user will input
    # their change in dollars (e.g., 0.50 dollars instead of 50 cents)
    n = round(n * 100)

    # Dividing a float number uses "//" instead of "/"
    # Reference: https://www.w3schools.com/python/python_operators.asp
    # Quarter
    calc += n // 25
    n %= 25

    # Dime
    calc += n // 10
    n %= 10

    # Nickel
    calc += n // 5
    n %= 5

    # Penny
    calc += n // 1

    # Return calculation
    return calc


main()
