#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int end, dead, neW, population;
    int years = 0;
    // TODO: Solicite o valor inicial ao usuário
    do
    {
        population = get_int("population size: ");
    }
    while (population <= 8);

    // TODO: Solicite o valor final ao usuário
    do
    {
        end = get_int("end size: ");
    }
    while (end < population);


    // TODO: Calcule o número de anos até o limite
    while (population < end)
    {
        neW = population / 3;
        dead = -population / 4;
        population = population + neW + dead;
        years++;
    }

    // TODO: Imprima o número de anos
    printf("Years: %i \n", years);

}