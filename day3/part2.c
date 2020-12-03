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

unsigned int tree_counter(unsigned char *trees, unsigned int h, unsigned int w, unsigned int dw, unsigned int dh)
	{
	unsigned int i, c = 0;
	for (i = dh; i < h; i += dh)
		c += trees[(i * w) + ((i / dh * dw) % w)];
	return c;
	}

int main(int argc, char *argv[])
	{
	unsigned int sz, w;
	unsigned char *trees = read_entries(&sz, &w);
	unsigned long long i = 1;
	unsigned int counts[] =
		{
		tree_counter(trees, sz, w, 1, 1),
		tree_counter(trees, sz, w, 3, 1),
		tree_counter(trees, sz, w, 5, 1),
		tree_counter(trees, sz, w, 7, 1),
		tree_counter(trees, sz, w, 1, 2),
		};
	i *= counts[0];
	i *= counts[1];
	i *= counts[2];
	i *= counts[3];
	i *= counts[4];
	printf("T(1, 1) = %d\n", counts[0]);
	printf("T(3, 1) = %d\n", counts[1]);
	printf("T(5, 1) = %d\n", counts[2]);
	printf("T(7, 1) = %d\n", counts[3]);
	printf("T(1, 2) = %d\n", counts[4]);
	printf("S = %lld\n", i);
	}
