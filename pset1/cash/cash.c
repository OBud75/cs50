#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    //getting the user's input
    float dollars;

    do
    {
        dollars = get_float("How much I own you?: ");
    }
    while (dollars <= 0);
    
    int cents = round(dollars * 100);
    
    //variables
    int quarters = 0, dimes = 0, nickels = 0, pennies = 0;
    
    
    
    //add quarters to the change given and subtract 25cents to the change due as long as possible
    if (cents >= 25)
    {
        do
        {
            quarters += 1;
            cents -= 25;
        }
        while (cents >= 25);
    }
    
    //add 1 dimes to the change given and subtract 10cents to the change due as long as possible
    if (cents >= 10)
    {
        do
        {
            dimes += 1;
            cents -= 10;
        }
        while (cents >= 10);
    }
    
    //add nickels to the change given and subtract 5cents to the change due as long as possible
    if (cents >= 5)
    {
        do
        {
            nickels += 1;
            cents -= 5;
        }
        while (cents >= 5);
    }
    
    //add pennies to the change given and subtract 1cents to the change due as long as possible
    if (cents >= 1)
    {
        do
        {
            pennies += 1;
            cents -= 1;
        }
        while (cents >= 1);
    }


    int coins_due = quarters + dimes + nickels + pennies;
    //output
    printf("%i\n", coins_due);
}