/*
	Name: Dheer Rudani
	Description: Arbitrary Precision Calculator (APC)
	Date: 06/02/2025
*/

#include "APC.h"

int create_operands(Dlist **head, Dlist **tail, char *argv)
{
	int i = 0, j = 0, flag = 0;
	// Operand 1
	while (argv[i] != '\0')
	{
		Dlist *new = malloc(sizeof(Dlist));

		// Validating the created memory
		if (new == NULL)
			return FAILURE;

		// Updating the values based upon the sign
		if (argv[i] == '-')
		{
			flag = 1;
			i++;
		}
		else if(argv[i] == '+' || argv[i] == '(' || argv[i] == ')')
			i++;

		if (flag == 1)
		{
			new->data = -(argv[i] - 48);
			flag = 0;
		}
		else
			new->data = argv[i] - 48;
		new->prev = NULL;
		new->next = NULL;

		// Validate the list
		if (*head == NULL)
		{
			*head = *tail = new;
		}
		else
		{
			(*tail)->next = new;
			new->prev = *tail;
			*tail = new;
		}

		i++;
	}
	return SUCCESS;
}