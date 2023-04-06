#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool check_sum(long num);

int main(void)
{
    //defining
    int digits = 0, single_digit = 0, two_digit = 0;
    bool checksum;
    long number = get_long("Number: ");
    checksum = check_sum(number);
    // checking if the card sintaxe is valid
    if (checksum == false)
    {
        return 0;
    }
    // counting the digits and saving the last ones
    while (number > 0)
    {
        if (number < 10)
        {
            single_digit = number;
        }
        if (number > 10 && number < 100)
        {
            two_digit = number;
        }
        number /= 10;
        digits++;
    }

    //indentifying the bank
    if (digits == 13 || digits == 16)
    {
        if (single_digit == 4)
        {

            printf("VISA\n");
            return 0;
        }
        else
        {
            if (digits == 16)
            {
                if (two_digit == 51 || two_digit == 52 || two_digit == 53 || two_digit == 54 || two_digit == 55)
                {
                    printf("MASTERCARD\n");
                    return 0;
                }
                else
                {
                    printf("INVALID\n");
                    return 0;
                }

            }
        }
    }
    // identifying pt.2
    if (digits == 15)
    {
        if (two_digit == 34 || two_digit == 37)
        {
            printf("AMEX\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    if (true)
    {
            printf("INVALID\n");
    }

}
// function to check the checksum
bool check_sum(long num)
{
    int total = 0, charger = 0;
    bool var = true;
    while (num > 0)
    {
        if (var == true)
        {
            total += num % 10;
            num /= 10;
            var = false;
        }
        else
        {
            charger = num % 10;
            charger *= 2;
            if (charger >= 10)
            {
                // separating the digits to add them
                total += charger % 10;
                total += charger / 10;
            }
            else
            {
                total += charger;
            }
            var = true;
            num /= 10;
        }
    }

    if (total % 10 == 0)
    {
        return true;
    }
    printf("INVALID\n");
    return false;
}