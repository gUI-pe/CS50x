from cs50 import get_int
import sys


def main():
    number = get_int("Number: ")
    if checksum(number) == False:
        sys.exit(1)

    digits = 0
    while number > 0:
        if number < 10:
            single_digit = number
        if number > 10 and number < 100:
            two_digit = number
        number = number // 10
        digits += 1

    if digits == 13 or digits == 16:
        if single_digit == 4:
            print("VISA")
            sys.exit(0)
        else:
            if digits == 16:
                if two_digit == 51 or two_digit == 52 or two_digit == 53 or two_digit == 54 or two_digit == 55:
                    print("MASTERCARD")
                    sys.exit(0)
                else:
                    print("INVALID")
                    sys.exit(2)

    if digits == 15:
        if two_digit == 34 or two_digit == 37:
            print("AMEX")
            sys.exit(0)
        else:
            print("INVALID")
            sys.exit(2)
    else:
        print("INVALID")
        sys.exit(3)


def checksum(n):
    var = True
    total = 0
    while n > 0:
        if var == True:
            total += n % 10
            n = n // 10
            var = False
        else:
            charger = n % 10
            charger *= 2
            if charger >= 10:
                total += charger % 10
                total += charger // 10
            else:
                total += charger
            var = True
            n = n // 10

    if total % 10 == 0:
        return True
    else:
        print("INVALID")
        return False


main()