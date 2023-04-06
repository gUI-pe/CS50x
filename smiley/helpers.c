#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0;
    int j = 0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (image[i][j].rgbtBlue == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtRed == 0x00)
            {
                image[i][j].rgbtGreen = 0xff;
                image[i][j].rgbtRed = 0xa4;
            }
        }
    }
}
