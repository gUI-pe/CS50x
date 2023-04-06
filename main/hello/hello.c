#include <stdio.h>
#include <cs50.h>

int main(void)

{
    // prompting user for input
    string nome = get_string("Qual é seu nome? \n");
    printf("olá, %s \n", nome);

}