#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "libqueue.h"
#include "debug.h"

int main(){
  queue_t test_queue;
  queue_init(&test_queue);
  assert(queue_size(&test_queue)==0);

  char *str=(char *)malloc(sizeof(char)*4);
  /*strcpy(str, "hid");*/
  str = "hid";
  queue_enqueue(&test_queue,str);
  assert(queue_size(&test_queue)==1);
  queue_destroy(&test_queue,1);
  puts("Passed all tests (you should add more tests yourself)");
/*  queue_init(&test_queue);*/
/*  queue_print(&test_queue);*/
/*  assert(queue_size(&test_queue)==0);*/

/*  char str[20]="node";*/
/*  char str0[20]="nob";*/

/*  queue_enqueue(&test_queue,str);*/
/*  queue_print(&test_queue);*/
/*  queue_enqueue(&test_queue,str0);;*/
/*  assert(queue_size(&test_queue)==2);*/
/*  queue_print(&test_queue);*/
/*  queue_dequeue(&test_queue);*/
/*  assert(queue_size(&test_queue)==1);*/
/*  queue_destroy(&test_queue,0);*/
/*  assert(queue_size(&test_queue)==1);*/
/*  puts("Passed all tests (you should add more tests yourself)");*/
/*	queue_t myq;
	queue_init(&myq);
	char s0[]="how";
	char s1[]="are";
	char s2[]="you";
	char s3[]="?";
	queue_enqueue(&myq, s0);
	queue_enqueue(&myq, s1);
	queue_enqueue(&myq, s2);
	queue_enqueue(&myq, s3);

	queue_print(&myq);
	char *ap = queue_dequeue(&myq);
	printf("%s ", ap);
	ap = queue_dequeue(&myq);
	printf("%s ", ap);
	ap = queue_dequeue(&myq);
	printf("%s ", ap);
	ap = queue_dequeue(&myq);
	printf("%s ", ap);
	if (0) printf("0 is true");	
	if (1) printf("1 is true");
 	 return 0;*/
}
