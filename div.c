/*
	Name: Dheer Rudani
	Description: Arbitrary Precision Calculator (APC)
	Date: 06/02/2025
*/

#include "APC.h"

extern char sign;

int validate_div(Dlist **res_head, Dlist **res_tail, Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2)
{
    if((head2 == tail2) && (head2->data == 0))
    {
        return DIVIDE_BY_ZERO;
    }
    else if((head1->data < 0 && head2->data >= 0))
    {
        head1->data = -(head1->data);
        sign = '-';
    }
    else if(head1->data >= 0 && head2->data < 0)
    {
        head2->data = -(head2 ->data);
        sign = '-';
    }
    else if(head1->data < 0 && head2->data < 0)
    {
        head1->data = -(head1->data);
        head2->data = -(head2->data);
    }

    return div_num(res_head, res_tail, head1, head2, tail1, tail2);
}

int div_num(Dlist **res_head, Dlist **res_tail, Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2)
{
    Dlist *t1 = NULL;
    Dlist *t2 = NULL;
    int count = 0, length1 = 0, length2 = 0, flag = 0;

    while(1)
    {
        t1 = head1;
        t2 = head2;
        length1 = length2 = 0;

        // Calculate the length of list1
        while(t1 != NULL)
        {
            t1 = t1->next;
            length1++;
        }

        // Calculate the length of list2
        while(t2 != NULL)
        {
            t2 = t2->next;
            length2++;
        }

        // If length1 < length2, division is done
        if(length1 < length2)
        {
            if(count == 0)
            {
                sign = '+';
                return LIST_EMPTY;
            }
            break;
        }

        // If lengths are equal, compare the actual values in the lists
        else 
        {
            if(length1 == length2)
            {
                t1 = head1;
                t2 = head2;

                // Compare digits of the lists
                while(t1 != NULL)
                {
                    if(t1->data > t2->data)
                    {
                        flag = 1;
                        break;
                    }
                    else if(t1->data < t2->data)
                    {
                        if(count == 0)
                        {
                            sign = '+';
                            return LIST_EMPTY;
                        }
                        flag = -1; // If list1 < list2, stop the division
                        break;
                    }
                    t1 = t1->next;
                    t2 = t2->next;
                }

                // If both lists are equal, division is done
                if(flag == -1)
                    break;
            }

            // Perform subtraction operation (list1 - list2)
            if(sub_num(res_head, res_tail, head1, head2, tail1, tail2) == FAILURE)
                return FAILURE;

            // Delete the old head1 list after subtraction
            if(dl_delete_list(&head1, &tail1) == FAILURE)
                return FAILURE;

            // Update head1 and tail1 to the result of subtraction
            head1 = *res_head;
            tail1 = *res_tail;

            // Reset result list pointers
            *res_head = *res_tail = NULL;

            // Increment the count of division (quotient digit)
            count++;
        }
    }

    // Store the final count in the result list (quotient)
    while(count)
    {
        dl_insert_first(res_head, res_tail, (count % 10));  // Insert quotient digits in reverse order
        count = count / 10;
    }

    return SUCCESS;
}
