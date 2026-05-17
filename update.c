/*
 * FILE NAME   : update_database.c
 * DESCRIPTION : This file contains functions to:
 *               1. Update the inverted index database by adding a new file
 *               2. Insert a file at the beginning of the file linked list
 */

#include "inverted.h"

/*
 * Function : update_database
 * -----------------------------------------
 * Updates the existing database by adding a new file.
 *
 * Steps:
 * 1. Accept filename from user
 * 2. Validate file (extension, existence, non-empty)
 * 3. Check for duplicate file entry
 * 4. Insert file into linked list
 * 5. Recreate database with updated file list
 *
 * HT   : Hash table
 * head : Pointer to file linked list
 *
 * return : SUCCESS / FAILURE
 */

/* Function to update database with a new file */
int update_database(M_node *HT[], F_node **head)
{ 
    char filename[25];

    // Ask user for filename
    printf("Enter the filename you want to update : ");
    scanf("%s", filename);

    // Check for file extension
    char *res = strstr(filename, ".");

    if(res)
    {
        // Check if file is .txt
        if (strcmp(res, ".txt") == 0)
        {
            // Try to open file
            FILE *fptr = fopen(filename, "r"); 

            if (fptr)
            {
                // Check file size
                fseek(fptr, 0, SEEK_END);
                unsigned long int size = ftell(fptr);
                rewind(fptr); 

                // Check if file is not empty
                if (size)
                {
                    // Check for duplicate file
                    if (check_duplicates(*head, filename) == FAILURE)
                    {
                        // Insert file at beginning of list
                        if (insert_first(head, filename) == SUCCESS)
                        {
                            printf("\nINFO : Successful : Inserting file name %s into file linked list\n", filename);
                        }
                    }
                    else
                    {
                        // Duplicate file case
                        printf("\nINFO : %s => This file is repeated, so it will not store into the sll\n", filename);
                        printf("\nINFO : Database update failed\n");
                        return FAILURE;
                    }
                }
                else
                {
                    // Empty file case
                    printf("\nINFO : %s => This file is empty\n", filename);
                    printf("\nINFO : Database update failed\n");
                    return FAILURE;
                }
            }
            else
            {
                // File not found
                printf("\nINFO : %s => This file does not exist in the current directory\n", filename);
                printf("\nINFO : Database update failed\n");
                return FAILURE;
            }
        }
        else
        {
            // Invalid extension
            printf("\nINFO : %s => This file is not .txt\n", filename);
            printf("\nINFO : Database update failed\n");
            return FAILURE;
        }
    }
    else
    {
        // No extension case
        printf("\nINFO : %s => This file has without extension\n", filename);
        printf("\nINFO : Database update failed\n");
        return FAILURE;
    }

    // Print updated file list
    print_filenames(*head);

    // Recreate database with updated file
    create_database(HT, *head);

    printf("\nINFO : DATABASE UPDATED SUCCESSFULLY\n");
}