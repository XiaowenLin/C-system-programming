#include <stdio.h>
#include <string.h>

/* (stdin / valid FILE pinter) -> */
void dog(FILE *fp)
{
	char buff;
	/* put every char until EOF */
	while (!feof(fp))
	{
		buff = fgetc(fp);
		if (!feof(fp)) putchar(buff);
	}
}

int main(int argc, char *argv[])
{
	int flag = 0;
  /* no arg provided, repeat keyboard input*/
  if (argc == 1) dog(stdin);
  /* when arg provided, they are considered files */
  else
  {
		int i;
		FILE *fp;
  	for (i = 1; i < argc; ++i)
  	{
			fp = fopen(argv[i], "r");
			/* if the file exists */
			if (fp != NULL)
			{
				dog(fp);
			}
  		else
  		{
  			flag = 1;
  		}
  	}
  }
  return flag;
}
