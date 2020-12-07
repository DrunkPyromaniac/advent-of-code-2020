#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

unsigned int *read_entries(unsigned int *sz)
	{
	unsigned int i = 0, size = 0, *ret = NULL, j;
	char *answers, spaces[1024], c[26];
	int v;
	memset(c, 0, sizeof(c));
	do
		{
		v = scanf("%ms%[ \n]", &answers, spaces);
		if (answers)
			for (j = 0; j < strlen(answers); j++)
				c[answers[j] - 'a'] = 1;
		if (strstr(spaces, "\n\n") || v == EOF)
			{
			if (i == size)
				{
				size += 50;
				ret = realloc(ret, size * sizeof(*ret));
				}
			ret[i] = 0;
			for (j = 0; j < sizeof(c) / sizeof(c[0]); j++)
				ret[i] += c[j];
			memset(&c, 0, sizeof(c));
			i++;
			}
		free(answers);
		} while (v != EOF);
	if (sz)
		*sz = i;
	return ret;
	}

int main(int argc, char *argv[])
	{
	unsigned int sz, i, c = 0;
	unsigned int *q = read_entries(&sz);
	for (i = 0; i < sz; i++)
		c += q[i];
	printf("V = %d\n", c);
	}
