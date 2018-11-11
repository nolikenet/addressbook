#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "s_node.h"
#include "s_linked_list.h"
#include "s_contact.h" 
#include "common.h"
#include "deps/cJSON.c"

#define USER_INPUT_MAX_SIZE 40

const char* DATA_PATH = "data/data.json";

s_linked_list* contact_list; 

s_contact* user_input_add_contact()
{
	 printf("Type in person's Name \n ");
	 char name[TEXT_FIELD_MAX_SIZE];
	 scanf("%s", name);

	 printf("Type in person's Surname \n ");
	 char surname[TEXT_FIELD_MAX_SIZE];
	 scanf("%s", surname);

	 printf("Type in person's phone number \n ");
	 int phoneNumber;
	 scanf("%d", &phoneNumber);

     printf("Type in person's address \n ");
     char* address[TEXT_FIELD_MAX_SIZE];
     scanf("%s", address);

	 s_contact* contact = create_contact(name, surname, address, phoneNumber);

	 return contact;
}


void populate_list_from_buffer(char* buff)
{
    cJSON* root = cJSON_Parse(buff);
    const cJSON* contacts = NULL;
    const cJSON* contact = NULL;

    contacts = cJSON_GetObjectItemCaseSensitive(root, "contacts");

    printf("Populating list... \n ");
    cJSON_ArrayForEach(contact, contacts) {
        cJSON* name= cJSON_GetObjectItemCaseSensitive(contact, "name");
        cJSON* surname = cJSON_GetObjectItemCaseSensitive(contact, "surname");
        cJSON* address = cJSON_GetObjectItemCaseSensitive(contact, "address");
        cJSON* phone = cJSON_GetObjectItemCaseSensitive(contact, "phone");

        if (cJSON_IsString(name) && (name->valuestring != NULL))
        {
             s_contact* contact = create_contact(name->valuestring, surname->valuestring, address->valuestring, phone->valueint); 
             push_to_list(contact_list, contact);
             printf("\n");
        }
    }
    cJSON_Delete(root);
}

char* read_storage(char* path)
{
    FILE* fp;
    fp = fopen(path,"r");
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buff = malloc(sizeof (char) * len);
    fread(buff, sizeof(char), sizeof(char) * len, fp);
    fclose(fp);
    fp = NULL;
    printf("buff read %s \n", buff);
    return buff;
}

void search_contact(char* query)
{
    s_node* tmp = contact_list->head;
    while(tmp != NULL)
    {
        s_contact* data = tmp->data;
        char* concat_str = calloc(strlen(data->name) + strlen(data->surname) + 1, sizeof(char));
        strcat(concat_str, data->name);
        strcat(concat_str, data->surname);

        printf("Searching for concat: %s, query: %s \n ", concat_str, query);
        if (strcmp(concat_str, query) == 0 )
        {
            printf("found data. Name: %s, Surname: %s, Address: %s, Phone: %d \n ", data->name, data->surname, data->address, data->phone);
            destroy(concat_str);
            destroy(query);
            return;
        }
        destroy(concat_str);
        tmp = tmp->next;
    }
    destroy(query);
    printf("Contact not found. \n");

}

void write_data(char* path, char* buff)
{
    /*FILE* fp;
    fp = fopen(path, "r");*/

}

void find_contact_by_name(s_linked_list* list, char* name)
{
	s_node* temp = list->head;
	while(temp != NULL)
	{
		s_contact* c = temp->data;
		if (strcmp(c->name, name) == 0)
		{
			printf("Found contact. \n");
			printf("Name: %s \n ", c->name);
			printf("Surname: %s \n ", c->surname);
			printf("Phone Number: %d \n ", c->phone);
		}

		temp = temp->next;
	}
}

void handle_prompt(s_linked_list* contact_list){
	int input;
    printf("\n Choose Action: \n 1. Find Contact \n 2. Add Contact \n 3. Delete Contact \n 4. Print Contact \n 5. Exit \n");
    scanf("%d", &input);

    if (input > 5 || input < 0)
    {
    	printf("Error. Please, type in numeric values from 1 to 5 \n");
    	handle_prompt(contact_list);
    }

    if (input == 1)
    {
    	char name[TEXT_FIELD_MAX_SIZE];
    	printf("Enter person's name: \n");
        scanf("%s", name);

        char surname[TEXT_FIELD_MAX_SIZE];
    	printf("Enter person's surname: \n");
        scanf("%s", surname);

        char* query = calloc(strlen(name) + strlen(surname) + 1, sizeof(char));

        strcat(query, name);
        strcat(query, surname);
        printf("Searching for name %s \n ", query);
        search_contact(query);
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
    contact_list = create_linked_list();

    populate_list_from_buffer(read_storage(DATA_PATH));
	
	handle_prompt(contact_list);

    destroy(contact_list);
	
	return 0;
}
