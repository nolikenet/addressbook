#include <stdio.h>
#include <stdlib.h>
#include "s_node.h"
#include "s_linked_list.h"
#include "contact.h" 

int main()
{
	int c;
	Contact *firstContact = malloc(sizeof(Contact));
	printf("First contact %p", firstContact);
	//firstContact->name[0] = 'a';

	Node *head = malloc(sizeof(Node));
	head->data = firstContact;
	head->next = 0;


	push(head, firstContact);
	push(head, firstContact);
	push(head, firstContact);
	push(head, firstContact);
	push(head, firstContact);
	//remove_last(head);
	remove_first(head);

    get_length(head);
    //remove_at_index(head, 2);
    get_length(head);


	LinkedList *list;
	return 0;
}
