/*
	Name: Dheer Rudani
	Description: Arbitrary Precision Calculator (APC)
	Date: 06/02/2025
*/

#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAILURE 1
#define SUCCESS 0
#define DIVIDE_BY_ZERO 2
#define LIST_EMPTY 3

typedef struct node
{
	int data;
	struct node *next;
	struct node *prev;
} Dlist;

//Other
int create_operands(Dlist **, Dlist **, char *);
void print_list(Dlist *head, char sign);
int dl_insert_first(Dlist **head, Dlist **tail, int data);
void swap_ptr(Dlist **, Dlist **, Dlist **, Dlist **);
int check_length(Dlist *head1, Dlist *head2);
int dl_delete_list(Dlist **head, Dlist **tail);
int dl_delete_first(Dlist **head, Dlist **tail);
int is_digit(int ch);

//Addition
int add_num(Dlist **res_head, Dlist **res_tail, Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2);
int validate_add_op(Dlist **res_head, Dlist **res_tail, Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2);

//Subtraction
int sub_num(Dlist **res_head, Dlist **res_tail, Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2);
int validate_sub_op(Dlist **res_head, Dlist **res_tail, Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2);

//Multiplication
int validate_mul(Dlist **res_head, Dlist **res_tail, Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2);
int mul_num(Dlist **res_head, Dlist **res_tail, Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2);

//Division
int div_num(Dlist **res_head, Dlist **res_tail, Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2);
int validate_div(Dlist **res_head, Dlist **res_tail, Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2);

#endif