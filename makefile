# build an executable named myprog from myprog.c
# -Werror 
SRC = $(wildcard src/deps/*.c) $(wildcard src/misc/*.c) $(wildcard src/data_structures/*.c) $(wildcard src/entities/*.c) $(wildcard src/ui/*.c) $(wildcard src/*.c) 
CFLAGS = -I ./include -std=c99 -Wall -Wno-unused -g

all:
	clang $(CFLAGS) $(SRC) -o ./bin/debug/output

#  clean: 
#	  $(RM) myprog
