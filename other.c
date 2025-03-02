/*
	Name: Dheer Rudani
	Description: Arbitrary Precision Calculator (APC)
	Date: 06/02/2025
*/

#include "APC.h"

extern char sign;
extern int len_list1, len_list2;

int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
    //Allocate memory for new data
    Dlist *new = malloc(sizeof(Dlist));
    
    //Validate the allocated memory
    if(new == NULL)
        return FAILURE;
        
    //Update the data and link
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    
    //Validate the list
    if(*head == NULL) //If list is empty
    {
        *tail = *head = new; // Point both head and tail to new node
        return SUCCESS;
    }
    else //If list is not empty
    {
        (*head)->prev = new; //Point the prev pointer of head node to new node
        new->next = *head; //Point the next pointer of new to head
        *head = new; //Point the head pointer to new pointer
        return SUCCESS;
    }
}

//Check list function
int check_length(Dlist *head1, Dlist *head2)
{
    Dlist *t1 = head1, *t2 = head2;

    //Calculating the sizes
    while(t1 != NULL)
    {
        len_list1++;
        t1 = t1->next; 
    }

    while(t2 != NULL)
    {
        len_list2++;
        t2 = t2->next;
    }   
}

//Swap pointer function
void swap_ptr(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2)
{
    // Swap head pointers
    Dlist *temp = *head1;
    *head1 = *head2;
    *head2 = temp;

    // Swap tail pointers
    temp = *tail1;
    *tail1 = *tail2;
    *tail2 = temp;
}

int dl_delete_list(Dlist **head, Dlist **tail)
{
    //Validate the list
    if(*head == NULL) //If list is empty
    {
        return FAILURE;
    }
    else //If list is not empty
    {
        while(*head != NULL)
        {
            if(*head == *tail) //Validate if the list has only one node or not
            {
                free(*head); //Delete the existing node
                *head = *tail = NULL;
            }
            else
            {
                *head = (*head)->next; //Move the head pointer to next node
                free((*head)->prev); //Delete the previous node
                (*head)->prev = NULL; //Update the previous node with NULL
            }
        }
        return SUCCESS;
    }
}

int dl_delete_first(Dlist **head, Dlist **tail)
{
    //Validate the list
    if(*head == NULL) //If list is empty
    {
        return FAILURE;
    }
    else //If list is not empty
    {
        if(*head == *tail) //Validate if the list has only one node or not
        {
            free(*head); //Delete the existing node
            *head = *tail = NULL;
        }
        else
        {
            *head = (*head)->next; //Move the head pointer to next node
            free((*head)->prev); //Delete the previous node
            (*head)->prev = NULL; //Update the previous node with NULL
        }
        return SUCCESS;
    }
}

int is_digit(int ch)//Function definition
{
   if ((ch>=48 && ch<=57) || (ch =='-') || (ch == '+'))//Condition
   return 1;
   else
   return 0;
}