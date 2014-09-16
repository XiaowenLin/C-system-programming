#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>

/* str -> STR */
void toUp(char *str)
{
	int i;
	for (i = 0; i < strlen(str); i++)
		str[i] = toupper(str[i]);
}

/* (string, valid file pointer / stdin) -> string*/
/*#define MAX 4096*/
void findstr(const char *str, FILE *fp, char *filename, int *err, int *flags, int multiple)
{
/*	puts(str);*/
/*	printf("err is %d\n", *err);*/
/*	puts(filename);*/
/*	char mystr[MAX];*/
  char *mystr = NULL;
  size_t len = 0;
  ssize_t read;
	char *ret;
	int nlines = 0;
	if (fp == NULL) fp = fopen(filename, "r");
	int cflag = flags[0], iflag = flags[1], lflag = flags[2], nflag = flags[3], vflag = flags[4];
	/* loop until eof */
	if (fp != NULL)
	{
		int lineN = 1;
/*		while (fgets(mystr, MAX, fp) != NULL)*/
	while ((read = getline(&mystr, &len, fp)) != -1)
		/* read one line and find */
		{
/*			char smystr[MAX], sstr[MAX];*/
			char smystr[read]; 
			strcpy(smystr, mystr);
/*			printf("------%s\n", smystr);*/
			char sstr[strlen(str)];
			strcpy(sstr, str);
/*			printf("======%s\n", sstr);*/
			if (iflag) 
			{
				toUp(smystr);
				toUp(sstr);
			}
			/* match and vflag false */
			if ((strstr(smystr, sstr) != NULL) ^ vflag)
			{
				nlines++;
				if (multiple && !lflag) printf("%s:", filename);
				if (nflag && !cflag && !lflag) printf("%d:", lineN);
				if (!cflag && !lflag) 
					printf("%s", mystr);
				if (lflag) 
				{	
					printf("%s\n", filename);
					if (mystr != NULL) free(mystr);
					return;
				}
			}
			lineN++;
		}
		fclose(fp);
	}
	else
	{
		*err = 1;
		if (cflag) printf("%d\n", nlines);
		if (mystr != NULL) free(mystr);
		return;
	}
	if (cflag) printf("%d\n", nlines);
	if (mystr != NULL) free(mystr);
	return;
}

int main(int argc, char *argv[])
{
	/* get opts and argv */
	extern char *optarg;
	extern int optind;
	int c, err = 0;
	int flags[5] = {0,0,0,0,0};
	int *cflag = flags, *iflag = flags + 1, *lflag = flags + 2, *nflag = flags + 3, *vflag = flags + 4;
	while ((c = getopt(argc, argv, "cilnv")) != -1)
		switch (c) 
		{
			case 'c':
				*cflag = 1;
				break;
			case 'i':
				*iflag = 1;
				break;
			case 'l':
				*lflag = 1;
				break;
			case 'n':
				*nflag = 1;
				break;
			case 'v':
				*vflag = 1;
				break;
			case '?':
				err = 1;
				break;
		}
	if (*nflag == 1 && (*cflag == 1 || *lflag == 1)) 
	{	
		exit(1);
	} 
	else if (*cflag == 1 && *lflag == 1) exit(1);
	
	/* no arg provided */
	else if (optind == argc)
	{
		exit(1);
	}
	/* read from stdin */
	else if (optind + 1 == argc)
	{
		char *str = argv[optind];
		int i;
		int multiple = 0;
		findstr(str, stdin, "", &err, flags, multiple);
	}
	/* no opt, one pattern and one or more file provided */
	else
	{
		FILE *fp;
		char *str = argv[optind];
		int i;
		int multiple = 0;
		if (argc - optind > 2) multiple = 1;
		for (i = optind + 1; i < argc; ++i)
		{
			findstr(str, NULL, argv[i], &err, flags, multiple);
		}
	}
/*	printf("err is %d\n", err);*/
	return err;
}
