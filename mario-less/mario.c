#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // prompting the user for the height
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0);

    // printing the pyramid
    for (int i = 1; i <= height; i++)
    {
        // printing each row
        int blocks = i, spaces = height - i;

        // printing the spaces first
        while (spaces--)
        {
            printf(" ");
        }

        // finally, printing the blocks
        while (blocks--)
        {
            printf("#");
        }

        // moving the cursor to the next line
        printf("\n");
    }
}
