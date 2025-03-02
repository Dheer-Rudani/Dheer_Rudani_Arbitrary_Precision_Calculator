/*
	Name: Dheer Rudani
	Description: Arbitrary Precision Calculator (APC)
	Date: 06/02/2025
*/

#include "APC.h"

void print_list(Dlist *head, char sign)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
		// printf("Operand -> ");
		while (head)
		{
			/* Printing the list */
			if (sign == '-')
			{
				printf("%c ", sign);
				sign = 0;
			}
			printf("%d ", head->data);

			/* Travering in forward direction */
			head = head->next;
			// if (head)
			//     printf("> ");
		}
		printf("\n");
	}
}