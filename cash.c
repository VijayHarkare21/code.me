#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for input
    float d;
    do
    {
        d = get_float("Change owed: ");
    }
    while (d < 0);
    // Change float to int
    int c = round(d * 100);
    // Def. variables for no. of coins: x - 25, y - 10, z - 5, w - 1
    int x = 0;
    int y = 0;
    int z = 0;
    int w = 0;
    // Using the coins to return change owed
    int i = 1; // i stands for integral multiples
    while (c >= 25 * i)
    {
        x++;
        c = c - 25;
        i++;
    }
    i = 1;
    while (c >= 10 * i)
    {
        y++;
        c = c - 10;
        i++;
    }
    i = 1;
    while (c >= 5 * i)
    {
        z++;
        c = c - 5;
        i++;
    }
    i = 1;
    while (c >= 1 * i)
    {
        w++;
        c = c - 1;
        i++;
    }
    // Calculate the total coins used and print the respective value
    int a = x + y + z + w;
    printf("%i\n", a);
}
