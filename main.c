/*
------------------------------------------------------------
Author      : YDNS PAVAN
Project Name: Inverted Search (Inverted Index using Hashing)
Date        : 2026
------------------------------------------------------------

Description:

This project implements an Inverted Search system using 
Data Structures in C. The main goal of the project is to 
store and retrieve words efficiently from multiple text files.

The system uses a Hash Table (size 27) combined with 
Linked Lists to map words to the files in which they appear.

Working:
- Reads multiple .txt files
- Extracts words from each file
- Stores words in hash table using indexing (a–z)
- Each word is stored in a main node
- Each main node contains a sub linked list of file details
- Tracks:
    -> File name
    -> Word occurrence count

Features:
- Create database from input files
- Display database in structured format
- Search word and show file occurrences
- Save database into a file
- Update database with new file

Data Structures Used:
- Hash Table
- Singly Linked List (File List)
- Multi-level Linked List (Main + Sub nodes)

Applications:
- Search engines (basic concept)
- File indexing systems
- Text processing tools

------------------------------------------------------------
*/

#include "inverted.h"

/* 
 * Global flags to track database status
 * update_flag : Indicates whether database is updated
 * create_flag : Indicates whether database is created
 */
int update_flag = 0; 
int create_flag = 0; 

/*
 * Function : main
 * -------------------------
 * Entry point of the program.
 * Handles file validation, database creation, display,
 * saving, searching, and updating operations.
 *
 * argc : Argument count
 * argv : Argument vector (file names passed through command line)
 *
 * return : SUCCESS / FAILURE
 */

int main(int argc, char *argv[])
{
    /* Head pointer for file linked list */
    F_node *head = NULL; 

    /* Hash Table with 27 indices (a-z + special characters) */
    M_node *HT[27];         

    /* Initialize hash table with NULL */
    for (int i = 0; i < 27; i++)
        HT[i] = NULL;

    /* ---------------- FILE VALIDATION ---------------- */

    /* Check if files are passed as arguments */
    if (argc >= 2)                     
        validate_files(argv, &head);   // Validate and store file names
    else
    {
        printf("-------------------------------------------------\n");
        printf("INFO : Insufficient arguments\n");
        printf("Please pass the arguments like ./a.out <txt file>\n");
        printf("-------------------------------------------------\n");
        return FAILURE;
    }

    /* Print all validated file names */
    if (print_filenames(head) == FAILURE)
    {
        printf("ERROR : No valid files found\n");
        printf("Database creation is not possible\n-> NULL\n");
        return FAILURE;
    }

    int option; 

    /* ---------------- MENU DRIVEN LOOP ---------------- */
    do
    {
        printf("\nSelect your choice among following operations:\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Save Database\n");
        printf("4. Search\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("\nEnter your choice : ");

        scanf("%d", &option); 

        switch (option)
        {
        /* -------- CREATE DATABASE -------- */
        case 1:
            create_database(HT, head); // Build inverted index
            create_flag = 1;           // Mark database as created
            break;

        /* -------- DISPLAY DATABASE -------- */
        case 2:
            if (!create_flag) // Check if database exists
            {
                printf("\nDatabase not created yet! Nothing to display!!\n");
                break;
            }
            display_database(HT); // Show indexed data
            break;

        /* -------- SAVE DATABASE -------- */
        case 3:
        {
            char filename[25]; 
            printf("Enter the filename to save database : ");
            scanf("%s", filename);         
            save_database(HT, filename); // Save database to file
            break;
        }

        /* -------- SEARCH WORD -------- */
        case 4:
        {
            char word[25]; 
            printf("Enter the word to search : ");
            scanf("%s", word);          
            search_database(HT, word); // Search word in database
            break;
        }

        /* -------- UPDATE DATABASE -------- */
        case 5:
            if (!create_flag) // Ensure database exists before update
            {
                printf("\nDatabase not created yet! Nothing to update!!\n");
                break;
            }
            create_flag = 0;              // Reset create flag
            update_flag = 1;              // Set update flag
            update_database(HT, &head);  // Update existing database
            create_flag = 1;              // Restore create flag
            break;

        /* -------- EXIT -------- */
        case 6:
            printf("\nThank you for using Inverted Search\n");
            break;

        /* -------- INVALID INPUT -------- */
        default:
            printf("\nINFO : Please enter a valid option\n");
        }

    } while (option != 6); // Loop until user exits

    return 0; 
}