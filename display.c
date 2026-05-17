/*
 * FILE NAME   : display_database.c
 * DESCRIPTION : This file contains the function to display the
 *               inverted index database in a tabular format.
 */

#include "inverted.h"

/*
 * Function : display_database
 * -----------------------------------------
 * Displays the contents of the hash table in a structured table format.
 *
 * Structure:
 * INDEX | WORD | FILECOUNT | FILENAME | WORDCOUNT
 *
 * Steps:
 * 1. Traverse hash table (0–26)
 * 2. Traverse main nodes (words)
 * 3. Traverse sub nodes (file details)
 * 4. Print formatted output
 *
 * HT : Hash table
 */
void display_database(M_node *HT[])
{
    /* Print table header */
    printf("|----------------------------------------------------------------------|\n");
    printf("|%-15s%-15s%-15s%-15s%-15s\n",
           "INDEX","WORD","FILECOUNT","FILENAME","WORDCOUNT |");
    printf("|----------------------------------------------------------------------|\n");

    /* Traverse all 27 hash indices */
    for(int i = 0; i < 27; i++)
    {
        /* Check if index has data */
        if(HT[i] != NULL)
        {
            M_node *main_temp = HT[i];        

            /* Traverse main nodes (each word) */
            while(main_temp)
            {
                /* Traverse sub nodes (file details) */
                S_node *sub_temp = main_temp->sub_link;  

                while(sub_temp)                      
                {
                    /* First sub-node → print full row (index + word info) */
                    if(sub_temp == main_temp->sub_link)
                    {
                        printf("|%-15d", i);             
                        printf("%-15s%-15d",
                               main_temp->word,
                               main_temp->file_count);   
                    }
                    /* Remaining sub-nodes → skip repeating word info */
                    else
                    {
                        printf("|%-15s", "");                               
                        printf("%-15s%-15s", "", "");                        
                    }

                    /* Print file name and word count */
                    printf("%-15s%-10d|\n",
                           sub_temp->filename,
                           sub_temp->word_count);    

                    sub_temp = sub_temp->sub_link;     
                }

                main_temp = main_temp->main_link;  
            }
        }
    }

    /* Print table footer */
    printf("|----------------------------------------------------------------------|\n");
}