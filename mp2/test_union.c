/** @file alloc.c */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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

int main()
{
	printf("size of union is %lu\n", sizeof(unt));
	unt myunt, myu1;
	myunt.atom.nunit = 100;
	myu1.atom.nunit = 500;
	myunt.atom.next = &myu1;
	printf("size of unt is %lu\n", sizeof(myunt));
	printf("size of atom is %lu\n", sizeof(myunt.atom));
	printf("value of nunit is %lu\n", myunt.atom.nunit);
	printf("next to myunt is %p\n", myunt.atom.next);

}
