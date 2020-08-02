#include <cs50.h> 
#include <stdio.h>

int get_height_int(void); //the rest of the function is hidden under the main section.

int main(void)
{
    int height = get_height_int();
    //Integrating the user input Function to the pyramid.

    for (int row = 0; row < height; row++) //row addition...(phew)
    {
        int col;
        //Left section of pyramid.
        for (col = 0; col < (height - row) - 1; col++) //spacing
        {
            printf(" ");
        }
        for (int hash = 0; hash < (height) - col; hash++) 
        {
            printf("#");
        }
        // 2 spaces (dots) middle of 2 pyramids.
        for (int space = 0; space < 2; space++)
        {
            printf(" ");
        }
        //Right section of pyramid.
        for (int hash = 0; hash < (height) - col; hash++)
        {
            printf("#");
        }
        
        //Solution to previously not working vertical issue. (allows hashes to execute downwards per row) as per pyrbar program.
        printf("\n");
    }
}



//use this do while loop for Mario Comfortable.
//work on # program and integrate the do while loop.
int get_height_int(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);
    return height;

}


