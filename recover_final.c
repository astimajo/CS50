#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //note for myself: for bool data type in C99 w/o utilizing the cs50 library.

int main(int argc, char *argv[])
{
    //return an error if usage is wrong.
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //open the file and assign to file pointer f.
    FILE *f = fopen("card.raw", "r");
    //initialize an image pointer
    FILE *image = NULL;
    //buffer for fread to check magic number iteration for jpeg
    unsigned char buffer[512];
    //counter for filename output
    int count = 0;
    //setting a normally false status identifier (no jpeg detection yet)
    bool test = false;

    //repeat iteration until end of file
    while (fread(buffer, 512, 1, f) == 1)
    {
        //buffer check for magic numbers
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //close image to move to next
            if (test == true)
            {
                fclose(image);
            }
            //found jpeg
            else
            {
                test = true;
            }

            //filename setting
            char file_name[8];
            sprintf(file_name, "%03i.jpg", count);
            image = fopen(file_name, "w");
            count++;
        }
        //writing the recovered image files to disk.
        if (test == true)
        {
            fwrite(&buffer, 512, 1, image);
        }
    }
    //close file pointer f
    fclose(f);
    //close image files.
    fclose(image);

    return 0;
}
