// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"



// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;
//counts how many words in dictionary
int words = 0;

// Hash table
node *table[N];



// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    int a = strlen(word);

    //copy words to another array
    char word_cp[LENGTH + 1];

    //incrementation for case insensitivity issues a while ago
    for (int i = 0; i < a; i++)
    {
        word_cp[i] = tolower(word[i]);
    }

    //NULL terminator to each word in copy to distinguish the end of each word
    word_cp[a] = '\0';

    int hash_index = hash(word_cp);

    node *cursor = table[hash_index];

    //keep searching the dictionary for words while cursor is not yet NULL
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word_cp) == 0)
        {
            return true;
        }
        //found, therefore move forward.
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}




//src for hash function = https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/ => (delipity)
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO

    char word[LENGTH + 1];
    //Open the dictionary file.
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }


    //Read the file.
    while (fscanf(file, "%s", word) != EOF)
    {
        //malloc for new nodes
        node *new_n = malloc(sizeof(node));
        if (new_n == NULL)
        {
            free(new_n);
            return false;
        }
        //add word to node
        strcpy(new_n->word, word);

        //hash function
        int hash_index = hash(word);

        //check if occupied
        if (table[hash_index] == NULL)
        {
            new_n->next = NULL; //note to myself: fixed. set next to null first as it is still pointing to nothing.
            table[hash_index] = new_n;
            words++;
        }
        else
        {
            new_n->next = table[hash_index];
            table[hash_index] = new_n;
            words++;
        }
    }
    fclose(file);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO

    //iterate each node to delete each.
    for (int i = 0; i < N; i++)
    {
        //while table value != NULL continue to free N sized memory usage.
        if (table[i] != NULL)
        {
            node *cursor = table[i];
            //while cursor is not yet pointing to NULL continue freeing up the nodes.
            while (cursor != NULL)
            {
                node *tmp = cursor;
                cursor = tmp->next;
                free(tmp);
            }
        }
    }
    return true;
}

//notes to myself: strcasecmp is similar to strcmp but eliminates the case issues(string.h)