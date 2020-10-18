// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Make the word lowercase
    char lower_word[strlen(word)];
    strcpy(lower_word, word);
    for (int i = 0; lower_word[i] != '\0'; i++)
    {
        lower_word[i] = tolower(lower_word[i]);
    }

    // Compare word to each words in right bucket
    // Returns true if the word is in the bucket else false
    int key = hash(word);
    if (table[key] != NULL)
    {
        for (node *node_pointer = table[key]; node_pointer != NULL; node_pointer = node_pointer -> next)
        {
            if (strcmp(node_pointer -> word, lower_word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Takes a word
    // Returns value corresponding to that word
    int value = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        value += tolower(word[i]);
    }
    return value % N;
}

bool is_loaded = false;
int words_number = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open file
    FILE *f = fopen(dictionary, "r");
    // Check if file exist
    if (f == NULL)
    {
        printf("No file named %c\n", *dictionary);
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char tmp_word[LENGTH + 1];

    // Create temporary node
    while (fscanf(f, "%s\n", tmp_word) != EOF)
    {
        node *tmp_node = malloc(sizeof(node));
        strcpy(tmp_node -> word, tmp_word);

        // Define appropriate bucket
        int key = hash(tmp_word);
        // If key does not exist (empty bucket)
        if (table[key] == NULL)
        {
            tmp_node -> next = NULL;
            table[key] = tmp_node;
        }

        else
        {
            tmp_node -> next = table[key];
            table[key] = tmp_node;
        }
        words_number ++;
    }
    // Close file
    fclose(f);
    is_loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (is_loaded)
    {
        return words_number;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Free memory
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *pointer = table[i];
            while (pointer != NULL)
            {
                node *previous_pointer = pointer;
                pointer = pointer->next;
                free(previous_pointer);
            }
        }
    }
    return true;
}
