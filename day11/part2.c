#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define NOT_SEAT '.'
#define EMPTY 'L'
#define FULL '#'
#define FILLING 'F'
#define EMPTYING 'E'

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
			ret[(i * w) + j] = line[j];
		free(line);
		i++;
		}
	if (sz)
		*sz = i;
	return ret;
	}

unsigned char is_full(unsigned char *s, unsigned int width, unsigned int sz, unsigned int down, unsigned int right, signed char dd, signed char dr)
	{
	down += dd;
	right += dr;
	while (down < sz && right < width)
		{
		if (s[down * width + right] != NOT_SEAT)
			return s[down * width + right] == EMPTYING || s[down * width + right] == FULL;
		down += dd;
		right += dr;
		}
	return 0;
	}

unsigned char adj_count(unsigned char *s, unsigned int down, unsigned int right, unsigned int width, unsigned int sz)
	{
	unsigned char c = 0;
	c += is_full(s, width, sz, down, right, -1, -1);
	c += is_full(s, width, sz, down, right, -1, 0);
	c += is_full(s, width, sz, down, right, -1, 1);
	c += is_full(s, width, sz, down, right, 1, -1);
	c += is_full(s, width, sz, down, right, 1, 0);
	c += is_full(s, width, sz, down, right, 1, 1);
	c += is_full(s, width, sz, down, right, 0, -1);
	c += is_full(s, width, sz, down, right, 0, 1);
	return c;
	}

int main(int argc, char *argv[])
	{
	unsigned int sz, w, i, j, f = 0;
	unsigned char *s = read_entries(&sz, &w), c = 0, adj;
	do {
		c = 0;
		for (i = 0; i < sz; i++)
			for (j = 0; j < w; j++)
				{
				adj = adj_count(s, i, j, w, sz);
				if (s[i * w + j] == FULL && adj >= 5)
					s[i * w + j] = EMPTYING;
				if (s[i * w + j] == EMPTY && !adj)
					s[i * w + j] = FILLING;
				}
		for (i = 0; i < sz; i++)
			for (j = 0; j < w; j++)
				{
				if (s[i * w + j] == FILLING)
					{
					s[i * w + j] = FULL;
					c = 1;
					}
				if (s[i * w + j] == EMPTYING)
					{
					s[i * w + j] = EMPTY;
					c = 1;
					}
				}
		} while (c);
	for (i = 0; i < sz; i++)
		for (j = 0; j < w; j++)
			f += s[i * w + j] == FULL;			
	printf("F = %u\n", f);
	}
