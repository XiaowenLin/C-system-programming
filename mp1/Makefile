CC=gcc
INC=-I.
DFLAG=
FLAGS=-g -std=gnu99 -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare
ALL=dog findstr twirl
all: $(ALL)
%:%.c
	$(CC) $(DFLAG) $(FLAGS) $(INC) $^ -o $@
clean:
	rm -rf $(ALL)