#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int height_max, spaces, hashtags;


    //ask user a number beetween 1 and 8
    do
    {
        height_max = get_int("Height: ");
    }
    while (height_max < 1 || height_max > 8);



    //declare counters for hashtags and spaces
    int height = 1;
    int height2 = height_max;

    //loop * height
    for (int h = 0; h < height_max; h++)
    {

        for(spaces = height2 -1; spaces > 0 ; spaces -= 1)
        {
            printf (" ");
        }

        for(hashtags = 0; hashtags < height; hashtags +=1)
        {
            printf ("#");
        }


        //separation of the 2 pyramids
        printf("  ");


        //second pyramid
        for(hashtags = 0; hashtags < height; hashtags +=1)
        {
            printf ("#");
        }


    //increase hashtag and decrease spaces
    height += 1;
    height2 -= 1;

    //next lign of the pyramid
    printf ("\n");
    }
}