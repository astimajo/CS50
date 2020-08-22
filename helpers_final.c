#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = ((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)) / 3;

            //grayscale changes applied
            image[i][j].rgbtRed = (int)roundf(average);
            image[i][j].rgbtGreen = (int)roundf(average);
            image[i][j].rgbtBlue = (int)roundf(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Variable declaration
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;

    //Iterate through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Algorithms
            sepiaRed = roundf((float)(image[i][j].rgbtRed * 0.393) + (float)(image[i][j].rgbtGreen * 0.769) + (float)
                              (image[i][j].rgbtBlue * 0.189));
            sepiaGreen = roundf((float)(image[i][j].rgbtRed * 0.349) + (float)(image[i][j].rgbtGreen * 0.686) + (float)
                                (image[i][j].rgbtBlue * 0.168));
            sepiaBlue = roundf((float)(image[i][j].rgbtRed * 0.272) + (float)(image[i][j].rgbtGreen * 0.534) + (float)
                               (image[i][j].rgbtBlue * 0.131));

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }

    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp_1;
    int temp_2;
    int temp_3;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp_1 = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - (j + 1)].rgbtRed;
            image[i][width - (j + 1)].rgbtRed = temp_1;

            temp_2 = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - (j + 1)].rgbtGreen;
            image[i][width - (j + 1)].rgbtGreen = temp_2;

            temp_3 = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - (j + 1)].rgbtBlue;
            image[i][width - (j + 1)].rgbtBlue = temp_3;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make a copy for computation.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    //loop through each pixel
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            float count = 0;
            float r = 0, g = 0, b = 0;

            //loop through each pixel in 3 x 3 grids within the image.
            for (int c = 0; c < 3; c++)
            {
                for (int d = 0; d < 3; d++)
                {
                    //find pixel and calculation
                    if ((m + c - 1 >= 0 && m + c - 1 < height) && (n + d - 1 >= 0 && n + d - 1 < width))
                    {
                        r = r + (float)copy[m + c - 1][n + d - 1].rgbtRed;
                        g = g + (float)copy[m + c - 1][n + d - 1].rgbtGreen;
                        b = b + (float)copy[m + c - 1][n + d - 1].rgbtBlue;
                        count++;
                    }
                }
            }

            //application
            image[m][n].rgbtRed = (int)roundf(r / count);
            image[m][n].rgbtGreen = (int)roundf(g / count);
            image[m][n].rgbtBlue = (int)roundf(b / count);
        }
    }
}
