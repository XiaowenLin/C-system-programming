/** @file alloc.c */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


/* size of atom is 16 bytes */
union _u
{
	struct _atom
	{
		size_t nunit;
		union _u *next;
	}atom;
	
	struct
	{
		void *p1;
		void *p2;
		void *p3;
		void *p4;
	};
};

typedef union _u unt;

static unt *pos = NULL;
static unt base;

void printall()
{
/*	printf("	[printall] ++++++++++++++++++++++++++++++++++>\n");*/
	pos = &base;
	unt *itr = pos->atom.next;
	// printf("	[----] %p\n", itr);
	// puts("");
	size_t i = 0;
	size_t tsize = 0;
	printf("		[printchain] ");
	while (itr != &base)
	{
/*		printf("	[printblock] units in block %lu\n", itr->nunit + 1);*/
/*		for (i = 0; i < itr->nunit + 1; i++)*/
/*		{*/
/*			printf("	[printpool] %p\n", itr+ i);*/
/*		}*/
// 		printf("	[printpool] %p\n", itr);
/*		printf("	[printlink] %p -> %p\n", itr, itr->next);*/
/*		printf("	[printpool] i=%lu memory=%lu MB, %lu KB\n", i, itr->nunit*sizeof(atom)/1024/1024, itr->nunit*sizeof(atom)/1024);*/
		tsize += itr->atom.nunit;
		printf("%p(%luMB, %lu KB) -> %p(%luMB, %lu KB) -> ", itr, itr->atom.nunit*sizeof(unt)/1024/1024, itr->atom.nunit*sizeof(unt)/1024, itr->atom.next, itr->atom.next->atom.nunit*sizeof(unt)/1024/1024, itr->atom.next->atom.nunit*sizeof(unt)/1024);
		itr = itr->atom.next;
		i++;
	}
	puts("");
/* 	printf("	[printpool] block#=%lu total memory usage %lu MB, %lu KB\n", i, tsize*sizeof(atom)/1024/1024, tsize*sizeof(atom)/1024);*/
/* 	printf("	[printall] <++++++++++++++++++++++++++++++++++\n");*/
}

void *calloc(size_t num, size_t size)
{
	/* Note: This function is complete. You do not need to modify it. */
	void *ptr = malloc(num * size);
	
	if (ptr)
		memset(ptr, 0x00, num * size);

	return ptr;
}

/* (size) -> pointer to the first unit, which contains metadata
size number of bytes 
next to NULL */
unt *reqst(size_t bsize, size_t unit, size_t n)
{
	unt * p;
	p = (unt *)sbrk(bsize + unit); /* one extra unit for metadata */
/*	if (p == (void *)-1) perror("reqst fail");*/
	/* in the first unit, setup metadata */
	p->atom.nunit = n;
/*	printf("	[reqst] %lu+1 atoms from %p to %p\n", n, p, p+n);*/
	return p;
}

void *malloc(size_t size)
{
	printf("	[malloc]\n");
	if (size == 0) return NULL;
	/* initialize base and pos */
	if (pos == NULL) 
	{
		pos = base.atom.next = &base;
		base.atom.nunit = 0;
	}
	unt *ret;
	unt *itr;
	unt *prev;
	size_t unit = sizeof(unt);
	size_t n = (size - 1) / unit + 1; /* num of units required by user */
	size_t bsize = n * unit; /* bytes will be used by user */
	/* if base has been initialized, search for one block satisfies*/
	size_t i;
	prev = &base;
	pos = base.atom.next;
	while (pos != &base)
	{
		if (pos->atom.nunit >= n) break;
		prev = pos;
		pos = pos->atom.next;
	}
/*	printf("	[malloc] break at %p\n", pos);*/
	/* if no enough space to return to user, 
		request memory from sys and return */
	/* if no space has been sbrked for malloc, request memory from sys */
	if (pos == &base)
	{
		printf("	[malloc] ->reqst bsize=%lu MB \n", bsize/1024/1024);
		ret = reqst(bsize, unit, n);
		if (ret == NULL) return NULL;
		ret++;
		printf("	[malloc] <-reqst return pointer at %p\n", ret);
		printall();
		return (void *)ret;
	}
	/* if enough space found, 
			size equals, return this block, 
			bigger than required, partition the later part of the block, reset metadata, and return the later part to user */
	if (pos != &base && pos->atom.nunit > n) 
	{
		pos->atom.nunit = pos->atom.nunit - n - 1;
		itr = pos + pos->atom.nunit + 1;
		itr->atom.nunit = n;
		itr->atom.next = NULL;
		ret = itr + 1;
/*		printf("[malloc] return %lu to user from pool ptr = %p cur pos unit=%lu\n", n, ret, pos->nunit);*/
		printall();
		return (void *)ret;
	}
	if (pos != &base && pos->atom.nunit == n)
	{
		ret = pos + 1;
		prev->atom.next = pos->atom.next;
/*		printf("[malloc] return to user from pool block equlas need\n");*/
		printall();
		return (void *)ret;
	}
	return NULL;
}

/* ptr points right after header */
void free(void *ptr)
{
/*	printf("	[free]\n");*/
	// "If a null pointer is passed as argument, no action occurs."
	if (ptr == NULL)
		return;
		
	/* locator and connector: (ptr, pos, base) -> prev block */
	pos = &base;
	unt *next = pos->atom.next;
	unt *mptr = (unt *)ptr;
	printf("	[free]\n");
	while (next != &base)
	{
		/* if ptr is between two blocks */
		/* if ptr is very first */
		/* if ptr is very last */
		if (
			(mptr > pos && mptr < next) ||
			(mptr < pos && mptr < next && next < pos) ||
			(mptr > pos && mptr > next && next < pos)		
		)
		{
			break;
		}
		pos = next;
		next = pos->atom.next;
	}
	/* connect returned block from user */
	unt *big = pos;
	unt *mid = pos->atom.next = mptr - 1;
	unt *end = pos->atom.next->atom.next = next;
	printf("		[free] %p -> %p -> %p\n", big, mid, end);
	/* merger: (big) -> void */
	/* right */
/*	printf("	[detect] %p + 1 + %lu == %p\n", mid, mid->nunit, end);*/
	if (mid + 1 + mid->atom.nunit == end && end != &base)
	{ 
		mid->atom.nunit = mid->atom.nunit + 1 + end->atom.nunit;
		mid->atom.next = end->atom.next; 
		end = mid->atom.next;
		printf("		[free] right merger\n");
	}
	/* left */
/*	printf("	[detect] %p + 1 + %lu == %p\n", big, big->nunit, mid);*/
	if (big + 1 + big->atom.nunit == mid && big != &base)
	{ 
		big->atom.nunit = big->atom.nunit + 1 + mid->atom.nunit;
		big->atom.next = mid->atom.next; 
		printf("		[free] left merger\n");
	} 

	printall();
}


void *realloc(void *ptr, size_t size)
{
	printf("	[realloc]\n");
	/* if ptr is NULL, malloc size bytes for user */
	if (ptr == NULL) 
		return malloc(size);
	/* if ptr not NULL and size is 0, free block and return NULL*/
	if (size == 0) 
	{
		free(ptr); 
		return NULL; 
/*		printf("	return from [realloc]\n");*/
	}
	
	unt *oatm = (unt *)ptr - 1;
	size_t nunit = (size - 1) / sizeof(unt) + 1;
	/* if size is similar, don't change */
	if (oatm->atom.nunit == nunit)
	{
		printf("		[realloc] exact: ptr %p %lu MB\n", oatm, oatm->atom.nunit*sizeof(unt)/1024/1024);
		return ptr;
	}
	/* if size is smaller, shrink */
	if (oatm->atom.nunit > nunit)
	{
/*		printall();*/
		unt *tofr = oatm + 1 + nunit;
		tofr->atom.nunit = oatm->atom.nunit - nunit - 1;
		oatm->atom.nunit = nunit;
		printf("		[realloc] left to user: ptr %p %lu MB \n", oatm, oatm->atom.nunit*sizeof(unt)/1024/1024);
		tofr++;
		printf("		[realloc] ->\n");
		free(tofr);
		printf("		[realloc] <-\n");
		return ptr;
	}
/*	printf("	[realloc] malloc %lu < %lu\n", oatm->nunit, nunit);*/
	/* if size is bigger, malloc new */
	void *nptr = malloc(size);
/*	printf("[realloc] memcpy size=%lu\n", sm);*/
	
	/* #if size is bigger, extend user block */
	/* #if size is bigger, malloc block, and free current */
	memcpy(nptr, ptr, oatm->atom.nunit * sizeof(unt));
  	free(ptr);
/*  	printf("[realloc] <--------------------------------\n");*/
	return nptr;
}


