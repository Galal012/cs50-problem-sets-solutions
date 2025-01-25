#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
        int blocks = i, spaces = height - i;
        while (spaces--)
        {
            printf(" ");
        }
        for (int j = 0; j < blocks; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int j = 0; j < blocks; j++)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}
