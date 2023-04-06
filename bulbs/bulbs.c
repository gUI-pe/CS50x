#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    int k = 0;
    int i = 0;
    // TODO
    string message = get_string("Message: ");
    //text into decimal numbers
    int n = strlen(message);
    string dmessage[n];
    while(i < n)
    {
        k = message[i];
        dmessage[i] = k;
        i++;
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
