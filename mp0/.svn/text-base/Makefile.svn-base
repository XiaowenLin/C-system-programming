CC=gcc
INC=-I.
DFLAG=
FLAGS=-g -std=gnu99 -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare

all: main

main: main.c libtrie.o libqueue.o
	$(CC) $(DFLAG) $(FLAGS) $^ -o $@
%.o: %.c %.h 
	$(CC) $(DFLAG) $(FLAGS) $(INC) -c $<
libqueue.o: ../lab0/libqueue.c ../lab0/libqueue.h
	$(CC) $(DFLAG) $(FLAGS) $(INC) -c $<
.PHONY : clean
clean:
	-rm -f *.o main
