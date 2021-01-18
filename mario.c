#include <cs50.h>
#include <stdio.h>

int  main(void)
{
    // Prompt user for input
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    // Building the pyramids
    int s = 1;
    for (int h = 1; h <= n; h++)
    {
        s = h;
        // Building first pyramid
        while (s <= n - 1)
        {
            printf(" ");
            s++;
        }
        for (int i = 1; i <= h; i++)
        {
            printf("#");
        }
        // Building second pyramid
        printf("  ");
        for (int i = 1; i <= h; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}
