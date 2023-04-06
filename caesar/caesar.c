#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Make sure every character in argv[1] is a digit
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // Convert argv[1] from a `string` to an `int`
    int j = atoi(argv[1]);

    // Prompt user for plaintext
    string prompt = get_string("plaintext: ");
    printf("ciphertext: ");

    // For each character in the plaintext:
    // Rotate the character if it's a letter
    for (int i = 0, n = strlen(prompt); i < n; i++)
    {
        if (isalpha(prompt[i]))
        {
            if (isupper(prompt[i]))
            {
                printf("%c", (prompt[i] - 65 + j) % 26 + 65);
            }
            else
            {
                printf("%c", (prompt[i] - 97 + j) % 26 + 97);
            }
        }
        else
        {
            printf("%c", prompt[i]);
        }
    }
    printf("\n");
}

