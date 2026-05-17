/*
 * FILE NAME   : search_database.c
 * DESCRIPTION : This file contains the function to search a given word
 *               in the inverted index database and display its details.
 */

#include "inverted.h"

/*
 * Function : search_database
 * -----------------------------------------
 * Searches for a given word in the hash table.
 *
 * Steps:
 * 1. Find index using hash function
 * 2. Traverse main node list at that index
 * 3. Compare words
 * 4. If found, display details
 * 5. If not found, print message
 *
 * HT   : Hash table
 * word : Word to be searched
 */
void search_database(M_node *HT[], char *word)
{
    /* Get index based on first character */
    int index = get_index(word); 

    /* Traverse main nodes at that index */
    while (HT[index])            
    {
        /* Compare stored word with input word */
        if (!strcmp(HT[index]->word, word))
        {
            printf("===============================================\n");
            printf("FOUND AT : \n");

            /* Display index and word details */
            printf("%-10s : [%d]\n", "INDEX", index);                      
            printf("%-10s : %-15s\n", "WORD", HT[index]->word);            
            printf("%-10s : %-15d\n", "FILECOUNT", HT[index]->file_count);

            /* Traverse sub nodes (file details) */
            S_node *sub_temp = HT[index]->sub_link;                        

            while (sub_temp)                                               
            {
                printf("%-10s : %-10s || %-10s : %-15d\n",
                       "FILENAME", sub_temp->filename,
                       "WORDCOUNT", sub_temp->word_count);

                sub_temp = sub_temp->sub_link; 
            }

            printf("===============================================\n");

            return; /* Exit after successful search */
        }

        /* Move to next main node */
        HT[index] = HT[index]->main_link; 
    }

    /* Word not found case */
    printf("\nINFO : WORD IS NOT FOUND IN THE DATABASE\n");
}