// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int cnt = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int idx = hash(word);
    node *list = table[idx];
    while (list != NULL)
    {
        if (strcasecmp(word, list->word) == 0)
            return true;
        list = list->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Can't open file\n");
        return false;
    }

    char *word = malloc((LENGTH + 1) * sizeof(char));
    if (word == NULL)
    {
        printf("Can't allocate memory\n");
        return false;
    }

    // initialize the hash table with NULL
    for (int i = 0; i < N; i++)
        table[i] = NULL;

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Can't allocate memory\n");
            return false;
        }

        cnt++;

        strcpy(n->word, word);

        int idx = hash(word);

        n->next = table[idx];

        table[idx] = n;
    }
    free(word);
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return cnt;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i], *tmp = table[i];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }

    return true;
}
