from cs50 import get_int


def main():
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break

    for i in range(height):

        spaces = height - i - 1

        while spaces > 0:
            print(" ", end="")
            spaces -= 1

        for j in range(i + 1):
            print("#", end="")

        print("  ", end="")

        for j in range(i + 1):
            print("#", end="")

        print("")


main()