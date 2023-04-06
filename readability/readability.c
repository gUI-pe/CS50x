#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // defining stuff
    int W = 0;
    float S = 0;
    float L = 0;
    int Grade = 0;
    float index = 0;
    string text = get_string("Text: ");
    // index = 0.0588 * L - 0.296 * S - 15.8
    // L is the average number of letters per 100 words in the text
    // S is the average number of sentences per 100 words in the text
    W = count_words(text);
    S = (float) count_sentences(text) / W * 100;
    L = (float) count_letters(text) / W * 100;
    index = 0.0588 * L - 0.296 * S - 15.8;
    Grade = round(index);
    // printing the results
    if (Grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (Grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", Grade);
    }
}
// letters function
int count_letters(string text)
{
    int letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            letters++;
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            letters++;
        }
    }
    return letters;
}
// words function
int count_words(string text)
{
    int words = 0;
    int spaces = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            spaces++;
        }
    }
    words = spaces + 1;
    return words;
}
// sentences function
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}