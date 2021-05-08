// Implements a dictionary's functionality

#include <stdbool.h>
#include<stdio.h>
#include<strings.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH+1) *'Z';

// Hash table
node *table[N];

// for determing size of total words

 int word_counter=0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int n =hash(word);
    node *check=table[n];
    while(check!=NULL)
    {
        if(strcasecmp(check->word,word)==0)
        {
            return true;
        }

        check= check->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum =0;

    for (int i=0;i<strlen(word);i++)
    {
       sum+=tolower(word[i]);
    }


    return sum % N;

}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE *f = fopen(dictionary ,"r");
    if (f==NULL)
    {
        printf("could not load");
        return false;
    }
    // buffer for storing  words from dictionary
     char buffer[LENGTH +1];

     while (fscanf(f,"%s",buffer)!=EOF)
     {

         node *n = malloc(sizeof(node));

         if(n==NULL)
         {
             printf("unable to allocate memory");
             return false;
         }

         strcpy(n->word,buffer);
         n->next=NULL;

         int h= hash(n->word);
         node *head =table[h];

         if (head==NULL)
         {
             table[h]=n;
         }
         else
         {
             n->next=table[h];
             table[h]=n;
         }

       word_counter++;
     }
 fclose(f);
 return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *head =NULL;
    node *cursor=head;

    while(cursor != NULL)
    {
        node* temp =cursor;
        cursor=cursor->next;
        free(temp);
    }

    return true;
}
