#include "s_contact.h"
#include "string.h"

s_contact* create_contact(unsigned int id, char* name, char* surname, char* address, unsigned int phone)
{
	s_contact* contact = malloc(sizeof(s_contact));

    contact->id = id;	
	printf("Added id: %d \n ", contact->id);

	strcpy(contact->name, name);
	printf("Added Name: %s \n ", contact->name);

	strcpy(contact->surname, surname);
	printf(" Added Surname: %s \n ", contact->surname);

    strcpy(contact->address, address);
	printf(" Added Address: %s \n ", contact->address);
    
    contact->phone = phone;
	printf(" Added Number: %d \n ", contact->phone);

	return contact;
}	
