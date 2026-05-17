/*
 * FILE NAME   : file_validation.c
 * DESCRIPTION : This file contains functions to:
 *               1. Validate input files
 *               2. Avoid duplicate file entries
 *               3. Store file names in a linked list
 *               4. Print validated file names
 *               5. Generate hash index for words
 */

#include "inverted.h"

/*
 * Function : validate_files
 * -----------------------------------------
 * Validates all input files passed through command line.
 *
 * Steps:
 * 1. Checks file extension (.txt)
 * 2. Checks if file exists
 * 3. Checks if file is not empty
 * 4. Avoids duplicate file entries
 * 5. Inserts valid file names into linked list
 *
 * argv : Array of file names
 * head : Pointer to file linked list
 */
void validate_files(char *argv[], F_node **head)
{
    int i = 1;      
    char *res;      

    printf("--------------------------------------------------------------------------------\n");

    /* Loop through all command line arguments */
    while (argv[i]) 
    {
        /* Check for file extension */
        res = strstr(argv[i], "."); 

        if (res)                    
        {
            /* Validate .txt extension */
            if (strcmp(res, ".txt") == 0) 
            {
                /* Open file in read mode */
                FILE *fptr = fopen(argv[i], "r"); 

                if (fptr)                         
                {
                    /* Check file size */
                    fseek(fptr, 0, SEEK_END);               
                    unsigned long int f_tell = ftell(fptr); 
                    rewind(fptr);                           

                    if (f_tell)                             
                    {
                        /* Check duplicate file entry */
                        if (check_duplicates(*head, argv[i]) == FAILURE) 
                        {
                            /* Insert file into linked list */
                            if (insert_last(head, argv[i]) == SUCCESS) 
                                printf("INFO : Successful : Inserting file name %s into file linked list\n\n", argv[i]);
                        }
                        else
                            printf("INFO : %s => This file is repeated, so it will not store into the SLL\n\n", argv[i]);
                    }
                    else
                        printf("INFO : %s => This file is empty\n\n", argv[i]);

                    fclose(fptr);      
                }
                else
                    printf("INFO : %s => This file does not exist in the current directory\n\n", argv[i]);
            }
            else
                printf("INFO : %s => This file is not .txt\n\n", argv[i]);
        }
        else
            printf("INFO : %s => This file has no extension\n\n", argv[i]);

        i++; 
    }

    printf("--------------------------------------------------------------------------------\n");
}


/*
 * Function : check_duplicates
 * -----------------------------------------
 * Checks whether a file name already exists
 * in the file linked list.
 *
 * head   : Head of linked list
 * f_name : File name to check
 *
 * return : SUCCESS (duplicate found)
 *          FAILURE (not found)
 */
int check_duplicates(F_node *head, char *f_name) 
{
    while (head)
    {
        /* Compare file names */
        if (strcmp(head->f_name, f_name) == 0) 
            return SUCCESS;                    

        head = head->link;                     
    }

    return FAILURE; 
}


/*
 * Function : insert_last
 * -----------------------------------------
 * Inserts a new file node at the end of the linked list.
 *
 * head   : Pointer to head node
 * f_name : File name to insert
 *
 * return : SUCCESS / FAILURE
 */
int insert_last(F_node **head, char *f_name)
{
    /* Allocate memory for new node */
    F_node *new_node = malloc(sizeof(F_node));

    if (new_node == NULL)                     
        return FAILURE;

    /* Copy file name into node */
    strcpy(new_node->f_name, f_name); 

    new_node->link = NULL;    

    /* If list is empty */
    if (*head == NULL)                
        *head = new_node;

    /* Insert at end */
    else
    {
        F_node *temp = *head;

        while (temp->link != NULL) 
        {
            temp = temp->link;
        }

        temp->link = new_node; 
    }

    return SUCCESS;
}

/* Function to insert node at beginning of linked list */
int insert_first(F_node **head, char *filename)
{
    // Allocate memory
    F_node *new_node = malloc(sizeof(F_node)); 

    if (new_node == NULL)
    {
        return FAILURE;
    }

    // Initialize node data
    strcpy(new_node->f_name, filename);
    new_node->link = NULL; 

    // Insert at beginning
    new_node->link = *head;
    *head = new_node; 

    return SUCCESS; 
}

/*
 * Function : print_filenames
 * -----------------------------------------
 * Displays all validated file names stored
 * in the linked list.
 *
 * head : Head of linked list
 *
 * return : SUCCESS / FAILURE
 */
int print_filenames(F_node *head)
{
    /* Check if list is empty */
    if (head == NULL) 
        return FAILURE;

    printf("\n>>> Valid input files selected for inverted index <<\n\n");

    /* Traverse and print file names */
    while (head) 
    {
        printf("%s -> ", head->f_name);
        head = head->link;
    }

    printf("NULL\n"); 

    return SUCCESS;
}


/*
 * Function : get_index
 * -----------------------------------------
 * Generates hash index based on first character of word.
 *
 * Rules:
 * - 'A' to 'Z'  -> 0 to 25
 * - 'a' to 'z'  -> 0 to 25
 * - Special characters -> 26
 *
 * word : Input word
 *
 * return : Index (0–26)
 */
int get_index(char *word)
{
    /* Uppercase letters */
    if (word[0] >= 'A' && word[0] <= 'Z')      
        return word[0] - 'A';  

    /* Lowercase letters */
    else if (word[0] >= 'a' && word[0] <= 'z') 
        return word[0] - 'a'; 

    /* Special characters */
    else                                      
        return 26;                             
}