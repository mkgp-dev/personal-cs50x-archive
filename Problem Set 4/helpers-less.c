#include "helpers.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // @mkgp-dev: Make loop to grab height and width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Define rgb to get average
            float r = image[i][j].rgbtRed;
            float g = image[i][j].rgbtGreen;
            float b = image[i][j].rgbtBlue;

            // Simple average computation
            int avrg = round((r + g + b) / 3.0);

            // Apply average to rgb
            image[i][j].rgbtRed = avrg;
            image[i][j].rgbtGreen = avrg;
            image[i][j].rgbtBlue = avrg;
        }
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // @mkgp-dev: Make loop to grab height and width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Define rgb
            float r = image[i][j].rgbtRed;
            float g = image[i][j].rgbtGreen;
            float b = image[i][j].rgbtBlue;

            // Simple sepia computation
            int sR = round(.393 * r + .769 * g + .189 * b);
            int sG = round(.349 * r + .686 * g + .168 * b);
            int sB = round(.272 * r + .534 * g + .131 * b);

            // Rule: Ensure the resulting value is no larger than 255
            sR = (sR < 0) ? 0 : (sR > 255) ? 255 : sR;
            sG = (sG < 0) ? 0 : (sG > 255) ? 255 : sG;
            sB = (sB < 0) ? 0 : (sB > 255) ? 255 : sB;

            // Apply computation to rgb
            image[i][j].rgbtRed = sR;
            image[i][j].rgbtGreen = sG;
            image[i][j].rgbtBlue = sB;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // @mkgp-dev: Make loop to grab height and width divided by 2
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Basic swap
            RGBTRIPLE tmp = image[i][j];
            // This should fix when it overlaps the given loop
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy
    RGBTRIPLE img[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[i][j] = image[i][j];
        }
    }

    // Make a 3x3 grid computation
    // Thank you @abotishere6757 from discord-cs50 for the idea
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float r = 0, g = 0, b = 0, count = 0;

            for (int gridh = -1; gridh <= 1; gridh++)
            {
                for (int gridw = -1; gridw <= 1; gridw++)
                {
                    int h = i + gridh;
                    int w = j + gridw;

                    if (h >= 0 && h < height && w >= 0 && w < width)
                    {
                        r += img[h][w].rgbtRed;
                        g += img[h][w].rgbtGreen;
                        b += img[h][w].rgbtBlue;
                        count++;
                    }
                }
            }

            // Apply blur to image
            image[i][j].rgbtRed = round(r / count);
            image[i][j].rgbtGreen = round(g / count);
            image[i][j].rgbtBlue = round(b / count);
        }
    }
}
