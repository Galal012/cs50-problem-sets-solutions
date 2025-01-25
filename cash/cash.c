#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int owed;

    do
    {
        owed = get_int("Change owed: ");
    }
    while (owed < 0);

    int answer = 0;

    answer += owed / 25;
    owed -= owed / 25 * 25;

    answer += owed / 10;
    owed -= owed / 10 * 10;

    answer += owed / 5;
    owed -= owed / 5 * 5;

    answer += owed;

    printf("%i\n", answer);
}
