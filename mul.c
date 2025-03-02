/*
	Name: Dheer Rudani
	Description: Arbitrary Precision Calculator (APC)
	Date: 06/02/2025
*/

#include "APC.h"

extern char sign;

int validate_mul(Dlist **res_head, Dlist **res_tail, Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2)
{
    if((head1->data < 0 && head2->data >= 0))
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

    return mul_num(res_head, res_tail, head1, head2, tail1, tail2);
}

int mul_num(Dlist **res_head, Dlist **res_tail, Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2)
{
    Dlist *rh1 = NULL, *rh2 = NULL, *rt1 = NULL, *rt2 = NULL, *t1 = tail1, *t2 = tail2;
    int mul = 0, count = 0;

    while(t2 != NULL)
    {
        t1 = tail1;
        int carry = 0;

        //Multiplying and storing the value in a new list
        while(t1 != NULL)
        {
            mul = (t1->data * t2->data) + carry;
            carry = mul / 10;

            dl_insert_first(&rh1, &rt1, (mul % 10));

            t1 = t1->prev;
        }
        //If carry is still set
        if(carry != 0)
        {
            dl_insert_first(&rh1, &rt1, carry);
            carry = 0;
        }

        //adding the resulting lists
        add_num(res_head, res_tail, rh1, rh2, rt1, rt2);

        //Taking the count of zeros to be padded
        count++;
        
        //Moving the pointer 
        t2 = t2->prev;
        t1 = tail1;

        if(t2 == NULL)
        {
            break;
        }
        else
        {
            //Updating the addition result into the second list
            rh2 = *res_head;
            rt2 = *res_tail;

            //Pointing the result pointer to NULL
            *res_head = *res_tail = NULL;

            //Deleting the list
            dl_delete_list(&rh1, &rt1);

            //Padding with zeros
            for(int i = 0; i < count; i++)
                dl_insert_first(&rh1, &rt1, 0);
        }
    }

    //Deleting the leading zeros
    while((*res_head != NULL) && ((*res_head)->data == 0) && (*res_head != *res_tail))
    {
        dl_delete_first(res_head, res_tail);
    }

    return SUCCESS;
}