# build an executable named myprog from myprog.c
all:
	gcc -g -Wall -Wcomment -std=c89 main.c s_linked_list.c common.c s_node.c s_contact.c -o ./bin/debug/output.out

#  clean: 
#	  $(RM) myprog
