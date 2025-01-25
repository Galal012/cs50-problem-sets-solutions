#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];

            int average = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
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
            int cur_blue = image[i][j].rgbtBlue;
            int cur_green = image[i][j].rgbtGreen;
            int cur_red = image[i][j].rgbtRed;

            int new_blue = round(0.272 * cur_red + 0.534 * cur_green + 0.131 * cur_blue);
            int new_green = round(0.349 * cur_red + 0.686 * cur_green + 0.168 * cur_blue);
            int new_red = round(0.393 * cur_red + 0.769 * cur_green + 0.189 * cur_blue);

            if (new_blue > 255)
                new_blue = 255;
            if (new_green > 255)
                new_green = 255;
            if (new_red > 255)
                new_red = 255;

            image[i][j].rgbtBlue = new_blue;
            image[i][j].rgbtGreen = new_green;
            image[i][j].rgbtRed = new_red;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            temp[i][j] = image[i][j];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sum_red = 0, sum_green = 0, sum_blue = 0, cnt = 0;

            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if (x >= 0 && y >= 0 && x < height && y < width)
                    {
                        sum_red += temp[x][y].rgbtRed;
                        sum_green += temp[x][y].rgbtGreen;
                        sum_blue += temp[x][y].rgbtBlue;

                        cnt++;
                    }
                }
            }

            image[i][j].rgbtRed = round(sum_red / cnt);
            image[i][j].rgbtGreen = round(sum_green / cnt);
            image[i][j].rgbtBlue = round(sum_blue / cnt);
        }
    }

    return;
}
