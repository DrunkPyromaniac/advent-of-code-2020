#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

struct seat
	{
	unsigned int row, column;
	};

struct seat *read_entries(unsigned int *sz)
	{
	unsigned int i = 0, size = 0, j;
	char id[11];
	struct seat *ret = NULL;
	while (scanf(" %10c", id) != EOF)
		{
		id[10] = 0;
		if (i == size)
			{
			size += 50;
			ret = realloc(ret, size * sizeof(struct seat));
			}
		ret[i].row = 0;
		ret[i].column = 0;
		for (j = 0; j < 7; j++)
			{
			if (id[j] == 'B')
				ret[i].row += (1 << (6 - j));
			else if (id[j] != 'F')
				{
				printf("Gah! %s\n", id);
				exit(0);
				}
			}
		for (j = 0; j < 3; j++)
			{
			if (id[7 + j] == 'R')
				ret[i].column += (1 << (2 - j));
			else if (id[7 + j] != 'L')
				{
				printf("Gah!\n");
				exit(0);
				}
			}
		i++;
		}
	if (sz)
		*sz = i;
	return ret;
	}

int main(int argc, char *argv[])
	{
	unsigned int sz, i, max = 0, id;
	struct seat *s = read_entries(&sz);
	for (i = 0; i < sz; i++)
		{
		id = s[i].row * 8 + s[i].column;
		if (id > max)
			max = id;
		}
	printf("M = %d\n", max);
	}
