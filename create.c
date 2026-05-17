#include "inverted.h"

extern int create_flag; 
extern int update_flag; 

M_node *create_main_node(char *word, char *filename)
{
    M_node *new_main = malloc(sizeof(M_node)); 
    strcpy(new_main->word, word);              
    new_main->file_count = 1;                  
    new_main->main_link = NULL;                

    new_main->sub_link = create_sub_node(filename); 
    return new_main;                                
}


S_node *create_sub_node(char *filename)
{
    S_node *new_sub = malloc(sizeof(S_node)); 
    new_sub->word_count = 1;                  
    strcpy(new_sub->filename, filename);      
    new_sub->sub_link = NULL;                 
    return new_sub;                           
}


void create_database(M_node *HT[], F_node *head)
{
    
    if (create_flag)
    {
        printf("INFO : Database is already created\n");
        return;
    }
    
    while (head)
    {
        FILE *fptr = fopen(head->f_name, "r"); 
        char str[25];                          
        while (fscanf(fptr, "%s", str) == 1)
        {
            int index = get_index(str); 

            if (HT[index] == NULL)
            {
                HT[index] = create_main_node(str, head->f_name); 
            }
            else
            {
                M_node *temp = HT[index]; 
                M_node *prev = NULL;
                
                while (temp && strcmp(temp->word, str) != 0)
                {
                    prev = temp;
                    temp = temp->main_link;
                }
                
                if (temp == NULL)
                {
                    prev->main_link = create_main_node(str, head->f_name); 
                }
                
                else
                {
                    S_node *sub_temp = temp->sub_link; 
                    S_node *sub_prev = NULL;

                    while (sub_temp && strcmp(sub_temp->filename, head->f_name) != 0)
                    {
                        sub_prev = sub_temp;
                        sub_temp = sub_temp->sub_link;
                    }
                    
                    if (sub_temp == NULL)
                    {
                        sub_prev->sub_link = create_sub_node(head->f_name); 
                        temp->file_count++;                                 
                    }
                    
                    else
                        sub_temp->word_count++;
                }
            }
        }
        fclose(fptr); 

        
        printf("\nINFO : Successful : Creation of DATABASE for file : %s\n", head->f_name);

        if (update_flag) 
            break;
        head = head->link; 
    }
}
