#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for input
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    // Building a pyramid
    int s = 1;
    for (int h = 1; h <= n; h++)
    {
        // Printing out spaces
        s = h;
        while (s <= n - 1)
        {
            printf(" ");
            s++;
        }
        // Printing out the hashes
        for (int i = 1; i <= h; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}
