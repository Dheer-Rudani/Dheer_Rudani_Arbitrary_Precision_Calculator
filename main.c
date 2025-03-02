/*
	Name: Dheer Rudani
	Description: Arbitrary Precision Calculator (APC)
	Date: 06/02/2025
*/

#include "APC.h"
#include <string.h>

char sign;
int len_list1 = 0, len_list2 = 0;

int main(int argc, char **argv)
{
	Dlist *head1, *tail1, *head2, *tail2;
	Dlist *res_head = NULL, *res_tail = NULL;
	head1 = tail1 = head2 = tail2 = NULL;

	//Input validation
	if(argc < 4)
	{
		printf("Error!\nInvalid number of arguments\nEnter the arguments as -> ./a.out <operand1> <operator> <operand2>\n");
		return FAILURE;
	}

	//Operator validation
	if(strlen(argv[2]) > 1)
	{
		printf("Error!\nInvalid operator\nOperation Failed\n");
		return FAILURE;
	}

	//Number validation
	for(int i = 0; argv[1][i] != '\0'; i++)
	{
		if(is_digit(argv[1][i]) == 0)
		{
			printf("Error!\nOperand must always contain digits\n");
			return FAILURE;
		}
	}
	for(int i = 0; argv[3][i] != '\0'; i++)
	{
		if(is_digit(argv[3][i]) == 0)
		{
			printf("Error!\nOperand must always contain digits\n");
			return FAILURE;
		}
	}

	//Creating the operands
	create_operands(&head1, &tail1, argv[1]);
	create_operands(&head2, &tail2, argv[3]);

	//Storing the operator
	char op = argv[2][0];
	
	printf("Operand 1-> ");
	print_list(head1, sign);
	printf("Operator -> %c\n", op);
	printf("Operand 2-> ");
	print_list(head2, sign);

	//Performing the specific operation based upon the operator
	switch (op)
	{
		case '+':
			if(validate_add_op(&res_head, &res_tail, &head1, &head2, &tail1, &tail2) == FAILURE)
			{
				printf("Error!\nCouldn't perform Addition\n");
				return FAILURE;
			}
			break;

		case '-':
			if(validate_sub_op(&res_head, &res_tail, &head1, &head2, &tail1, &tail2) == FAILURE)
			{
				printf("Error!\nCouldn't perform Subtraction\n");
				return FAILURE;
			}
			break;

		case '*':
		case 'x':
			if(validate_mul(&res_head, &res_tail, head1, head2, tail1, tail2) == FAILURE)
				printf("Error!\nCouldn't perform Multiplication\n");
			break;

		case '/':
			int status = validate_div(&res_head, &res_tail, head1, head2, tail1, tail2);
			if (status == FAILURE) // If there is any error in allocating memory or performing subtraction
				printf("Error!\nCouldn't perform Division\n");
			else if(status == DIVIDE_BY_ZERO) //If we are trying to divide by zero
			{
				printf("Cannot divide a number by 0\n");
				return DIVIDE_BY_ZERO;
			}
			else if(status == LIST_EMPTY) //If the list1 data is smaller than list2 data
			{
				dl_insert_first(&res_head, &res_tail, 0);
			}
			break;

		default:
			printf("Error!\nOperator not found\n");
			return FAILURE;
	}

	//Priting the result
	printf("\nResult   -> ");
	print_list(res_head, sign);
}
