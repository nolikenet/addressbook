#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "s_node.h"
#include "s_linked_list.h"
#include "s_contact.h" 
#include "common.h"

#define USER_INPUT_MAX_SIZE 40

s_contact* user_input_add_contact()
{
	 printf("Type in person's Name \n ");
	 char name[20];
	 scanf("%s", name);

	 printf("Type in person's Surname \n ");
	 char surname[20];
	 scanf("%s", surname);

	 printf("Type in person's phoneNumber \n ");
	 int phoneNumber;
	 scanf("%d", &phoneNumber);

	 s_contact* contact = create_contact(name, surname, phoneNumber);

	 return contact;
}

void find_contact_by_name(s_linked_list* list, char* name)
{
	s_node* temp = list->head;
	while(temp != NULL)
	{
		s_contact* c = temp->data;
		if (strcmp(c->name, name) == 0)
		{
			printf("found name");
		}

		temp = temp->next;
	}
}

void handle_prompt(s_linked_list* contact_list){
	int input;
    printf("\n Choose Your Destiny: \n 1. Find Contact \n 2. Add Contact \n 3. Delete Contact \n 4. Print Contact \n 5. Exit \n");
    scanf("%d", &input);

    printf("Got Input %d \n", input);

    if (input > 5 || input < 0)
    {
    	printf("Error. Please, type in numeric values from 1 to 5 \n");
    	handle_prompt(contact_list);
    }

    if (input == 1)
    {
    	char name[20];
    	printf("Enter person's name: \n");
        scanf("%s", name);

        find_contact_by_name(contact_list, name);
    }

    else if (input == 2) 
    {
    	push_to_list(contact_list, user_input_add_contact());

	    printf("List length is %d \n ", get_list_length(contact_list));

	    handle_prompt(contact_list);
    }
}


int main()
{
	s_linked_list *contact_list = create_linked_list();
	
	handle_prompt(contact_list);

	free(contact_list);
	contact_list = NULL;
	
	return 0;
}
