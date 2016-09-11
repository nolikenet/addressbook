#include "s_linked_list.h"


void push(Node *head, void *data)
{
	Node *current = head;

	printf("\n %p", head);
	while (current->next != 0)
	{
		current = current->next;
	}

	current->next = malloc(sizeof(Node));
	printf("\n Next data %p", current->next->data);
	current->next->data = data;
	current->next->next = 0;
   	printf("\n Next data %p", current->next->data);
}

void remove_first(Node *head)
{
	Node *temp = 0;
	printf("\n Node Before removing %p", head);
 	temp = head->next;
 	free(head);
 	head = temp; 
 	printf("\nNode removed %p", head);
}

void remove_last(Node *head)
{
	Node *current = head;

	while(current->next != 0)
	{
		current = current->next;
	}
	free(current);
	current = 0;
	printf("\n Current data should be 0 %p", current);
}

int get_length(Node *head)
{
	unsigned int i = 0;
	Node *current = head;
	while(current->next != 0)
	{
		i++;
		current = current->next;
	}
	printf("\n Current length %i", i);
	return i;
}