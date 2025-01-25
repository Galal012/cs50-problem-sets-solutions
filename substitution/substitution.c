#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        if (strlen(key) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            bool valid = 1, visited[26] = {};
            for (int i = 0; i < 26; i++)
            {
                if (key[i] >= 'a' && key[i] <= 'z')
                {
                    int position = key[i] - 'a';
                    if (visited[position])
                        valid = 0;
                    else
                        visited[position] = 1;
                }
                else if (key[i] >= 'A' && key[i] <= 'Z')
                {
                    int position = key[i] - 'A';
                    if (visited[position])
                        valid = 0;
                    else
                        visited[position] = 1;
                }
                else
                    valid = 0;
            }

            if (!valid)
            {
                printf("Please enter a valid key with 26 distinct alphabets.\n");
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
                        int position = plain[i] - 'a';
                        char character = key[position];
                        if (character < 'a')
                            character += 'a' - 'A';
                        printf("%c", character);
                    }
                    else if (plain[i] >= 'A' && plain[i] <= 'Z')
                    {
                        int position = plain[i] - 'A';
                        char character = key[position];
                        if (character >= 'a')
                            character -= 'a' - 'A';
                        printf("%c", character);
                    }
                    else
                        printf("%c", plain[i]);
                }
                printf("\n");
                return 0;
            }
        }
    }
}
