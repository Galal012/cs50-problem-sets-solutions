#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string number;
    bool valid;

    do
    {
        number = get_string("Number: ");
        valid = 1;
        for (int i = 0; i < strlen(number); i++)
        {
            if (number[i] < '0' || number[i] > '9')
            {
                valid = 0;
            }
        }
    }
    while (!valid);

    if (strlen(number) != 15 && strlen(number) != 13 && strlen(number) != 16)
    {
        printf("INVALID\n");
    }
    else
    {
        int sum = 0;
        for (int i = 0; i < strlen(number); i++)
        {
            if ((strlen(number) - i) % 2 == 0)
            {
                int num = 2 * (number[i] - '0');
                while (num)
                {
                    sum += num % 10;
                    num /= 10;
                }
            }
            else
            {
                sum += number[i] - '0';
            }
        }

        if (sum % 10 == 0)
        {
            if (strlen(number) == 15 && number[0] == '3' && (number[1] == '4' || number[1] == '7'))
            {
                printf("AMEX\n");
            }
            else if ((strlen(number) == 13 || strlen(number) == 16) && number[0] == '4')
            {
                printf("VISA\n");
            }
            else if (strlen(number) == 16 && number[0] == '5' &&
                     (number[1] == '1' || number[1] == '2' || number[1] == '3' ||
                      number[1] == '4' || number[1] == '5'))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }

    return 0;
}
