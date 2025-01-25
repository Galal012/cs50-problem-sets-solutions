#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int values[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    int points1 = 0, points2 = 0;

    for (int i = 0; i < strlen(p1); i++)
    {
        if (p1[i] >= 'a' && p1[i] <= 'z')
        {
            points1 += values[p1[i] - 'a'];
        }
        else if (p1[i] >= 'A' && p1[i] <= 'Z')
        {
            points1 += values[p1[i] - 'A'];
        }
    }

    for (int i = 0; i < strlen(p2); i++)
    {
        if (p2[i] >= 'a' && p2[i] <= 'z')
        {
            points2 += values[p2[i] - 'a'];
        }
        else if (p2[i] >= 'A' && p2[i] <= 'Z')
        {
            points2 += values[p2[i] - 'A'];
        }
    }

    if (points1 > points2)
        printf("Player 1 wins!\n");
    else if (points1 < points2)
        printf("Player 2 wins!\n");
    else
        printf("Tie!\n");

    return 0;
}
