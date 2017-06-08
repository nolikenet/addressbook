#include "s_node.h"
#include <stddef.h>

#ifndef LinkedList_H_  
#define LinkedList_H_

typedef struct { s_node *head;  s_node *tail; int length; } s_linked_list;

s_linked_list *create_linked_list();

void push_to_list(s_linked_list *list, void *data);

void remove_from_list(s_linked_list *list, void* node);

void remove_first(s_node *head);

void remove_last(s_linked_list* list);

int get_length(s_node *head);
#endif // FOO_H_


