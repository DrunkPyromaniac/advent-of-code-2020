#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

struct entry
	{
	unsigned int i1, i2;
	char c, *pw;
	};

struct entry *read_entries(unsigned int *sz)
	{
	unsigned int i = 0, size = 0;
 	struct entry e, *ret = NULL;
	while (scanf("%d-%d %c: %ms", &e.i1, &e.i2, &e.c, &e.pw) != EOF)
		{
		e.i1--;
		e.i2--;

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
	unsigned int sz, i, valid = 0;
	struct entry *entries = read_entries(&sz);
	for (i = 0; i < sz; i++)
		{
		if (entries[i].i1 > strlen(entries[i].pw) || entries[i].i2 > strlen(entries[i].pw))
			continue;
		if ((entries[i].pw[entries[i].i1] == entries[i].c) ^ (entries[i].pw[entries[i].i2] == entries[i].c))
			valid++;
		}
	printf("V = %d\n", valid);
	}
