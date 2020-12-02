#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

struct entry
	{
	unsigned int min, max;
	char c, *pw;
	};

struct entry *read_entries(unsigned int *sz)
	{
	unsigned int i = 0, size = 0;
 	struct entry e, *ret = NULL;
	while (scanf("%d-%d %c: %ms", &e.min, &e.max, &e.c, &e.pw) != EOF)
		{
		if (i == size)
			{
			size += 50;
			ret = realloc(ret, size * sizeof(e));
			}
		memmove(ret + i, &e, sizeof(e));
		i++;
		}
	if (sz)
		*sz = i;
	return ret;
	}

int main(int argc, char *argv[])
	{
	unsigned int sz, i, j, valid = 0, c;
	struct entry *entries = read_entries(&sz);
	for (i = 0; i < sz; i++)
		{
		for (c = 0, j = 0; j < strlen(entries[i].pw); j++)
			if (entries[i].pw[j] == entries[i].c)
				c++;
		if (c >= entries[i].min && c <= entries[i].max)
			valid++;
		}
	printf("V = %d\n", valid);
	}
