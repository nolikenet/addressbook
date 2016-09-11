#include "s_node.h"all

#ifndef LinkedList_H_  
#define LinkedList_H_

struct s_linked_list
{
	Node *head;
	Node *tail;
};

typedef struct s_linked_list LinkedList;

void push(Node *head, void *data);

void remove_first(Node *head);

void remove_last(Node *head);

int get_length(Node *head);
#endif // FOO_H_


