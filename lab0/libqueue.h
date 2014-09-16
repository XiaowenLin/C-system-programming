#ifndef _QUEUE_H
#define _QUEUE_H
#include <stddef.h>

typedef struct node{
	void *ptr;
	struct node *next;
} node;

typedef struct queue_t{
	node *head;
	node *tail;
	int size;
} queue_t;

void queue_init(queue_t *q);
void queue_destroy(queue_t *q,int free_ptr);

void queue_enqueue(queue_t *q,void *ptr);
void *queue_dequeue(queue_t *q);
size_t queue_size(queue_t *q);

void queue_print(queue_t *q);
#endif

