#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ALLOC_SIZE ( 256 * 1024 * 1024)
#define MAX_ALLOC_SIZE (1536 * 1024 * 1024)

void verify(void *region, int c, size_t len)
{
  char *r = region;
  while (len--)
  {
/*  	  printf("		[verify] %c == %c\n", *(r), (char)c);*/
	  if (*(r++) != (char)c) {
/*		printf("		[verify] %c != %c\n", *(r-1), (char)c);*/
		exit(1);
	  }
  }
}

int overlap(void *r1, void *r2, size_t len)
{
  return (size_t)r1 <= (size_t)r2 && (size_t)r2 < (size_t)(r1 + len);
}

void verify_overlap2(void *r1, void *r2, size_t len)
{
  if (overlap(r1, r2, len)) {
    printf("Memory regions overlap!\n");
    exit(1);
  }
}

void verify_overlap3(void *r1, void *r2, void *r3, size_t len)
{
  if (overlap(r1, r2, len) || overlap(r1, r3, len) || overlap(r2, r3, len)) {
    printf("Memory regions overlap!\n");
    exit(1);
  }
}

void *malloc_and_break(void *region, int c, size_t len)
{
  printf("	[malloc_and_break]\n");
  if (len < MIN_ALLOC_SIZE) {
    printf("	[malloc_and_break] region\n");
    return region;
  }
  printf("	[malloc_and_break] -> void *sr1 = [realloc](%p, %lu MB, %lu KB/ 3);\n", region, len/1024/1024, len/1024);
  void *sr1 = realloc(region, len / 3);
  printf("	[malloc_and_break] <- void *sr1 = [realloc](%p, %lu MB, %lu KB/ 3);\n", region, len/1024/1024, len/1024);
  printf("	[malloc_and_break] -> void *sr2 = malloc(%lu MB, %lu KB/ 3);\n",len/1024/1024, len/1024);
  void *sr2 = malloc(len / 3);
  printf("	[malloc_and_break] <- void *sr2 = malloc(%lu MB, %lu KB/ 3);\n",len/1024/1024, len/1024);
  printf("	[malloc_and_break] -> void *sr3 = malloc(%lu MB, %lu KB/ 3);\n",len/1024/1024, len/1024);
  void *sr3 = malloc(len / 3);
  printf("	[malloc_and_break] <- void *sr3 = malloc(%lu MB, %lu KB/ 3);\n",len/1024/1024, len/1024);

/*  printf("	[malloc_and_break] -> [verify_overlap3]\n");*/
  verify_overlap3(sr1, sr2, sr3, len / 3);
  
/*  printf("	[malloc_and_break] -> [verify]\n");*/
  verify(sr1, c, len / 3);

  memset(sr1, 0xab, len / 3);
  memset(sr2, 0xcd, len / 3);
  memset(sr3, 0xef, len / 3);
  free(sr2);

  sr1 = malloc_and_break(sr1, 0xab, len / 3);
  sr3 = malloc_and_break(sr3, 0xef, len / 3);

  sr1 = realloc(sr1, len / 2);
  sr3 = realloc(sr3, len / 2);

/*  printf("	[malloc_and_break] -> [verify]\n");*/
  verify(sr1, 0xab, len / 3);
  verify(sr3, 0xef, len / 3);

  memset(sr1, 0xab, len / 2);
  memset(sr3, 0xef, len / 2);

  verify_overlap2(sr1, sr3, len / 2);
  free(sr3);

  sr1 = realloc(sr1, len);
  verify(sr1, 0xab, len / 2);

  memset(sr1, c, len);

  return sr1;
}

int main()
{
/*	printf("<main> --> \n");*/
	printf("<main> --> malloc(1)\n");
	malloc(1);
	printf("<main> <-- \n");
  	size_t len = MAX_ALLOC_SIZE;
  	while (len > MIN_ALLOC_SIZE) {
/*    printf("<main> --> \n");*/
	printf("<main> --> malloc(%lu MB, %lu KB)\n", len/1024/1024, len/1024);
    void *mem = malloc(len);
    printf("<main> <-- \n");
    
    memset(mem, 0x6f, len);
/*    printf("<main> mem=%s, len=%lu\n", (char *)mem, len);*/
    
    printf("<main> --> [free]\n");
    free(malloc_and_break(mem, 0x6f, len));
    printf("<main> <-- [free]\n");
    len /= 3;
  }
	printf("Memory was allocated and freed!\n");	
	return 0;
}

