CC=gcc
DFLAG=
FLAGS=-g -std=gnu99 -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare -pthread

all:lab3

lab3:lab3.c lib.o
	$(CC) $(DFLAG) $(FLAGS) $^ -o $@
clean:
	rm -rf lab3
