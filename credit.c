#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for a credit card number
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 1000000000000 || n > 9999999999999999);
    if (n < 1000000000000)
    {
        printf("INVALID\n");
    }
    // Calculating checksum
    string status;
    if (n >= 1000000000000 && n <= 9999999999999)
    {
        int a = (n % 100) / 10; // 12th digit
        int b = (n % 10000) / 1000; // 10th digit
        int c = (n % 1000000) / 100000; // 8th digit
        int d = (n % 100000000) / 10000000; // 6th digit
        int e = (n % 10000000000) / 1000000000; // 4th digit
        int f = (n % 1000000000000) / 100000000000; // 2nd digit
        int a1 = (n % 10); // 13th digit
        int b1 = (n % 1000) / 100; //11th digit
        int c1 = (n % 100000) / 10000; //9th digit
        int d1 = (n % 10000000) / 1000000; // 7th digit
        int e1 = (n % 1000000000) / 100000000; // 5th digit
        int f1 = (n % 100000000000) / 10000000000; // 3rd digit
        int f2 = (n % 10000000000000) / 1000000000000; // 1st digit
        a = a * 2;
        b = b * 2;
        c = c * 2;
        d = d * 2;
        e = e * 2;
        f = f * 2;
        // ss - calculating sum from second last digit
        int ss = (a % 10) + (a / 10) + (b % 10) + (b / 10) + (c % 10) + (c / 10) + (d % 10) + (d / 10) + (e % 10) + (e / 10) + (f % 10) +
                 (f / 10);
        // s - calculating sum ss + (sum of remaining digits)
        int s = ss + a1 + b1 + c1 + d1 + e1 + f1 + f2;
        if (s % 10 == 0)
        {
            status = "valid";
            if (n / 1000000000000 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            status = "invalid";
            printf("INVALID\n");
        }
    }
    if (n >= 1000000000000000 && n <= 9999999999999999)
    {
        int a = (n % 100) / 10; // 15th digit
        int b = (n % 10000) / 1000; // 13th digit
        int c = (n % 1000000) / 100000; // 11th digit
        int d = (n % 100000000) / 10000000; // 9th digit
        int e = (n % 10000000000) / 1000000000; // 7th digit
        int f = (n % 1000000000000) / 100000000000; // 5th digit
        int g = (n % 100000000000000) / 10000000000000; // 3rd digit
        int h = (n % 10000000000000000) / 1000000000000000; // 1st digit
        int a1 = (n % 10); // 16th digit
        int b1 = (n % 1000) / 100; //14th digit
        int c1 = (n % 100000) / 10000; //12th digit
        int d1 = (n % 10000000) / 1000000; // 10th digit
        int e1 = (n % 1000000000) / 100000000; // 8th digit
        int f1 = (n % 100000000000) / 10000000000; // 6th digit
        int g1 = (n % 10000000000000) / 1000000000000; // 4th digit
        int h1 = (n % 1000000000000000) / 100000000000000; // 2nd digit
        a = a * 2;
        b = b * 2;
        c = c * 2;
        d = d * 2;
        e = e * 2;
        f = f * 2;
        g = g * 2;
        h = h * 2;
        // ss - calculating sum from second last digit
        int ss = (a % 10) + (a / 10) + (b % 10) + (b / 10) + (c % 10) + (c / 10) + (d % 10) + (d / 10) + (e % 10) + (e / 10) + (f % 10) +
                 (f / 10) + (g % 10) + (g / 10) + (h % 10) + (h / 10);
        // s - calculating sum ss + (sum of remaining digits)
        int s = ss + a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
        if (s % 10 == 0)
        {
            status = "valid";
            if (n / 1000000000000000 == 4)
            {
                printf("VISA\n");
            }
            else if (n / 100000000000000 == 51 || n / 100000000000000 == 52 || n / 100000000000000 == 53 || n / 100000000000000 == 54
                     || n / 100000000000000 == 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            status = "invalid";
            printf("INVALID\n");
        }
    }
    if (n >= 100000000000000 && n <= 999999999999999)
    {
        int a = (n % 100) / 10; // 14th digit
        int b = (n % 10000) / 1000; // 12th digit
        int c = (n % 1000000) / 100000; // 10th digit
        int d = (n % 100000000) / 10000000; // 8th digit
        int e = (n % 10000000000) / 1000000000; // 6th digit
        int f = (n % 1000000000000) / 100000000000; // 4th digit
        int g = (n % 100000000000000) / 10000000000000; // 2nd digit
        int a1 = (n % 10); // 15th digit
        int b1 = (n % 1000) / 100; //13th digit
        int c1 = (n % 100000) / 10000; //11th digit
        int d1 = (n % 10000000) / 1000000; // 9th digit
        int e1 = (n % 1000000000) / 100000000; // 7th digit
        int f1 = (n % 100000000000) / 10000000000; // 5th digit
        int g1 = (n % 10000000000000) / 1000000000000; // 3rd digit
        int h1 = (n % 1000000000000000) / 100000000000000; // 1st digit
        a = a * 2;
        b = b * 2;
        c = c * 2;
        d = d * 2;
        e = e * 2;
        f = f * 2;
        g = g * 2;
        // ss - calculating sum from second last digit
        int ss = (a % 10) + (a / 10) + (b % 10) + (b / 10) + (c % 10) + (c / 10) + (d % 10) + (d / 10) + (e % 10) + (e / 10) + (f % 10) +
                 (f / 10) + (g % 10) + (g / 10);
        // s - calculating sum ss + (sum of remaining digits)
        int s = ss + a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
        if (s % 10 == 0)
        {
            status = "valid";
            if (n / 10000000000000 == 34 || n / 10000000000000 == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            status = "invalid";
            printf("INVALID\n");
        }
    }
}
