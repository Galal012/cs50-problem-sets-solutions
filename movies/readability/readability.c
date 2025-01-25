#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");

    double letters = 0, words = 0, sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
            letters++;
        if (text[i] == ' ' || i == n - 1)
            words++;
        if (text[i] == '?' || text[i] == '!' || text[i] == '.')
            sentences++;
    }

    double idx = 0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8;

    int answer = round(idx);

    if (answer >= 16)
        printf("Grade 16+\n");
    else if (answer < 1)
        printf("Before Grade 1\n");
    else
        printf("Grade %i\n", answer);
}
