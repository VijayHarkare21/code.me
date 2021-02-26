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

// Function which takes as argument 3 arrays, multiplies corresponding elements of one of them with the corresponding elements of the other two, and adds the obtained values
// Defining for red, green and blue values distinctly
int arr_mult_add_red(int gx[3][3], int gy[3][3], RGBTRIPLE grid[3][3]);
int arr_mult_add_green(int gx[3][3], int gy[3][3], RGBTRIPLE grid[3][3]);
int arr_mult_add_blue(int gx[3][3], int gy[3][3], RGBTRIPLE grid[3][3]);

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

    // Defining a temporary array to copy the pixels of given image
    RGBTRIPLE image_c[height + 2][width + 2];
    // First writing black colour to the columnar edges
    for (int i = 0; i < height + 2; i++)
    {
        image_c[i][0].rgbtBlue = 0;
        image_c[i][0].rgbtGreen = 0;
        image_c[i][0].rgbtRed = 0;
        image_c[i][width + 2].rgbtBlue = 0;
        image_c[i][width + 2].rgbtGreen = 0;
        image_c[i][width + 2].rgbtRed = 0;
    }
    //Now writing black colour to the row edges
    for (int i = 1; i < width; i++)
    {
        image_c[0][i].rgbtBlue = 0;
        image_c[0][i].rgbtGreen = 0;
        image_c[0][i].rgbtRed = 0;
        image_c[height + 2][i].rgbtBlue = 0;
        image_c[height + 2][i].rgbtGreen = 0;
        image_c[height + 2][i].rgbtRed = 0;
    }
    // Copying the image array into another array for precise operating
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            image_c[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_c[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_c[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    // Defining Gx
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    // Defining Gy
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // Defining a temporary array to store the 3 * 3 pixel grid
    RGBTRIPLE grid[3][3];
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            // Populating the blue part of grid
            grid[0][0].rgbtBlue = image_c[i - 1][j - 1].rgbtBlue;
            grid[0][1].rgbtBlue = image_c[i - 1][j].rgbtBlue;
            grid[0][2].rgbtBlue = image_c[i - 1][j + 1].rgbtBlue;
            grid[1][0].rgbtBlue = image_c[i][j - 1].rgbtBlue;
            grid[1][1].rgbtBlue = image_c[i][j].rgbtBlue;
            grid[1][2].rgbtBlue = image_c[i][j + 1].rgbtBlue;
            grid[2][0].rgbtBlue = image_c[i + 1][j - 1].rgbtBlue;
            grid[2][1].rgbtBlue = image_c[i + 1][j].rgbtBlue;
            grid[2][2].rgbtBlue = image_c[i + 1][j + 1].rgbtBlue;

            // Populating the green part of grid
            grid[0][0].rgbtGreen = image_c[i - 1][j - 1].rgbtGreen;
            grid[0][1].rgbtGreen = image_c[i - 1][j].rgbtGreen;
            grid[0][2].rgbtGreen = image_c[i - 1][j + 1].rgbtGreen;
            grid[1][0].rgbtGreen = image_c[i][j - 1].rgbtGreen;
            grid[1][1].rgbtGreen = image_c[i][j].rgbtGreen;
            grid[1][2].rgbtGreen = image_c[i][j + 1].rgbtGreen;
            grid[2][0].rgbtGreen = image_c[i + 1][j - 1].rgbtGreen;
            grid[2][1].rgbtGreen = image_c[i + 1][j].rgbtGreen;
            grid[2][2].rgbtGreen = image_c[i + 1][j + 1].rgbtGreen;

            // Populating the red part of grid
            grid[0][0].rgbtRed = image_c[i - 1][j - 1].rgbtRed;
            grid[0][1].rgbtRed = image_c[i - 1][j].rgbtRed;
            grid[0][2].rgbtRed = image_c[i - 1][j + 1].rgbtRed;
            grid[1][0].rgbtRed = image_c[i][j - 1].rgbtRed;
            grid[1][1].rgbtRed = image_c[i][j].rgbtRed;
            grid[1][2].rgbtRed = image_c[i][j + 1].rgbtRed;
            grid[2][0].rgbtRed = image_c[i + 1][j - 1].rgbtRed;
            grid[2][1].rgbtRed = image_c[i + 1][j].rgbtRed;
            grid[2][2].rgbtRed = image_c[i + 1][j + 1].rgbtRed;

            // Check whether the blue colour exceeds 255. If yes do the necessary adjustments
            if (arr_mult_add_blue(Gx, Gy, grid) > 255)
            {
                image[i - 1][j - 1].rgbtBlue = 255;
                // Here other colour conditions are also checked to avoid any glitches
                if (arr_mult_add_green(Gx, Gy, grid) <= 255)
                {
                    image[i - 1][j - 1].rgbtGreen = arr_mult_add_green(Gx, Gy, grid);
                }
                if (arr_mult_add_red(Gx, Gy, grid) <= 255)
                {
                    image[i - 1][j - 1].rgbtRed = arr_mult_add_red(Gx, Gy, grid);
                }
            }
            // Then check whether the green colour exceeds 255. If yes do the necessary adjustments
            if (arr_mult_add_green(Gx, Gy, grid) > 255)
            {
                // Here other colour conditions are also checked to avoid any glitches
                if (arr_mult_add_blue(Gx, Gy, grid) <= 255)
                {
                    image[i - 1][j - 1].rgbtBlue = arr_mult_add_blue(Gx, Gy, grid);
                }
                image[i - 1][j - 1].rgbtGreen = 255;
                if (arr_mult_add_red(Gx, Gy, grid) <= 255)
                {
                    image[i - 1][j - 1].rgbtRed = arr_mult_add_red(Gx, Gy, grid);
                }
            }
            // Then check whether the red colour exceeds 255. If yes do the necessary adjustments
            if (arr_mult_add_red(Gx, Gy, grid) > 255)
            {
                // Here other colour conditions are also checked to avoid any glitches
                if (arr_mult_add_blue(Gx, Gy, grid) <= 255)
                {
                    image[i - 1][j - 1].rgbtBlue = arr_mult_add_blue(Gx, Gy, grid);
                }
                if (arr_mult_add_green(Gx, Gy, grid) <= 255)
                {
                    image[i - 1][j - 1].rgbtGreen = arr_mult_add_green(Gx, Gy, grid);
                }
                image[i - 1][j - 1].rgbtRed = 255;
            }
            // After checking each of the above cases, if none are true, then do the following basic substitution
            else
            {
                image[i - 1][j - 1].rgbtBlue = arr_mult_add_blue(Gx, Gy, grid);
                image[i - 1][j - 1].rgbtGreen = arr_mult_add_green(Gx, Gy, grid);
                image[i - 1][j - 1].rgbtRed = arr_mult_add_red(Gx, Gy, grid);
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

// Definition of the arr_mult_add_red function
int arr_mult_add_red(int gx[3][3], int gy[3][3], RGBTRIPLE grid[3][3])
{
    // Defining two variables for storing Gx and Gy values
    double Gx = 0;
    double Gy = 0;
    // In this loop the multiplication and addition takes place
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Gx = Gx + (grid[i][j].rgbtRed * gx[i][j]);
            Gy = Gy + (grid[i][j].rgbtRed * gy[i][j]);
        }
    }
    // The square root is calculated for the magnitudes
    double root = sqrt((Gx * Gx) + (Gy * Gy));
    return (int) round(root);
}

// Definition of the arr_mult_add_green function
int arr_mult_add_green(int gx[3][3], int gy[3][3], RGBTRIPLE grid[3][3])
{
    // Defining two variables for storing Gx and Gy values
    double Gx = 0;
    double Gy = 0;
    // In this loop the multiplication and addition takes place
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Gx = Gx + (grid[i][j].rgbtGreen * gx[i][j]);
            Gy = Gy + (grid[i][j].rgbtGreen * gy[i][j]);
        }
    }
    // The square root is calculated for the magnitudes
    double root = sqrt((Gx * Gx) + (Gy * Gy));
    return (int) round(root);
}

// Definition of the arr_mult_add_blue function
int arr_mult_add_blue(int gx[3][3], int gy[3][3], RGBTRIPLE grid[3][3])
{
    // Defining two variables for storing Gx and Gy values
    double Gx = 0;
    double Gy = 0;
    // In this loop the multiplication and addition takes place
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Gx = Gx + (grid[i][j].rgbtBlue * gx[i][j]);
            Gy = Gy + (grid[i][j].rgbtBlue * gy[i][j]);
        }
    }
    // The square root is calculated for the magnitudes
    double root = sqrt((Gx * Gx) + (Gy * Gy));
    return (int) round(root);
}