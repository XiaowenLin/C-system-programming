#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef PART2
  #define NUM_CYCLES 5
#else
  #define NUM_CYCLES 5
#endif

int main()
{
	// test malloc and free general
	printf("<main> malloc %d, nu = %d\n", 200, 13);
	void *ptr = malloc(200);
	printf("<free>\n");
	free(ptr);
	
	// test left merge
	printf("<main> malloc %d, nu = %d\n", 100, 7);
	int *ptr1 = malloc(100);
	free(ptr1);
	// test right merge
	int *ptr2 = malloc(50);
	int *ptr3 = malloc(50);
	free(ptr2);
	
	// 
	char h[] = "put something between malloc?";
	printf("<main> malloc %d, nu = %d\n", 500, 32);
	long *ptr4 = malloc(500);
	free(ptr4);
	
	printf("<main> malloc %d, nu = %d\n", 120, 7);
	char *ptr5 = malloc(120);
	printf("<main> malloc %d, nu = %d\n", 120, 7);
	long *ptr6 = malloc(120);
	printf("<main> malloc %d, nu = %d\n", 120, 7);
	long *ptr7 = malloc(120);
	free(ptr6);
	
	// more bytes realloc
   strcpy(ptr5,"This is string.h library function");
   puts(ptr5);

   memset(ptr5,'$',7);
   puts(ptr5);
   puts("--------------------------");
   char *str = realloc(ptr5, 3);
   puts(str);
}
