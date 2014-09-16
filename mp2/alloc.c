/** @file alloc.c */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
/* size of atom is 32 bytes */
typedef struct atom
{
    size_t nunit;
    size_t flag;
    struct atom *next;
    struct atom *prev;
}atom;

static atom *pos = NULL;
static atom base;


void *calloc(size_t num, size_t size)
{
	void *ptr = malloc(num * size);
	
	if (ptr)
		memset(ptr, 0x00, num * size);

	return ptr;
}

atom *reqst(size_t bsize, size_t unit, size_t n)
{
	atom * p;
	p = (atom *)sbrk(bsize + unit); 
	if (p == (void *)-1) perror("reqst fail");
	p->nunit = n;
	p->flag = 0;
	p->next = p->prev = &base;
	return p;
}

atom *search(size_t size, size_t n)
{
	/* if base has been initialized, search for one block satisfies*/
	pos = base.next;
	while (pos != &base)
	{
		if (pos->nunit >= n) break;
		pos = pos->next;
	}
	return pos;
}

void *malloc(size_t size)
{
	printf("	[malloc]\n");
	if (size == 0) return NULL;
	
	/* initialize base and pos */
	if (pos == NULL) 
	{
		pos = base.prev = base.next = &base;
		base.nunit = 0;
		base.flag = 1;
	}
	
	size_t unit = sizeof(atom);
	size_t n = (size - 1) / unit + 1; /* num of units required by user */
	size_t bsize = n * unit; /* bytes will be used by user */
	
	pos = search(size, n);
	printf("	[malloc] break at %p\n", pos);
	
	/* if no enough space to return to user, 
		request memory from sys and return */
	/* if no space has been sbrked for malloc, request memory from sys */
	if (pos == &base)
	{
		printf("[malloc] ->reqst \n");
		atom *ret = reqst(bsize, unit, n);
		if (ret == NULL) return NULL;
		ret++;
		printf("[malloc] <-reqst return pointer at %p\n", ret);
		return (void *)ret;
	}
	
	/* if enough space found, 
			size equals, return this block, 
			bigger than required, partition the later part of the block, reset metadata, and return the later part to user */
	if (pos != &base && pos->nunit > n) 
	{
		pos->nunit = pos->nunit - n - 1;
		/* set itr */
		atom *itr = pos + pos->nunit + 1;
		itr->nunit = n;
		itr->flag = 0;
		itr->prev = pos;
		itr->next = pos->next;
		itr++;
		return itr;
	}
	if (pos != &base && pos->nunit == n)
	{
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		pos->flag = 0;
		printf("[malloc] return to user from pool block equlas need\n");
		atom *ret = pos + 1;
		return ret;
	}
	return NULL;
}

void printall()
{
	pos = &base;
	atom *itr = pos->next;
	// printf("	[----] %p\n", itr);
	// puts("");
	size_t i;
	while (itr != &base)
	{
		printf("	[printblock] units in block %lu\n", itr->nunit + 1);
		printf("	[printlink] %p -> %p\n", itr, itr->next);
		itr = itr->next;
	}
// 	printf("	[printpool] %p\n", itr+ i);
}

/* ptr points right after header */
void free(void *ptr)
{
	// "If a null pointer is passed as argument, no action occurs."
	if (ptr == NULL)
		return;
		
	/* locator: (ptr, pos, base) -> prev block */
	atom *mptr = (atom *)ptr;
	pos = mptr - 1;
	pos = pos->next;
	while (1) 
	{
		pos = pos->prev;
		if (pos < mptr) break;
	}

	/* connector & merger: connect returned block from user */
	atom *big = pos;
	atom *mid = pos->next = mptr - 1;
	atom *end = pos->next->next;
	end->prev = mid;
	mid->next = end;
	mid->prev = big;
	mid->flag = 1;
	printf("	[free] %p -> %p -> %p\n", big, mid, end);
	/* merger: (big) -> void */
	/* right */
	printf("	[detect] %p + 1 + %lu == %p\n", mid, mid->nunit, end);
	if (mid + 1 + mid->nunit == end && end != &base)
	{ 
		mid->nunit = mid->nunit + 1 + end->nunit;
		mid->next = end->next; 
		end = mid->next;
		end->prev = mid;
		printf("	[free] right merger\n");
	}
	/* left */
	printf("	[detect] %p + 1 + %lu == %p\n", big, big->nunit, mid);
	if (big + 1 + big->nunit == mid && big != &base)
	{ 
		big->nunit = big->nunit + 1 + mid->nunit;
		big->next = mid->next; 
		end->prev = big;
		printf("	[free] left merger\n");
	} 
/*	printall();*/
}


void *realloc(void *ptr, size_t size)
{
	/* if ptr is NULL, malloc size bytes for user */
	if (ptr == NULL) return malloc(size);
	/* if ptr not NULL and size is 0, free block and return NULL*/
	if (size == 0) { free(ptr); return NULL; }
	
	atom *oatm = (atom *)ptr - 1;
	size_t nunit = (size - 1) / sizeof(atom) + 1;
	/* if size is similar, don't change */
	if (oatm->nunit == nunit)
	{
//		printf("%lu == %lu\n", oatm->nunit, nunit);
		return ptr;
	}
	/* if size is smaller, shrink */
	if (oatm->nunit > nunit)
	{
//		printall();
//		printf("%lu > %lu\n", oatm->nunit, nunit);
		oatm->nunit = oatm->nunit - 1 - nunit;
		atom *ret = oatm + 1 + oatm->nunit;
		ret->flag = 0;
		ret->next = oatm->next;
		free(++oatm);
		return ++ret;
	}
/*	printf("%lu < %lu\n", oatm->nunit, nunit);*/
	/* if size is bigger, malloc new */
	void *nptr = malloc(size);
/*	printf("[realloc] memcpy size=%lu\n", sm);*/
	
	/* #if size is bigger, extend user block */
	/* #if size is bigger, malloc block, and free current */
	memcpy(nptr, ptr, oatm->nunit * sizeof(atom));
  	free(ptr);
/*  	printf("[realloc] <--------------------------------\n");*/
	return nptr;
}


