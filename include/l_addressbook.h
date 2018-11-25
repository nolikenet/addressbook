#include <stdio.h>
#include <string.h>
#include "deps/cJSON.h"
#include "s_contact.h"
#include "data_structures/s_linked_list.h"
#include "common.h"

#ifndef AddressBook_H_ 
#define AddressBook_H_

s_linked_list* address_book_init(char* data_path);

void populate_list_from_buffer(char* buff, s_linked_list* contact_list);

s_contact* search_contact(const char* query, s_linked_list* contact_list);

char* read_storage(char* path);

bool json_write_contact(s_contact* contact, s_linked_list* contact_list);

void save_data(const char* path);

void remove_contact_by_id(unsigned int id, s_linked_list* contact_list);

#endif
