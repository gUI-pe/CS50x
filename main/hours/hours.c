#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

float calc_hours(int hours[], int weeks, char output);
float calc_hourz(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');
    if (output == 'T')
    {
        printf("%.1f hours\n", calc_hours(hours, weeks, output));
    }
    else
    {
        printf("%.1f hours\n", calc_hourz(hours, weeks, output));
    }

}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
   int T = 0;

   for (int i = 0; i < weeks; i++)
   {
       T += hours[i];
   }
   return T;
}

float calc_hourz(int hours[], int weeks, char output)
{
   int T = 0;
   float A = 0;

   for (int i = 0; i < weeks; i++)
   {
       T += hours[i];
   }

   A = (float) T / weeks;
   return A;
}