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

// Function to calculate the square root of the sum of the given two integers, check whether it is greater than, less than or equal to 255, and return the appropriate result
int s_root(int x, int y);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Defining a temporary array for copying the original image
    RGBTRIPLE image_c[height + 2][width + 2];

    // Copying the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_c[i + 1][j + 1].rgbtBlue = image[i][j].rgbtBlue;
            image_c[i + 1][j + 1].rgbtGreen = image[i][j].rgbtGreen;
            image_c[i + 1][j + 1].rgbtRed = image[i][j].rgbtRed;
        }
    }
    // Defining the x and y kernels
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // From here, actual process starts
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            // Defining variables to track the weighted sum of various
            int gx_blue = 0;
            int gy_blue = 0;
            int gx_green = 0;
            int gy_green = 0;
            int gx_red = 0;
            int gy_red = 0;

            // Now looping throught the 3*3 grid, while checking for edge and corner pixels
            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    // This step ensures that weighted sum of edge and corner pixels is properly calculated
                    if (i + m == 0 || i + m == height + 1 || j + n == 0 || j + n == width + 1)
                    {
                        continue;
                    }

                    // Now we multiply each pixel of the 3*3 grid with the respective gx and gy values
                    gx_blue += image_c[i + m][j + n].rgbtBlue * Gx[m + 1][n + 1];
                    gy_blue += image_c[i + m][j + n].rgbtBlue * Gy[m + 1][n + 1];
                    gx_green += image_c[i + m][j + n].rgbtGreen * Gx[m + 1][n + 1];
                    gy_green += image_c[i + m][j + n].rgbtGreen * Gy[m + 1][n + 1];
                    gx_red += image_c[i + m][j + n].rgbtRed * Gx[m + 1][n + 1];
                    gy_red += image_c[i + m][j + n].rgbtRed * Gy[m + 1][n + 1];
                }
            }

            // Here, we define variables to store the square roots temporarily
            int s_blue = s_root(gx_blue, gy_blue);
            int s_green = s_root(gx_green, gy_green);
            int s_red = s_root(gx_red, gy_red);

            // Now we finally put the modified image pixels together for the effect
            image[i - 1][j - 1].rgbtBlue = s_blue;
            image[i - 1][j - 1].rgbtGreen = s_green;
            image[i - 1][j - 1].rgbtRed = s_red;
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

// Definition of the s_root function
int s_root(int x, int y)
{
    int root = (int) round(sqrt((x * x) + (y * y)));
    // Here we check for the limiting cases
    if (root >= 255)
    {
        return 255;
    }
    else
    {
        return root;
    }
}