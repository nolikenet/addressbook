#include "s_contact.h"
#include "string.h"

s_contact* create_contact(char* name, char* surname, int phoneNumber)
{
	//s_contact* contact = calloc(sizeof(s_contact), 1);
	s_contact* contact = malloc(sizeof(s_contact));

	strcpy(contact->name, name);
	printf("\n Added Name: %s ", contact->name);

	strcpy(contact->surname, surname);
	printf("\n Added Surname: %s ", contact->surname);

	memcpy(&contact->id, &phoneNumber, sizeof(phoneNumber));
	printf("\n Added Number: %d ", contact->id);

	return contact;
}	