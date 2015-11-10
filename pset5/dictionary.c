/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// creating hash table
node* head[SIZE];

// dictionary size to return for size
int dsize = 0;

// find out where to sort word with hash function
int hashfunc(char* s)
{
    // variable to hold ascii value of box
    int slot = tolower(s[0]) - 'a';
    // returns it
    return slot % SIZE;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // create a temporary variable to store lowercase spellcheck
    char lower[LENGTH+1];
    
    // create variable storing length of word
    int len = strlen(word);
    
    // for size of word, lowercase each character in string
    for (int i = 0; i < len; i++)
    {
        lower[i] = tolower(word[i]);
    }
    // append null character to end of word
    lower[len] = '\0';
    
    // find the box where the word is stored
    int box = hashfunc(lower);
    
    // if box is empty return false (no word to check)
    if (head[box] == NULL)
    {
        return false;
    }
    // create a pointer that checks each word in that box
    node* pointer = head[box];
    
    // while not at the end of linked list
    while (pointer != NULL)
    {
        // if comparison of word and word stored are the same, return true
        if (strcmp(lower, pointer->word) == 0)
        {
            return true;
        }
        // move on to next comparison
        pointer = pointer->next;
    }
    // return false if word not in dictionary
    return false;
}



/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // make all hash table boxes point to NULL
    for (int i = 0; i < SIZE; i++)
    {
        head[i] = NULL;
    }  
    // word to store dictionary text into    
    char word[LENGTH+1];
    // open dictionary, store in file
    FILE* file = fopen(dictionary,"r");
    
    // if null, return false
    if(file == NULL)
    {
        return false;
    }
    
    
    // while not at end of file
    while (fscanf(file, "%s\n", word) != EOF)
    {
        // increment size of dictionary
        dsize += 1;
        
        // allocate memory into new node
        node* new_node = malloc(sizeof(node));
        
        // copy word into new node
        strcpy(new_node->word,word);
        
        // hashfunc into int box (location of that word)
        int box = hashfunc(word);
        
        // if empty at first
        if (head[box] == NULL)
        {
            // box is equal to new node
            head[box] = new_node;
            // point to null
            new_node->next = NULL;
        }
        // else if not empty
        else
        {
            // new node next points to what head[box] points to so we dont lose it
            new_node->next = head[box];
            // head box points to new node
            head[box] = new_node;
        }
        
        
    }
    // close our dictionary file
    fclose(file);
    // return true :)
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
   
    // if dictionary loaded, return size
    if (dsize > 0)
    {
        return dsize;
    }
    // if not loaded, fail
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // start at first box
    int box = 0;
    // while box is less than size of hash table
    while (box<SIZE)
    {
        // if box is empty, move on
        if (head[box] == NULL)
        {
            box += 1;
        }
        // else
        else
        {
            // while box is not null
            while (head[box] != NULL)
            {
                // make a pointer to start going through list
                node* pointer = head[box];
                // move along linked list
                head[box] = pointer->next;
                // free each list
                free(pointer);
            }
            // when null, move on to next box
            box += 1;
        }
    }
    // return true if possible
    return true;
}
