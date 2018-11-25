#include "l_addressbook.h"

cJSON* json_root_object = NULL;

s_linked_list* address_book_init(char* data_path)
{
    s_linked_list* contact_list = create_linked_list();

    printf("contact list addr %p \n", contact_list);

    populate_list_from_buffer(read_storage(data_path), contact_list);
    
    printf("contact list addr 2! %p \n", contact_list);
    return contact_list;
}

void populate_list_from_buffer(char* buff, s_linked_list* contact_list)
{
    json_root_object = cJSON_Parse(buff);
    cJSON* contacts = NULL;
    cJSON* contact = NULL;

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
    printf("contact list addr in populate list %p \n", contact_list);

    s_contact* cont = (s_contact*)contact_list->head->data;
    printf("CONTACT PHONE IS %d \n", cont->phone);
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

s_contact* search_contact(const char* query, s_linked_list* contact_list)
{
    struct s_node* tmp = contact_list->head;


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


bool json_write_contact(s_contact* contact, s_linked_list* contact_list)
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

void remove_contact_by_id(unsigned int id, s_linked_list* contact_list)
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

    struct s_node* temp = contact_list->head;
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
