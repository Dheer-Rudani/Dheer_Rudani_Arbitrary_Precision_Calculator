/*
	Name: Dheer Rudani
	Description: Arbitrary Precision Calculator (APC)
	Date: 06/02/2025
*/

#include "APC.h"

extern char sign;
extern int len_list1, len_list2;

int validate_sub_op(Dlist **res_head, Dlist **res_tail, Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2)
{
    // Case when both numbers are positive
    if((*head1)->data >= 0 && (*head2)->data >= 0)
    {
        check_length(*head1, *head2); // Compare lengths of the two lists
        if(len_list1 < len_list2)
        {
            swap_ptr(head1, head2, tail1, tail2); // Swap lists if len_list1 < len_list2
            sign = '-'; // Set sign to negative
        }
        else if(len_list1 == len_list2)
        {
            if((*head1)->data < (*head2)->data)
            {
                swap_ptr(head1, head2, tail1, tail2); // Swap lists if head1 < head2
                sign = '-'; // Set sign to negative
            }
        }
        else
            sign = '+'; // Set sign to positive if head1 >= head2

        return sub_num(res_head, res_tail, *head1, *head2, *tail1, *tail2);
    }
    // Case when both numbers are negative
    else if((*head1)->data < 0 && (*head2)->data < 0)
    {
        (*head1)->data = -((*head1)->data); // Convert head1 to positive
        (*head2)->data = -((*head2)->data); // Convert head2 to positive

        check_length(*head1, *head2); // Compare lengths of the two lists
        if(len_list1 < len_list2)
        {
            swap_ptr(head1, head2, tail1, tail2); // Swap lists if len_list1 < len_list2
            sign = '+'; // Set sign to negative
        }
        else if(len_list1 == len_list2)
        {
            if((*head1)->data < (*head2)->data)
            {
                swap_ptr(head1, head2, tail1, tail2); // Swap lists if head1 < head2
                sign = '+'; // Set sign to negative
            }
        }
        else
            sign = '-'; // Set sign to negative
        
        return sub_num(res_head, res_tail, *head1, *head2, *tail1, *tail2);
    }
    // Case when head1 is positive and head2 is negative
    else if((*head1)->data >= 0 && (*head2)->data < 0)
    {
        sign = '+';
        (*head2)->data = -((*head2)->data); // Convert head2 to positive
        return add_num(res_head, res_tail, *head1, *head2, *tail1, *tail2);      
    }
    // Case when head1 is negative and head2 is positive
    else if((*head1)->data < 0 && (*head2)->data >= 0)
    { 
        sign = '-';
        (*head1)->data = -((*head1)->data); // Convert head1 to positive
        return add_num(res_head, res_tail, *head1, *head2, *tail1, *tail2);
    }
}

int sub_num(Dlist **res_head, Dlist **res_tail, Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2)
{
    Dlist *t1 = tail1, *t2 = tail2;
    int borrow = 0;

    while(t1 != NULL || t2 != NULL || borrow != 0)
    {
        // Validating what value to add
        int t1_data = (t1 != NULL) ? t1->data : 0;
        int t2_data = (t2 != NULL) ? t2->data : 0;

        int diff = t1_data - t2_data - borrow;

        //Checking the values
        if(diff < 0)
        {
            diff = diff + 10;
            borrow = 1;
        }
        else
            borrow = 0;

        //Creating a new node and updating the data
        if(dl_insert_first(res_head, res_tail, diff) == FAILURE)
            return FAILURE;

        // Updating the pointers
        if (t1 != NULL)
            t1 = t1->prev;
        if (t2 != NULL)
            t2 = t2->prev;
    }

    //Deleting the leading zeros
    while((*res_head != NULL) && ((*res_head)->data == 0) && (*res_head != *res_tail))
    {
        dl_delete_first(res_head, res_tail);
    }

    return SUCCESS;
}