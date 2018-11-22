#include <stdio.h>
#include "ui/user_input.h"
#include "data_structures/s_linked_list.h"

const char* DATA_PATH = "data/data.json";

int main()
{
    s_linked_list* list = address_book_init(DATA_PATH);	

    printf("contact list addr in main %p \n", list);
    s_contact* item = (s_contact*)list->head->data;
    printf("contact list address... %p \n ", list);
    printf("HEAD name data is... %s \n ", item->surname);

	handle_prompt(list, DATA_PATH);

	return 0;
}
