all: parmake

parmake: parmake.o queue.o parser.o rule.o
	gcc -O0 -pthread -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare -g -std=gnu99 parmake.o queue.o parser.o rule.o -o parmake

parmake.o: parmake.c
	gcc -O0 -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare -g -std=gnu99 -c parmake.c -o parmake.o

queue.o: queue.c queue.h
	gcc -O0 -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare -g -std=gnu99 -c queue.c -o queue.o

parser.o: parser.c parser.h
	gcc -O0 -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare -g -std=gnu99 -c parser.c -o parser.o

rule.o: rule.c rule.h
	gcc -O0 -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare -g -std=gnu99 -c rule.c -o rule.o

clean:
	rm -rf *.o parmake


