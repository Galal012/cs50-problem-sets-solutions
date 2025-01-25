#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCKSIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover input.raw\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Can't open file\n");
        return 1;
    }

    uint8_t buffer[BLOCKSIZE];

    FILE *img;

    int found = 0, number = 0;

    while (fread(buffer, sizeof(uint8_t), BLOCKSIZE, card) == BLOCKSIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (found)
                fclose(img);
            else
                found = 1;

            char *filename = malloc(8 * sizeof(char));
            sprintf(filename, "%03i.jpg", number);

            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Can't open file\n");
                return 1;
            }

            fwrite(buffer, sizeof(uint8_t), BLOCKSIZE, img);

            free(filename);

            number++;
        }
        else if (found)
            fwrite(buffer, sizeof(uint8_t), BLOCKSIZE, img);
    }

    fclose(img);
    fclose(card);
}
