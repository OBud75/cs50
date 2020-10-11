#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    // check if argc = 2
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    // check if file exist
    if (f == NULL)
    {
        printf("No file named ");
        printf("%c\n", *argv[1]);
        return 2;
    }

    // define block size, outfile, file index
    BYTE block[512];
    FILE *image;
    int image_index = 0;
    // boolean is the block start of a new file
    bool adding_to_same_file = true;

    // check each 512 byte block, while block is not jpeg, add them to file
    while (fread(block, 512, 1, f))
    {
        // if the block checked is start of a new JPEG
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] &0xf0) == 0xe0)
        {
            // close previous file if we start a new one
            if (!adding_to_same_file)
            {
                fclose(image);
            }
            else
            {
                adding_to_same_file = false;
            }

            // create file
            char image_number[8];
            sprintf(image_number, "%03i.jpg", image_index++);
            image = fopen(image_number, "w");
            // quit if image does not exist
            if (image == NULL)
            {
                return 3;
            }
            fwrite(block, 512, 1, image);
        }

        // if the block is not start of a new JPEG, we add the block to same file
        else if (adding_to_same_file)
        {
            fwrite(block, 512, 1, image);
        }
        adding_to_same_file = true;
    }
    fclose(image);
    fclose(f);
}
