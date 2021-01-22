#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Getting the key from the user as the command-line argument
int main(int argc, string argv[])
{
    // Here k denotes key
    int k;
    // Validating the key
    if (argc == 2)
    {
        int status = 0;
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]))
            {
                status++;
            }
        }
        if (status == strlen(argv[1]) || status == 0)
        {
            // Converting the string into integer
            k = atoi(argv[1]);
            // Prompting the user to enter plaintext to encipher it
            string s = get_string("plaintext:  ");
            printf("ciphertext: ");
            // Enciphering process starts
            for (int n = 0; n < strlen(s); n++)
            {
                if (isalpha(s[n]))
                {
                    char p = s[n];
                    // This ensures that uppercase alphabets remain uppercase
                    if (isupper(p))
                    {
                        // This step ensures that after Z, the increase in the alphabet continues from A
                        if (p + (k % 26) > 90 && p + (k % 26) < 97)
                        {
                            int x = 90 - p;
                            int y = (k % 26) - x;
                            int z = 26 - y;
                            char c = 90;
                            c = c - z;
                            printf("%c", c);
                        }
                        else
                        {
                            char c = p + (k % 26);
                            printf("%c", c);
                        }
                    }
                    // This ensures that lowercase alphabets remain lowercase
                    if (islower(p))
                    {
                        // This step ensures that after z, the increase in the alphabet continues from a
                        if (p + (k % 26) > 122)
                        {
                            int x = 122 - p;
                            int y = (k % 26) - x;
                            int z = 26 - y;
                            char c = 122;
                            c = c - z;
                            printf("%c", c);
                        }
                        else
                        {
                            char c = p + (k % 26);
                            printf("%c", c);
                        }
                    }
                }
                // This step ensures that the characters other than alphabets including whitespaces remain as it is
                else
                {
                    char p = s[n];
                    char c;
                    c = p;
                    printf("%c", c);
                }
            }
            printf("\n");
        }
        // The steps which follow ensure that no invalid key is entered by the user
        else
        {
            printf("Usage: ./caesar key\n");
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
    }
}
