#include "s_contact.h"
#include "string.h"

s_contact* create_contact(char* name, char* surname, char* address, int phone)
{
	//s_contact* contact = calloc(sizeof(s_contact), 1);
	s_contact* contact = malloc(sizeof(s_contact));

	strcpy(contact->name, name);
	printf("\n Added Name: %s ", contact->name);

	strcpy(contact->surname, surname);
	printf("\n Added Surname: %s ", contact->surname);

    strcpy(contact->address, address);
	printf("\n Added Address: %s ", contact->address);
    
    contact->phone = phone;
	printf("\n Added Number: %d ", contact->phone);

	return contact;
}	
