CC = gcc
INC = -I.
FLAGS = -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare -g -std=gnu99

all: main

main: main.o functions.o
	$(CC) $^ -o $@

functions.o: functions.c functions.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@

main.o: main.c
	$(CC) -c $(FLAGS) $(INC) $< -o $@

.PHONY : clean
clean:
	-rm -r -f *.o main
