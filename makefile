# build an executable named myprog from myprog.c
# -Werror 
SRC = $(wildcard src/*.c) $(wildcard src/*/*.c)
CFLAGS = -I ./include -std=c99 -Wall -Wno-unused -g

all:
	clang $(CFLAGS) $(SRC) -o ./bin/debug/output

#  clean: 
#	  $(RM) myprog
