#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

/**
 * (Edit this function to print out the ten "Illinois" lines in functions.c in order.)
 */
int main()
{
	first_step(81);
	
	int second_value = 132;
	int *second_p = &second_value;
	second_step(second_p);

	
	int third_value = 8942;
	int *third_p = &third_value;
	int **third_pp = &third_p;
	double_step(third_pp);

	int *forth_value = 0;
	strange_step(forth_value);

	void *fifth_value[] = {0, 0, 0, 0};
	empty_step(fifth_value);
	
	char *s2 = "uuuu";
	void *s = s2;
	two_step(s, s2);
	
	char *first, *second, *third;
	first = 0;
	second = first + 2;
	third = second + 2;
	three_step(first, second, third);
		
	char *arr = malloc(4*sizeof(char));
	arr[1] = 'a';
	arr[2] = arr[1] + 8;
	arr[3] = arr[2] + 8;
	step_step_step(arr, arr, arr);
	free(arr);
	
	int b = 1;
	void *a = &b;
	it_may_be_odd(a, b);	
	
	int end = 1281;
	void *orange, *blue;
	orange = blue = &end;
	the_end(orange, blue);	
	
	return 0;
}
