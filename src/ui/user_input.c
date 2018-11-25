#include "ui/user_input.h"

s_contact* user_input_add_contact(s_linked_list* contact_list)
{
	 printf("Type in person's Name \n ");
	 char name[TEXT_FIELD_MAX_SIZE];
	 scanf("%TEXT_FIELD_MAX_SIZEs", name);

	 printf("Type in person's Surname \n ");
	 char surname[TEXT_FIELD_MAX_SIZE];
	 scanf("%TEXT_FIELD_MAX_SIZEs", surname);

	 printf("Type in person's phone number \n ");
	 int phoneNumber;
	 scanf("%d", &phoneNumber);

     printf("Type in person's address \n ");
     char address[TEXT_FIELD_MAX_SIZE];
     scanf("%TEXT_FIELD_MAX_SIZEs", address);

     int id = 0;
     s_contact* latest_contact;

     if (v_list_is_empty(contact_list)) {   } 

     else 
     {
        latest_contact = (s_contact*)v_list_last_element(contact_list);
        id = latest_contact->id + 1;
     }

     printf("Writing contact id %d \n ", id);

	 s_contact* contact = create_contact(id, name, surname, address, phoneNumber);
     latest_contact = NULL;

	 return contact;
}

void handle_prompt(s_linked_list* contact_list, char* data_path)
{
	int input;
    printf("\n Choose Action: \n 1. Find Contact \n 2. Add Contact \n 3. Remove Contact by id \n 4. Save and exit. \n");
    scanf("%d", &input);

    if (input > 4 || input < 1)
    {
    	printf("Please, type in numeric values from 1 to 5 \n");
    	handle_prompt(contact_list, data_path);
    }

    if (input == 1)
    {
    	char name[TEXT_FIELD_MAX_SIZE];
    	printf("Enter person's name: \n");
        scanf("%TEXT_FIELD_MAX_SIZEs", name);

        printf("Name is %s ", name);

        char surname[TEXT_FIELD_MAX_SIZE];
    	printf("Enter person's surname: \n");
        scanf("%TEXT_FIELD_MAX_SIZEs", surname);

        const char* query = calloc(strlen(name) + strlen(surname) + 1, sizeof(char));

        strcat(query, name);
        strcat(query, surname);

        search_contact(query, contact_list);
        handle_prompt(contact_list, data_path);
    }

    else if (input == 2) 
    {
    	json_write_contact(user_input_add_contact(contact_list), contact_list);

	    handle_prompt(contact_list, data_path);
    }

    else if (input == 3)
    {
        printf("Write down contact id to remove: \n");
        unsigned int id;
        scanf("%d", &id);
        printf("Trying to remove... \n " );
        remove_contact_by_id(id, contact_list);
        handle_prompt(contact_list, data_path);
    }

    else if(input == 4)
    {
        printf("saving data to a file... \n ");
        save_data(data_path);
        printf("successfuly saved. \n ");
    }
}
