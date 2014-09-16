#include <stdlib.h>
#include "libqueue.h"
#include "debug.h"
#include <stdio.h>
void queue_init(queue_t *q)
{
	q->head = q->tail = NULL;
	q->size = 0;
}

/* ptr: data to be queued */
void queue_enqueue(queue_t *q,void *ptr)
{
	node *nnode = (node *)malloc(sizeof(node));
	nnode->ptr = ptr;
	nnode->next = NULL;
	if (q->size == 0) q->head = q->tail = nnode;
	else {
		q->tail->next = nnode;
		q->tail = nnode;
	}
	q->size++;
}

void *queue_dequeue(queue_t *q)
{
	if (q->size == 0) return NULL;
	node *tmp = q->head;
	if (q->size == 1) q->head = q->tail = NULL;
	else q->head = q->head->next;
	q->size--;
	void *ret = tmp->ptr;
	free(tmp);
	return ret;
}

/* free data only when free_ptr evaluates to true */
void queue_destroy(queue_t *q,int free_ptr)
{
	node *holder = q->head;
	node *remover = holder;
	while (holder != NULL){
		holder = remover->next;
		if (free_ptr) free(remover->ptr);
		free(remover);
		remover = holder;
	}
}

size_t queue_size(queue_t *q){
	return q->size;
}

/* this function is not graded (but it shouldn't segfault), it's up to you how the queue should be printed */
void queue_print(queue_t *q){
	node *p = q->head;
	while (p != NULL){
		printf("%s\n", (char *)p->ptr);
		p = p->next;
	}
}
