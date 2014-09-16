#include <stdlib.h>
#include <stdio.h>

typedef struct _rbn
{
	void *blc;
	int bt;
	size_t sz;
	struct _rbn *lc;
	struct _rbn *rc;
	struct _rbn *p;
}rbn;

static rbn base;

int main()
{
	printf("size of rbn %lu\n", sizeof(base));
	return 0;
}

void add(rbt *ptr)
{}

void balance(brt *ptr)
{}

rbn *bsch(rbn tree, size_t size)
{
	/* return null */
	/* return the best-fit node */
}

void *resize(rbn *nd, size_t nu) /* nd->sz > nu */
{
	rbn* ptr = nd + 1 + nu; /* split the block */
	ptr->sz = nd->sz - 1 - nu;
	nd->sz = nu;
	/* add residue back to tree */
	add(ptr);
	/* return */
	balance(nd);
	nd++;
	return (void *)nd;
}

rbn *rqst(size_t n)
{
	rbn * ret;
	size_t unit = sizeof(rbn);
	size_t bsize = unit * n;
	ret = (rbn *)sbrk(bsize + unit); 
	if (ret == (void *)-1) perror("rqst fail");
	ret->sz = n;
	return ret;
}

rbn *next(brn* ptr)
{
	return ptr + 1 + ptr->sz;
}

void *malloc(size_t size)
{
	if (size == 0) return NULL;
	size_t nu = size / sizeof(rbn);
	brt *ret = bsch(nu);
	if (ret == NULL) return rqst(nu); /* null: rqst, return */
	if (ret->sz == nu) return ++ret; /* equal: remove from tree, return */
	return resize(ret, nu); /* small: resize, balance, return */
}

void free(void *ptr)
{
	if (ptr == NULL) return;
	
}
