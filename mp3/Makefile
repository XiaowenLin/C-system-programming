CC=gcc
INC=-I.
DFLAG=
FLAGS=-g -std=gnu99 -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare -pthread

all: main

main: main.c scheduler.o parsort.o register.o
	$(CC) $(DFLAG) $(FLAGS) $^ -o $@
%.o: %.c %.h 
	$(CC) $(DFLAG) $(FLAGS) $(INC) -c $<

.PHONY : clean
clean:
	-rm -f parsort.o register.o main
