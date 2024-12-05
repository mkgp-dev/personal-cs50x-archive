from cs50 import get_string


def main():
    input = get_string("Text: ")
    call_read = readability(input)

    print(call_read)


def readability(string):
    # Converting my readability.c to Python
    ch = [".", "?", "!"]
    l, s = 0, 0
    wrd = len(string.split())

    # Make a for loop
    for char in string:
        if char.isalpha():
            l += 1

        if char in ch:
            s += 1

    # Coleman-Liau Formula
    ltr = (l / wrd) * 100
    stnc = (s / wrd) * 100
    glvl = round(0.0588 * ltr - 0.296 * stnc - 15.8)

    # Definition
    if glvl < 1:
        return "Before Grade 1"
    elif glvl == 2 or glvl <= 16:
        return f"Grade {glvl}"
    else:
        return "Grade 16+"


main()
