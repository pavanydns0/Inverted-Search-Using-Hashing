/*
 * FILE NAME   : save_database.c
 * DESCRIPTION : This file contains the function to save the inverted
 *               index database into a file. The database is written
 *               in a structured format so it can be reloaded later.
 */

#include "inverted.h"

/*
 * Function : save_database
 * -----------------------------------------
 * Saves the entire inverted index (hash table)
 * into a file in a structured format.
 *
 * Format:
 * #index;word;file_count;filename;word_count;...#
 *
 * HT       : Hash table containing main nodes
 * filename : Output file name
 */
void save_database(M_node *HT[], char *filename)
{
    /* Check if file has .txt extension */
    char *res = strstr(filename, ".txt"); 
    FILE *fptr = NULL;                    

    if (res && !strcmp(res, ".txt"))      
        fptr = fopen(filename, "w");     // Open file in write mode
    else
    {
        printf("\nINFO : %s => Please use .txt extension\n", filename);
        return;
    }

    /* Check file creation */
    if (fptr == NULL) 
    {
        printf("\nERROR : Unable to create file\n");
        return;
    }

    /* Traverse hash table (27 indices) */
    for (int i = 0; i < 27; i++) 
    {
        /* If index contains data */
        if (HT[i] != NULL) 
        {
            M_node *main_temp = HT[i]; 

            /* Traverse main nodes (words) */
            while (main_temp)          
            {
                /* Write index, word, and file count */
                fprintf(fptr, "#%d;", i);
                fprintf(fptr, "%s;", main_temp->word);
                fprintf(fptr, "%d;", main_temp->file_count);

                /* Traverse sub nodes (file details) */
                S_node *sub_temp = main_temp->sub_link; 
                                                        
                while (sub_temp)
                {
                    /* Write file name and word count */
                    fprintf(fptr, "%s;%d;", sub_temp->filename, sub_temp->word_count);

                    sub_temp = sub_temp->sub_link; 
                }

                /* Mark end of one word entry */
                fprintf(fptr, "#\n");             

                main_temp = main_temp->main_link; 
            }
        }
    }

    /* Close file */
    fclose(fptr); 

    printf("\nINFO : Database saved successfully\n");
}