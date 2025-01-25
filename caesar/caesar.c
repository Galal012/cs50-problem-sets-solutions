#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        bool ok = 1;
        string key = argv[1];
        int number = 0;
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            if (key[i] < '0' || key[i] > '9')
                ok = 0;
            else
            {
                number *= 10;
                number += key[i] - '0';
            }
        }

        if (!ok)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            string plain = get_string("plaintext:  ");
            printf("ciphertext: ");
            for (int i = 0, n = strlen(plain); i < n; i++)
            {
                if (plain[i] >= 'a' && plain[i] <= 'z')
                {
                    int position = plain[i] - 'a' + number;
                    position %= 26;
                    printf("%c", position + 'a');
                }
                else if (plain[i] >= 'A' && plain[i] <= 'Z')
                {
                    int position = plain[i] - 'A' + number;
                    position %= 26;
                    printf("%c", position + 'A');
                }
                else
                    printf("%c", plain[i]);
            }
            printf("\n");
            return 0;
        }
    }
}
