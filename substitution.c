#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Taking key from user
int main(int argc, string argv[])
{
    // Process of validation starts
    if (argc == 2)
    {
        // Checking if there are exactly 26 characters in the key
        if (strlen(argv[1]) != 26)
        {
            // Here, different messages for different types of invalid keys will be managed
            int stat = 0;
            for (int i = 0; i < strlen(argv[1]); i++)
            {
                if (isalpha(argv[1][i]))
                {
                    stat++;
                }
            }
            // If all characters are alphabets but less than 26 chars are provided
            if (stat == strlen(argv[1]))
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            // If all chars are not alphabets
            else
            {
                printf("Usage: ./substitution Key\n");
                return 1;
            }
        }
        // From here, keys of exactly 26 characters will be handled
        else
        {
            int status = 0;
            for (int i = 0; i < strlen(argv[1]); i++)
            {
                // First checking if all chars are alphabets
                if (isalpha(argv[1][i]))
                {
                    status++;
                }
                else
                {
                    printf("Key must only contaian alphabetic characters.\n");
                    return 1;
                }
            }
            // Checking for any repeated alphabets
            int repeat = 1;
            for (int i = 0; i < strlen(argv[1]); i++)
            {
                for (int j = i + 1; j < strlen(argv[1]); j++)
                {
                    if (argv[1][i] == argv[1][j] || argv[1][i] + 32 == argv[1][j] || argv[1][i] - 32 == argv[1][j])
                    {
                        repeat++;
                    }
                }
            }
            // Program stops if repeated alphabets are identified
            if (repeat > 1)
            {
                printf("Key must contain 26 distinct alphabets.\n");
                return 1;
            }
            // Here the validation process completes and enciphering starts
            // Prompting for plaintext
            string p = get_string("plaintext:  ");
            printf("ciphertext: ");
            // Enciphering process starts
            string key = argv[1];
            char key_u[26];
            char key_l[26];
            // Converting the whole key to uppercase
            for (int i = 0; i < 26; i++)
            {
                if (islower(key[i]))
                {
                    key_u[i] = toupper(key[i]);
                    key_l[i] = key[i];
                }
                else if (isupper(key[i]))
                {
                    key_l[i] = tolower(key[i]);
                    key_u[i] = key[i];
                }
            }
            // Assigning a variable to denote each character of enciphered text
            char c;
            // Here actual enciphering starts
            for (int i  = 0; i < strlen(p); i++)
            {
                // The following variables are assigned to substitute the characters as per like-for-like
                char uppercase[26];
                char lowercase[26];
                for (int b = 0; b < 26; b++)
                {
                    uppercase[b] = 'A' + b;
                    lowercase[b] = 'a' + b;
                }
                // This step ensures that only alphabets are substituted
                if (isalpha(p[i]))
                {
                    // The following steps ensure that the substitution is case-sensitive
                    if (isupper(p[i]))
                    {
                        int j = p[i] - 65;
                        uppercase[j] = key_u[j];
                        p[i] = uppercase[j];
                        c = p[i];
                        printf("%c", c);
                    }
                    else if (islower(p[i]))
                    {
                        int x = p[i] - 97;
                        lowercase[x] = key_l[x];
                        p[i] = lowercase[x];
                        c = p[i];
                        printf("%c", c);
                    }
                }
                // This step ensures that characters other than alphabets remain as they are
                else
                {
                    c = p[i];
                    printf("%c", c);
                }
            }
            printf("\n");
        }
    }
    else
    {
        printf("Usage: ./substitution Key\n");
        return 1;
    }
}
