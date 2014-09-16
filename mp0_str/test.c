#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{
	/* you can free a c string with free(pointer) */
	char *str = malloc(5*sizeof(char));
	strcpy(str, "your");
	puts(str);
	printf("strlen of your is %d", (int)strlen("your"));
	free(str);
	
	/* you can put two adj \0 in one string */
	char *str0 = malloc(2*sizeof(char));
	*str0 = '\0';
	str0[1] = '\0';
	puts(str0);
	free(str0);
	
	/* strlcmp */
	printf("comparing a and b is %d\n", strcmp("a", "b"));
	printf("comparing b and a is %d\n", strcmp("b", "a"));
	printf("comparing ab and b is %d\n", strcmp("ab", "b"));
	printf("comparing a and ab is %d\n", strcmp("a", "ab"));
	printf("comparing a and a is %d\n", strcmp("a", "a"));
	return;
}

