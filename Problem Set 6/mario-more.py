from cs50 import get_int


def main():
    # Using my mario-less.py
    while True:
        h = get_int("Height: ")
        if h >= 1 and h <= 8:
            break

    # If h complied, generate bricks
    generate_bricks(h)


def generate_bricks(n):
    for i in range(n):
        # Shortcut version
        space = " " * int(n - i - 1)
        hash = "#" * int(i + 1)
        print(space + hash + "  " + hash)

        # Long version
        # Generate indent to right
        # for _ in range(n - i - 1):
        #    print(" ", end="")

        # Generate bricks
        # for _ in range(i + 1):
        #    print("#", end="")

        # Two spaces
        # print("  ", end="")

        # Generate bricks
        # for _ in range(i + 1):
        #    print("#", end="")

        # Spaces
        # print()


main()
