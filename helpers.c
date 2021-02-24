#include "helpers.h"
#include <math.h>

// Function to round the average of 3 ints to nearest integer
int round_avg(int a, int b, int c);

// Function to swap the value of pixels in reflection
void swap(BYTE *r, BYTE *g, BYTE *b, BYTE *rr, BYTE *gg, BYTE *bb);

// Function to round the average of 4 ints to nearest integer
int round_avg4(int a, int b, int c, int d);

// Function to round the average of 6 ints to nearest integer
int round_avg6(int a, int b, int c, int d, int e, int f);

// Function to round the average of 9 ints to nearest integer
int round_avg9(int a, int b, int c, int d, int e, int f, int g, int h, int i);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through each of the pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Taking the average of the colour numbers
            int avg = round_avg(image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed);
            // Assigning the average to each of the colours
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;
            float sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            float sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            // First check whether the sepia blue colour exceeds 255. If yes do the necessary adjustments
            if ((int) round(sepiaBlue) > 255)
            {
                image[i][j].rgbtBlue = 255;
                // Here other colour conditions are also checked to avoid any glitches
                if ((int) round(sepiaGreen) <= 255)
                {
                    image[i][j].rgbtGreen = (int) round(sepiaGreen);
                }
                if ((int) round(sepiaRed) <= 255)
                {
                    image[i][j].rgbtRed = (int) round(sepiaRed);
                }
            }
            // Then check whether the sepia green colour exceeds 255. If yes do the necessary adjustments
            if ((int) round(sepiaGreen) > 255)
            {
                // Here other colour conditions are also checked to avoid any glitches
                if ((int) round(sepiaBlue) <= 255)
                {
                    image[i][j].rgbtBlue = (int) round(sepiaBlue);
                }
                image[i][j].rgbtGreen = 255;
                if ((int) round(sepiaRed) <= 255)
                {
                    image[i][j].rgbtRed = (int) round(sepiaRed);
                }
            }
            // Then check whether the sepia red colour exceeds 255. If yes do the necessary adjustments
            if ((int) round(sepiaRed) > 255)
            {
                // Here other colour conditions are also checked to avoid any glitches
                if ((int) round(sepiaBlue) <= 255)
                {
                    image[i][j].rgbtBlue = (int) round(sepiaBlue);
                }
                if ((int) round(sepiaGreen) <= 255)
                {
                    image[i][j].rgbtGreen = (int) round(sepiaGreen);
                }
                image[i][j].rgbtRed = 255;
            }
            // After checking each of the above cases, if none are true, then do the following basic substitution
            else
            {
                image[i][j].rgbtBlue = (int) round(sepiaBlue);
                image[i][j].rgbtGreen = (int) round(sepiaGreen);
                image[i][j].rgbtRed = (int) round(sepiaRed);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // First we check if the no. of pixels in a row is odd or even
        if (width % 2 == 1)
        {
            // This case performs swapping if no. of pixels is odd
            for (int j = 0; j < (width - 1) / 2; j++)
            {
                swap(&image[i][j].rgbtRed, &image[i][j].rgbtGreen, &image[i][j].rgbtBlue, &image[i][width - (1 + j)].rgbtRed,
                     &image[i][width - (1 + j)].rgbtGreen, &image[i][width - (1 + j)].rgbtBlue);
            }
        }
        else
        {
            // This case performs swapping if no. of pixels is even
            for (int k = 0; k < width / 2; k++)
            {
                swap(&image[i][k].rgbtRed, &image[i][k].rgbtGreen, &image[i][k].rgbtBlue, &image[i][width - (1 + k)].rgbtRed,
                     &image[i][width - (1 + k)].rgbtGreen, &image[i][width - (1 + k)].rgbtBlue);
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating a buffer array for copying original array
    RGBTRIPLE image_c[height][width];
    // Copying the array into another array for precise operating
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_c[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_c[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_c[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    // First we iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // The following four are the corner cases
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtBlue = round_avg4(image_c[i][j].rgbtBlue, image_c[i + 1][j].rgbtBlue, image_c[i][j + 1].rgbtBlue,
                                                  image_c[i + 1][j + 1].rgbtBlue);
                image[i][j].rgbtGreen = round_avg4(image_c[i][j].rgbtGreen, image_c[i + 1][j].rgbtGreen, image_c[i][j + 1].rgbtGreen,
                                                   image_c[i + 1][j + 1].rgbtGreen);
                image[i][j].rgbtRed = round_avg4(image_c[i][j].rgbtRed, image_c[i + 1][j].rgbtRed, image_c[i][j + 1].rgbtRed,
                                                 image_c[i + 1][j + 1].rgbtRed);
            }
            else if (i == 0 && j == (width - 1))
            {
                image[i][j].rgbtBlue = round_avg4(image_c[i][j].rgbtBlue, image_c[i][j - 1].rgbtBlue, image_c[i + 1][j].rgbtBlue,
                                                  image_c[i + 1][j - 1].rgbtBlue);
                image[i][j].rgbtGreen = round_avg4(image_c[i][j].rgbtGreen, image_c[i][j - 1].rgbtGreen, image_c[i + 1][j].rgbtGreen,
                                                   image_c[i + 1][j - 1].rgbtGreen);
                image[i][j].rgbtRed = round_avg4(image_c[i][j].rgbtRed, image_c[i][j - 1].rgbtRed, image_c[i + 1][j].rgbtRed,
                                                 image_c[i + 1][j - 1].rgbtRed);
            }
            else if (i == (height - 1) && j == 0)
            {
                image[i][j].rgbtBlue = round_avg4(image_c[i][j].rgbtBlue, image_c[i][j + 1].rgbtBlue, image_c[i - 1][j].rgbtBlue,
                                                  image_c[i - 1][j + 1].rgbtBlue);
                image[i][j].rgbtGreen = round_avg4(image_c[i][j].rgbtGreen, image_c[i][j + 1].rgbtGreen, image_c[i - 1][j].rgbtGreen,
                                                   image_c[i - 1][j + 1].rgbtGreen);
                image[i][j].rgbtRed = round_avg4(image_c[i][j].rgbtRed, image_c[i][j + 1].rgbtRed, image_c[i - 1][j].rgbtRed,
                                                 image_c[i - 1][j + 1].rgbtRed);
            }
            else if (i == (height - 1) && j == (width - 1))
            {
                image[i][j].rgbtBlue = round_avg4(image_c[i][j].rgbtBlue, image_c[i][j - 1].rgbtBlue, image_c[i - 1][j].rgbtBlue,
                                                  image_c[i - 1][j - 1].rgbtBlue);
                image[i][j].rgbtGreen = round_avg4(image_c[i][j].rgbtGreen, image_c[i][j - 1].rgbtGreen, image_c[i - 1][j].rgbtGreen,
                                                   image_c[i - 1][j - 1].rgbtGreen);
                image[i][j].rgbtRed = round_avg4(image_c[i][j].rgbtRed, image_c[i][j - 1].rgbtRed, image_c[i - 1][j].rgbtRed,
                                                 image_c[i - 1][j - 1].rgbtRed);
            }
            // The next four are the edge cases
            else if (i == 0 && j != 0 && j != (width - 1))
            {
                image[i][j].rgbtBlue = round_avg6(image_c[i][j].rgbtBlue, image_c[i][j + 1].rgbtBlue, image_c[i][j - 1].rgbtBlue,
                                                  image_c[i + 1][j].rgbtBlue, image_c[i + 1][j + 1].rgbtBlue, image_c[i + 1][j - 1].rgbtBlue);
                image[i][j].rgbtGreen = round_avg6(image_c[i][j].rgbtGreen, image_c[i][j + 1].rgbtGreen, image_c[i][j - 1].rgbtGreen,
                                                   image_c[i + 1][j].rgbtGreen, image_c[i + 1][j + 1].rgbtGreen, image_c[i + 1][j - 1].rgbtGreen);
                image[i][j].rgbtRed = round_avg6(image_c[i][j].rgbtRed, image_c[i][j + 1].rgbtRed, image_c[i][j - 1].rgbtRed,
                                                 image_c[i + 1][j].rgbtRed, image_c[i + 1][j + 1].rgbtRed, image_c[i + 1][j - 1].rgbtRed);
            }
            else if (j == 0 && i != 0 && i != (height - 1))
            {
                image[i][j].rgbtBlue = round_avg6(image_c[i][j].rgbtBlue, image_c[i + 1][j].rgbtBlue, image_c[i - 1][j].rgbtBlue,
                                                  image_c[i][j + 1].rgbtBlue, image_c[i + 1][j + 1].rgbtBlue, image_c[i - 1][j + 1].rgbtBlue);
                image[i][j].rgbtGreen = round_avg6(image_c[i][j].rgbtGreen, image_c[i + 1][j].rgbtGreen, image_c[i - 1][j].rgbtGreen,
                                                   image_c[i][j + 1].rgbtGreen, image_c[i + 1][j + 1].rgbtGreen, image_c[i - 1][j + 1].rgbtGreen);
                image[i][j].rgbtRed = round_avg6(image_c[i][j].rgbtRed, image_c[i + 1][j].rgbtRed, image_c[i - 1][j].rgbtRed,
                                                 image_c[i][j + 1].rgbtRed, image_c[i + 1][j + 1].rgbtRed, image_c[i - 1][j + 1].rgbtRed);
            }
            else if (i == (height - 1) && j != 0 && j != (width - 1))
            {
                image[i][j].rgbtBlue = round_avg6(image_c[i][j].rgbtBlue, image_c[i][j + 1].rgbtBlue, image_c[i][j - 1].rgbtBlue,
                                                  image_c[i - 1][j].rgbtBlue, image_c[i - 1][j + 1].rgbtBlue, image_c[i - 1][j - 1].rgbtBlue);
                image[i][j].rgbtGreen = round_avg6(image_c[i][j].rgbtGreen, image_c[i][j + 1].rgbtGreen, image_c[i][j - 1].rgbtGreen,
                                                   image_c[i - 1][j].rgbtGreen, image_c[i - 1][j + 1].rgbtGreen, image_c[i - 1][j - 1].rgbtGreen);
                image[i][j].rgbtRed = round_avg6(image_c[i][j].rgbtRed, image_c[i][j + 1].rgbtRed, image_c[i][j - 1].rgbtRed,
                                                 image_c[i - 1][j].rgbtRed, image_c[i - 1][j + 1].rgbtRed, image_c[i - 1][j - 1].rgbtRed);
            }
            else if (j == (width - 1) && i != 0 && i != (height - 1))
            {
                image[i][j].rgbtBlue = round_avg6(image_c[i][j].rgbtBlue, image_c[i + 1][j].rgbtBlue, image_c[i - 1][j].rgbtBlue,
                                                  image_c[i][j - 1].rgbtBlue, image_c[i - 1][j - 1].rgbtBlue, image_c[i + 1][j - 1].rgbtBlue);
                image[i][j].rgbtGreen = round_avg6(image_c[i][j].rgbtGreen, image_c[i + 1][j].rgbtGreen, image_c[i - 1][j].rgbtGreen,
                                                   image_c[i][j - 1].rgbtGreen, image_c[i - 1][j - 1].rgbtGreen, image_c[i + 1][j - 1].rgbtGreen);
                image[i][j].rgbtRed = round_avg6(image_c[i][j].rgbtRed, image_c[i + 1][j].rgbtRed, image_c[i - 1][j].rgbtRed,
                                                 image_c[i][j - 1].rgbtRed, image_c[i - 1][j - 1].rgbtRed, image_c[i + 1][j - 1].rgbtRed);
            }
            // This is the final middle pixel case
            else
            {
                image[i][j].rgbtBlue = round_avg9(image_c[i][j].rgbtBlue, image_c[i][j - 1].rgbtBlue, image_c[i - 1][j].rgbtBlue,
                                                  image_c[i - 1][j - 1].rgbtBlue, image_c[i][j + 1].rgbtBlue, image_c[i + 1][j].rgbtBlue, image_c[i + 1][j + 1].rgbtBlue,
                                                  image_c[i + 1][j - 1].rgbtBlue, image_c[i - 1][j + 1].rgbtBlue);
                image[i][j].rgbtGreen = round_avg9(image_c[i][j].rgbtGreen, image_c[i][j - 1].rgbtGreen, image_c[i - 1][j].rgbtGreen,
                                                   image_c[i - 1][j - 1].rgbtGreen, image_c[i][j + 1].rgbtGreen, image_c[i + 1][j].rgbtGreen, image_c[i + 1][j + 1].rgbtGreen,
                                                   image_c[i + 1][j - 1].rgbtGreen, image_c[i - 1][j + 1].rgbtGreen);
                image[i][j].rgbtRed = round_avg9(image_c[i][j].rgbtRed, image_c[i][j - 1].rgbtRed, image_c[i - 1][j].rgbtRed,
                                                 image_c[i - 1][j - 1].rgbtRed, image_c[i][j + 1].rgbtRed, image_c[i + 1][j].rgbtRed, image_c[i + 1][j + 1].rgbtRed,
                                                 image_c[i + 1][j - 1].rgbtRed, image_c[i - 1][j + 1].rgbtRed);
            }
        }
    }
    return;
}

// Definition of the rounded average function
int round_avg(int a, int b, int c)
{
    return (int) round((a + b + c) / 3.0);
}

// Definition of the swap function
void swap(BYTE *r, BYTE *g, BYTE *b, BYTE *rr, BYTE *gg, BYTE *bb)
{
    //Here we use pointers to actually change contents in memory
    BYTE r1 = *r;
    BYTE g1 = *g;
    BYTE b1 = *b;
    // From here we actually start swapping the values of the colours
    *r = *rr;
    *g = *gg;
    *b = *bb;
    *rr = r1;
    *gg = g1;
    *bb = b1;
}

// Definition of round_avg4 function
int round_avg4(int a, int b, int c, int d)
{
    return (int) round((a + b + c + d) / 4.0);
}

// Definition of round_avg6 function
int round_avg6(int a, int b, int c, int d, int e, int f)
{
    return (int) round((a + b + c + d + e + f) / 6.0);
}

// Definition of round_avg9 function
int round_avg9(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
    return (int) round((a + b + c + d + e + f + g + h + i) / 9.0);
}
