void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Re-using blur mechanism
    // Thank you @rmendesp from discord-cs50 for the idea
    RGBTRIPLE img[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[i][j] = image[i][j];
        }
    }

    // Sobel operation formula
    // https://en.wikipedia.org/wiki/Sobel_operator
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Apply Sobel operation
            int Gx_r = 0, Gx_g = 0, Gx_b = 0;
            int Gy_r = 0, Gy_g = 0, Gy_b = 0;

            for (int gridh = -1; gridh <= 1; gridh++)
            {
                for (int gridw = -1; gridw <= 1; gridw++)
                {
                    int h = i + gridh;
                    int w = j + gridw;

                    if (h >= 0 && h < height && w >= 0 && w < width)
                    {
                        // Gx area
                        Gx_r += img[h][w].rgbtRed * Gx[gridh + 1][gridw + 1];
                        Gx_g += img[h][w].rgbtGreen * Gx[gridh + 1][gridw + 1];
                        Gx_b += img[h][w].rgbtBlue * Gx[gridh + 1][gridw + 1];

                        // Gy area
                        Gy_r += img[h][w].rgbtRed * Gy[gridh + 1][gridw + 1];
                        Gy_g += img[h][w].rgbtGreen * Gy[gridh + 1][gridw + 1];
                        Gy_b += img[h][w].rgbtBlue * Gy[gridh + 1][gridw + 1];
                    }
                }
            }

            // Define calculations
            int eR = round(sqrt(Gx_r * Gx_r + Gy_r * Gy_r));
            int eG = round(sqrt(Gx_g * Gx_g + Gy_g * Gy_g));
            int eB = round(sqrt(Gx_b * Gx_b + Gy_b * Gy_b));

            // Rule: rounded to the nearest integer and capped at 255
            image[i][j].rgbtRed = (eR > 255) ? 255 : eR;
            image[i][j].rgbtGreen = (eG > 255) ? 255 : eG;
            image[i][j].rgbtBlue = (eB > 255) ? 255 : eB;
        }
    }
}
