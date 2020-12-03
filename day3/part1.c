#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

unsigned char *read_entries(unsigned int *sz, unsigned int *width)
	{
	unsigned int i = 0, size = 0, w, j;
	char *line;
 	unsigned char *ret = NULL;
	*width = 0;
	while (scanf("%ms", &line) != EOF)
		{
		w = strlen(line);
		if (!*width)
			*width = w;
		else if (*width != w)
			{
			printf("Gah!\n");
			exit(0);
			}
		if (i == size)
			{
			size += 50;
			ret = realloc(ret, size * w);
			}
		for (j = 0; j < w; j++)
			ret[(i * w) + j] = line[j] == '#';
		free(line);
		i++;
		}
	if (sz)
		*sz = i;
	return ret;
	}

int main(int argc, char *argv[])
	{
	unsigned int sz, w, i, c;
	unsigned char *trees = read_entries(&sz, &w);
	for (i = 0; i < sz; i++)
		c += trees[(i * w) + ((i * 3) % w)];
	printf("T = %d\n", c);
	}
