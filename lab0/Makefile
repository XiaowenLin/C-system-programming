CC=gcc
DFLAG=
FLAGS=-g -Wall

all:lab0

lab0:lab0.c libqueue.o
	$(CC) $(DFLAG) $(FLAGS) $^ -o $@
%.o:%.c %.h
	$(CC) $(DFLAG) $(FLAGS) -c $<
clean:
	rm -rf lab0 *.o
