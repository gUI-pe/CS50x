#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            float total = 0;
            total += round(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed);
            image[i][j].rgbtBlue = round(total / 3);
            image[i][j].rgbtGreen = round(total / 3);
            image[i][j].rgbtRed = round(total / 3);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;
    BYTE originalBlue = 0;
    BYTE originalGreen = 0;
    BYTE originalRed = 0;
    int Blue = 0;
    int Green = 0;
    int Red = 0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            originalBlue = image[i][j].rgbtBlue;
            originalGreen = image[i][j].rgbtGreen;
            originalRed = image[i][j].rgbtRed;

            Red = round((.393 * originalRed) + (.769 * originalGreen) + (.189 * originalBlue));
            Green = round((.349 * originalRed) + (.686 * originalGreen) + (.168 * originalBlue));
            Blue = round((.272 * originalRed) + (.534 * originalGreen) + (.131 * originalBlue));
            if (Red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = Red;
            }
            if (Blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = Blue;
            }
            if (Green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = Green;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    //making the copy an actual copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0, inverse = width - 1; j < width; j++)
        {
            image[i][j] = copy[i][inverse];
            inverse --;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    //making the copy an actual copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // main code
    float totalr = 0;
    float totalg = 0;
    float totalb = 0;
    int divisor = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int iup = i - 1; iup <= i + 1; iup++)
            {
                for (int jback = j - 1; jback <= j + 1; jback++)
                {
                    if (jback < width && iup < height && jback >= 0 && iup >= 0)
                    {
                        totalr += copy[iup][jback].rgbtRed;
                        totalg += copy[iup][jback].rgbtGreen;
                        totalb += copy[iup][jback].rgbtBlue;
                        divisor++;
                    }
                }
            }
            image[i][j].rgbtRed = round(totalr / divisor);
            image[i][j].rgbtGreen = round(totalg / divisor);
            image[i][j].rgbtBlue = round(totalb / divisor);
            totalr = 0;
            totalg = 0;
            totalb = 0;
            divisor = 0;
        }
    }
    return;
}
