#include <stddef.h>
#include <stdlib.h>
#include "s_node.h"
#include "common.h"

#ifndef LinkedList_H_  
#define LinkedList_H_

typedef struct { struct s_node *head;  struct s_node *tail; int length; } s_linked_list;

s_linked_list *v_list_create();

bool v_list_push(s_linked_list *list, void *data);

void v_list_remove(s_linked_list *list, void* node);

void v_list_remove_first(struct s_node *head);

void v_list_remove_last(s_linked_list* list);

int v_list_length();

bool v_list_is_empty();

void* v_list_last_element(s_linked_list* list);
#endif


