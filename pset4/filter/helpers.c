#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
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
            int new_red = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int new_green = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int new_blue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            //check if new color not > 255 and change it
            if (new_red <= 255)
            {
                image[i][j].rgbtRed = new_red;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
            if (new_green <= 255)
            {
                image[i][j].rgbtGreen = new_green;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if (new_blue <= 255)
            {
                image[i][j].rgbtBlue = new_blue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_pixel[height][width];
    //store reversed pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_pixel[i][j] = image[i][width -1 -j];
        }
    }
    //change old by new pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_pixel[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_pixel[height][width];

    //corners
    new_pixel[0][0].rgbtRed = round((image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed) / 4.0);
    new_pixel[0][0].rgbtGreen = round((image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen) / 4.0);
    new_pixel[0][0].rgbtBlue = round((image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue) / 4.0);

    new_pixel[0][width].rgbtRed = round((image[0][width].rgbtRed + image[1][width].rgbtRed + image[0][width-1].rgbtRed + image[1][width-1].rgbtRed) / 4.0);
    new_pixel[0][width].rgbtGreen = round((image[0][width].rgbtGreen + image[1][width].rgbtGreen + image[0][width-1].rgbtGreen + image[1][width-1].rgbtGreen) / 4.0);
    new_pixel[0][width].rgbtBlue = round((image[0][width].rgbtBlue + image[1][width].rgbtBlue + image[0][width-1].rgbtBlue + image[1][width-1].rgbtBlue) / 4.0);

    new_pixel[height][0].rgbtRed = round((image[height][0].rgbtRed + image[height-1][0].rgbtRed + image[height][1].rgbtRed + image[height-1][1].rgbtRed) / 4.0);
    new_pixel[height][0].rgbtGreen = round((image[height][0].rgbtGreen + image[height-1][0].rgbtGreen + image[height][1].rgbtGreen + image[height-1][1].rgbtGreen) / 4.0);
    new_pixel[height][0].rgbtBlue = round((image[height][0].rgbtBlue + image[height-1][0].rgbtBlue + image[height][1].rgbtBlue + image[height-1][1].rgbtBlue) / 4.0);

    new_pixel[height][width].rgbtRed = round((image[height][width].rgbtRed + image[height-1][width].rgbtRed + image[height][width-1].rgbtRed + image[height-1][width-1].rgbtRed) / 4.0);
    new_pixel[height][width].rgbtGreen = round((image[height][width].rgbtGreen + image[height-1][width].rgbtGreen + image[height][width-1].rgbtGreen + image[height-1][width-1].rgbtGreen) / 4.0);
    new_pixel[height][width].rgbtBlue = round((image[height][width].rgbtBlue + image[height-1][width].rgbtBlue + image[height][width-1].rgbtBlue + image[height-1][width-1].rgbtBlue) / 4.0);

    //top and bottom borders
    for (int i = 1; i < width -1; i++)
    {
        new_pixel[0][i].rgbtRed = round((image[0][i].rgbtRed + image[0][i-1].rgbtRed + image[0][i+1].rgbtRed + image[1][i-1].rgbtRed + image[1][i].rgbtRed + image[1][i+1].rgbtRed) / 6.0);
        new_pixel[0][i].rgbtGreen = round((image[0][i].rgbtGreen + image[0][i-1].rgbtGreen + image[0][i+1].rgbtGreen + image[1][i-1].rgbtGreen + image[1][i].rgbtGreen + image[1][i+1].rgbtGreen) / 6.0);
        new_pixel[0][i].rgbtBlue = round((image[0][i].rgbtBlue + image[0][i-1].rgbtBlue + image[0][i+1].rgbtBlue + image[1][i-1].rgbtBlue + image[1][i].rgbtBlue + image[1][i+1].rgbtBlue) / 6.0);
    }
    for (int i = 1; i < width -1; i++)
    {
        new_pixel[height][i].rgbtRed = round((image[height][i].rgbtRed + image[height][i-1].rgbtRed + image[height][i+1].rgbtRed + image[height-1][i-1].rgbtRed + image[height-1][i].rgbtRed + image[height-1][i+1].rgbtRed) / 6.0);
        new_pixel[height][i].rgbtGreen = round((image[height][i].rgbtGreen + image[height][i-1].rgbtGreen + image[height][i+1].rgbtGreen + image[height-1][i-1].rgbtGreen + image[height-1][i].rgbtGreen + image[height-1][i+1].rgbtGreen) / 6.0);
        new_pixel[height][i].rgbtBlue = round((image[height][i].rgbtBlue + image[height][i-1].rgbtBlue + image[height][i+1].rgbtBlue + image[height-1][i-1].rgbtBlue + image[height-1][i].rgbtBlue + image[height-1][i+1].rgbtBlue) / 6.0);
    }

    //left and right borders
    for (int i = 1; i < height -1; i++)
    {
        new_pixel[i][0].rgbtRed = round((image[i][0].rgbtRed + image[i-1][0].rgbtRed + image[i+1][0].rgbtRed + image[i][1].rgbtRed + image[i-1][1].rgbtRed + image[i+1][1].rgbtRed) / 6.0);
        new_pixel[i][0].rgbtGreen = round((image[i][0].rgbtGreen + image[i-1][0].rgbtGreen + image[i+1][0].rgbtGreen + image[i][1].rgbtGreen + image[i-1][1].rgbtGreen + image[i+1][1].rgbtGreen) / 6.0);
        new_pixel[i][0].rgbtBlue = round((image[i][0].rgbtBlue + image[i-1][0].rgbtBlue + image[i+1][0].rgbtBlue + image[i][1].rgbtBlue + image[i-1][1].rgbtBlue + image[i+1][1].rgbtBlue) / 6.0);
    }
    for (int i = 1; i < height -1; i++)
    {
        new_pixel[i][width].rgbtRed = round((image[i][width].rgbtRed + image[i-1][width].rgbtRed + image[i+1][width].rgbtRed + image[i][width-1].rgbtRed + image[i-1][width-1].rgbtRed + image[i+1][width-1].rgbtRed) / 6.0);
        new_pixel[i][width].rgbtGreen = round((image[i][width].rgbtGreen + image[i-1][width].rgbtGreen + image[i+1][width].rgbtGreen + image[i][width-1].rgbtGreen + image[i-1][width-1].rgbtGreen + image[i+1][width-1].rgbtGreen) / 6.0);
        new_pixel[i][width].rgbtBlue = round((image[i][width].rgbtBlue + image[i-1][width].rgbtBlue + image[i+1][width].rgbtBlue + image[i][width-1].rgbtBlue + image[i-1][width-1].rgbtBlue + image[i+1][width-1].rgbtBlue) / 6.0);
    }


    //inside of the picture
    for (int i = 1; i < width -1; i++)
    {
        for (int j = 1; j < height -1; j++)
        {
            new_pixel[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j+1].rgbtRed) / 9.0);
            new_pixel[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j+1].rgbtGreen) / 9.0);
            new_pixel[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j+1].rgbtBlue) / 9.0);
        }
    }

    //change old pixel by new
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_pixel[i][j];
        }
    }
    return;
}
