#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#define MAX 4096

/* (file pointer) -> matrx
convert a file into array */
char **toarray(FILE *fp, int *err, int *myc)
{
	/* malloc for array */
	int cap = MAX;

/*	printf("count%d\n", count);*/
	char **array;
	array = malloc(sizeof(char*)*cap); /* IMPORTANT the extra space if used to indicate the end */
/*	puts("malloc good");*/
	int itr;
	for (itr = 0; itr < cap; itr++){
/*		printf("c=%d, itr=%d\n", count, itr);*/
		array[itr] = NULL;
	}
	/* get everyline */
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t read;
	int i = 0;
	while ((read = getline(&lineptr, &n, fp)) != -1) {
/*		if (read == 0) break;*/
		if (read > 0) array[i] = malloc(sizeof(char)*(read));
		strcpy(array[i], lineptr);
		i++;
	}
	*myc = i;
	free(lineptr);
	return array;
}

/* (char**) -> max len */
int mlen(char **mat)
{
	int i = 0;
	int ml = 0;
	int len = 0;
	while (mat[i] != NULL) /* wihtout extra space, accessing mat[count + 1] is not permitted */
	{
		len = strlen(mat[i]);
		if (len > ml) ml = len;
		i++;
	}
	return ml;
}

/* rfind the first valid index */
int trunck(char *orig)
{
	int n = strlen(orig);
	int itr;
	for (itr = n - 1; itr > -1; itr--)
		if (!isspace(orig[itr])) break;
	return itr;
}

/* clean array: no tailing */
void clnarr(char **mat, int nrow)
{
	int i;
	int end;
	int ln;
	for (i = 0; i < nrow; i++)
	{
		end = trunck(mat[i]);
/*		printf("---test clean---%d---\n", end);*/
		ln = strlen(mat[i]);
		int j;
		for (j=end+1; j<ln; j++)
		{
/*			puts("********");*/
/*			printf("clean----->%c\n", mat[i][j]);*/
			mat[i][j] = '\0';
		}
	}
}

/* (const char**, const int, ) -> putc
print one column indicated by i */
void putCol(char **mat, int nrow, int i, int rflag)
{
	/**/
	int itr;
	int len;
	if (!rflag)
	{
		for (itr = nrow - 1; itr > -1; itr--)
		{
			len = strlen(mat[itr]);
			if (i < len && mat[itr][i] != '\n') putchar(mat[itr][i]);
			else putchar(' ');
		}
	}
	else
	{
		for (itr = 0; itr < nrow; itr++)
		{
			len = strlen(mat[itr]);
			if (i < len && mat[itr][i] != '\n') putchar(mat[itr][i]);
		
			else putchar(' ');
		}	
	}
	puts("");
}

/*  */
void putAll(char **mat, int nrow, int *err, int rflag, int bflag)
{
	int ml = mlen(mat);
	int i;
	
	if (!bflag)
	{
		clnarr(mat, nrow);
	}
	if (!rflag)
	{
		for (i = 0; i < ml-1; i++)
			putCol(mat, nrow, i, rflag);
	}
	else
	{
		for (i = ml-2; i > -1; i--)
			putCol(mat, nrow, i, rflag);	
	}
}

int main(int argc, char *argv[])
{
	/* get opts and argv */
	extern char *optarg;
	extern int optind;
	int c, err = 0;
	int rflag = 0, bflag = 0;
	while ((c = getopt(argc, argv, "rb")) != -1)
	switch (c) 
	{
		case 'r':
			rflag = 1;
			break;
		case 'b':
			bflag = 1;
			break;
		case '?':
			err = 1;
			break;
	}
	
	/* no arg provided */
	if (optind == argc)
	{
			char ** mat; 
			int count = 0;
			mat = toarray(stdin, &err, &count);
			putAll(mat, count, &err, rflag, bflag);
			int h;
			for (h = 0; h < count; h++)
				free(mat[h]);
			free(mat);
	}
	/* one pattern and one or more file provided */
	else
	{
		FILE *fp;
		int i;
		for (i = optind; i < argc; ++i)
		{
			char ** mat; 
			fp = fopen(argv[i], "r");
			if (fp == NULL) {
				err = 1;
				continue;
			}
			int count = 0;
			mat = toarray(fp, &err, &count);
/*			rot(mat, count, &err, rflag, bflag);*/
			putAll(mat, count, &err, rflag, bflag);
			int h;
			for (h = 0; h < count; h++)
				free(mat[h]);
			free(mat);
			fclose(fp);
		}
	}

/*	printf("err is %d\n", err);*/
	return err;
}


