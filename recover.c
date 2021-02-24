#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Check whether the user has provided exactly one file name
    if (argc != 2)
    {
        // Print an error if user hasn't provided exactly one file name
        printf("Usage: ./recover image\n");
        return 2;
    }

    // Open the provided file
    FILE *image = fopen(argv[1], "r");
    // If file cannot be opened for reading, print an error
    if (image == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Defining BYTE for facilitating buffer
    typedef uint8_t BYTE;

    // Defining buffer to temporarily store bytes
    BYTE buffer[512];

    // i is the image counter
    int i = 0;

    // This store the filename of image
    char *filename = NULL;
    FILE *img = NULL;

    // This loop ensures that whole file provided is read
    while (fread(buffer, 512, 1, image) == 1)
    {
        // Checking whether it is start of a new image
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Checking if it is the first image, and if yes, writing data to it
            if (i == 0)
            {
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                i++;
            }
            // This case starts writing data to next images
            else
            {
                // First we close the already open file, then open new one and start writing to it
                fclose(img);
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                i++;
            }
        }
        // Here, we continue writing data if no new image is found in subsequent block
        else if (i > 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    // Closing the last file after completion of writing process
    fclose(img);
    fclose(image);
}
