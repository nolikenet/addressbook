# build an executable named myprog from myprog.c
all:
	gcc -g -Wall main.c s_linked_list.c common.c s_node.c s_contact.h s_contact.c

#  clean: 
#	  $(RM) myprog