#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "libqueue.h"
#include "debug.h"
int main(){
/*	node * nnode =(node*) malloc(sizeof(node));
	nnode->next=NULL;*/
	char *a=(char*)malloc(sizeof(char)*4);
	printf("Before: %p\n",a);
	strncpy(a, "abc", 4);	
/*	nnode->ptr=a;*/
	free(a);
/*	free(nnode);

*/
/*queue_destroy(&test_queue,1);
  puts("Passed all tests (you should add more tests yourself)");
  printf("The size of one node is %lu byte", sizeof(node));*/
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
}
