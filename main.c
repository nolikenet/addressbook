#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "s_node.h"
#include "s_linked_list.h"
#include "s_contact.h" 
#include "common.h"
#include "deps/cJSON.c"

const char* DATA_PATH = "data/data.json";

s_linked_list* contact_list = NULL; 
cJSON* json_root_object = NULL;

s_contact* user_input_add_contact()
{
	 printf("Type in person's Name \n ");
	 char* name[TEXT_FIELD_MAX_SIZE];
	 scanf("%s", name);

	 printf("Type in person's Surname \n ");
	 char* surname[TEXT_FIELD_MAX_SIZE];
	 scanf("%s", surname);

	 printf("Type in person's phone number \n ");
	 int phoneNumber;
	 scanf("%d", &phoneNumber);

     printf("Type in person's address \n ");
     char* address[TEXT_FIELD_MAX_SIZE];
     scanf("%s", address);

     int id = 0;
     s_contact* latest_contact;

     if (is_list_empty(contact_list)) {   } 

     else 
     {
        latest_contact = (s_contact*)list_last_element(contact_list);
        id = latest_contact->id + 1;
     }

     printf("Writing contact id %d \n ", id);

	 s_contact* contact = create_contact(id, name, surname, address, phoneNumber);
     latest_contact = NULL;

	 return contact;
}


void populate_list_from_buffer(char* buff)
{
    json_root_object = cJSON_Parse(buff);
    const cJSON* contacts = NULL;
    const cJSON* contact = NULL;

    contacts = cJSON_GetObjectItemCaseSensitive(json_root_object, "contacts");

    printf("Populating list... \n ");
    cJSON_ArrayForEach(contact, contacts) {
        cJSON* id = cJSON_GetObjectItemCaseSensitive(contact, "id");
        cJSON* name = cJSON_GetObjectItemCaseSensitive(contact, "name");
        cJSON* surname = cJSON_GetObjectItemCaseSensitive(contact, "surname");
        cJSON* address = cJSON_GetObjectItemCaseSensitive(contact, "address");
        cJSON* phone = cJSON_GetObjectItemCaseSensitive(contact, "phone");

        if (cJSON_IsString(name) && (name->valuestring != NULL))
        {
             s_contact* contact = create_contact(id->valueint, name->valuestring, surname->valuestring, address->valuestring, phone->valueint); 
             push_to_list(contact_list, contact);
             printf("\n");
        }
    }
}

char* read_storage(char* path)
{
    FILE* fp;
    fp = fopen(path,"r");
    fseek(fp, 0, SEEK_END);
    long int len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buff = malloc(sizeof (char) * len);
    fread(buff, sizeof(char), sizeof(char) * len, fp);
    fclose(fp);
    return buff;
}

s_contact* search_contact(char* query)
{
    s_node* tmp = contact_list->head;
    while(tmp != NULL)
    {
        s_contact* data = tmp->data;
        char* concat_str = calloc(strlen(data->name) + strlen(data->surname) + 1, sizeof(char));
        strcat(concat_str, data->name);
        strcat(concat_str, data->surname);

        if (strcmp(concat_str, query) == 0 )
        {
            printf("Contact found. \n ID: %d, Name: %s, Surname: %s, Address: %s, Phone: %d \n ", data->id, data->name, data->surname, data->address, data->phone);
            destroy(concat_str);
            destroy(query);
            return (s_contact*)data;
        }
        destroy(concat_str);
        tmp = tmp->next;
    }
    tmp = NULL;
    destroy(query);
    printf("Contact not found. \n");
    return tmp; 
}

bool json_write_contact(s_contact* contact)
{
    printf("Writing Contact \n ");
    if (push_to_list(contact_list, contact) != true)
    {
        printf("Error: data hasn't been pushed to list \n ");
        return false;
    }

    const cJSON* contact_json_obj = cJSON_CreateObject();
    cJSON_AddItemToObject(contact_json_obj, "id", cJSON_CreateNumber(contact->id)); 
    cJSON_AddItemToObject(contact_json_obj, "name", cJSON_CreateString(contact->name)); 
    cJSON_AddItemToObject(contact_json_obj, "surname", cJSON_CreateString(contact->surname)); 
    cJSON_AddItemToObject(contact_json_obj, "address", cJSON_CreateString(contact->address)); 
    cJSON_AddItemToObject(contact_json_obj, "phone", cJSON_CreateNumber(contact->phone)); 
    cJSON_AddItemToArray(cJSON_GetObjectItemCaseSensitive(json_root_object, "contacts"), contact_json_obj);

    return true;
}

void save_data(const char* path)
{
    FILE* fp;
    fp = fopen(path,"w+");
    char* buff = cJSON_Print(json_root_object);
    fputs(buff, fp);
    fclose(fp);
}

void remove_contact_by_id(unsigned int id)
{
    printf("Trying to remove \n ");
    if (is_list_empty(contact_list))
    {
       printf("List is empty \n");
       return;
    }
    const cJSON* contact = NULL;
    cJSON* contacts = cJSON_GetObjectItemCaseSensitive(json_root_object, "contacts");

    unsigned int index = 0;
    cJSON_ArrayForEach(contact, contacts)
    {
        cJSON* json_id = cJSON_GetObjectItemCaseSensitive(contact, "id");
        
        if (json_id->valueint == id)
        {
            cJSON_DeleteItemFromArray(contacts, index);
        }
        index++;
    }

    s_node* temp = contact_list->head;
    while(temp->next != NULL)
    {
        s_contact* contact = temp->data;
        if (contact->id == id)
        {
            remove_from_list(contact_list, contact);
            printf("Contact removed \n");
            return;
        }
        temp = temp->next;
    }
}

void handle_prompt(s_linked_list* contact_list){
	int input;
    printf("\n Choose Action: \n 1. Find Contact \n 2. Add Contact \n 3. Remove Contact by id \n 4. Save and exit. \n");
    scanf("%d", &input);

    if (input > 4 || input < 1)
    {
    	printf("Please, type in numeric values from 1 to 5 \n");
    	handle_prompt(contact_list);
    }

    if (input == 1)
    {
    	char* name[TEXT_FIELD_MAX_SIZE];
    	printf("Enter person's name: \n");
        scanf("%s", name);

        char* surname[TEXT_FIELD_MAX_SIZE];
    	printf("Enter person's surname: \n");
        scanf("%s", surname);

        char* query = calloc(strlen(name) + strlen(surname) + 1, sizeof(char));

        strcat(query, name);
        strcat(query, surname);
        printf("Searching for name %s \n ", query);
        search_contact(query);
        handle_prompt(contact_list);
    }

    else if (input == 2) 
    {
    	json_write_contact(user_input_add_contact());

	    handle_prompt(contact_list);
    }

    else if (input == 3)
    {
        printf("Write down contact id to remove: \n");
        unsigned int id;
        scanf("%d", &id);
        printf("Trying to remove \n " );
        remove_contact_by_id(id);
        handle_prompt(contact_list);
    }

    else if(input == 4)
    {
        printf("saving data to a file... \n ");
        save_data(DATA_PATH);
        printf("successfuly saved. \n ");
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
