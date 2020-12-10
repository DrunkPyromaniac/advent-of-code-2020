#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

struct adapter
	{
	unsigned int joltage;
	unsigned long long count;
	};

struct adapter *read_entries(unsigned int *sz)
  {
  unsigned int i = 0, size = 0;
  struct adapter *ret = NULL, entry;
  while (scanf("%u", &(entry.joltage)) != EOF)
    {
		entry.count = 0;
    if (i == size)
      {
      size += 50;
      ret = realloc(ret, size * sizeof(*ret));
      }
		memmove(ret + i, &entry, sizeof(*ret));
    i++;
    }
  if (sz)
    *sz = i;
  return ret;
  }

void sort_entries(struct adapter *l, unsigned int sz)
	{
	unsigned char c;
	unsigned int i, temp;
	do
		{
		c = 0;
		for (i = 0; i < sz - 1; i++)
			{
			if (l[i].joltage > l[i + 1].joltage)
				{
				temp = l[i + 1].joltage;
				l[i + 1].joltage = l[i].joltage;
				l[i].joltage = temp;
				c = 1;
				}
			}
		} while (c);
	}

int main(int argc, char *argv[])
  {
  unsigned int sz, i, k;
	unsigned long long c;
  struct adapter *entries = read_entries(&sz);

	sort_entries(entries, sz);
	entries[sz - 1].count = 1;
	for (i = sz - 2; i < sz; i--)
		for (k = 1; k < 4 && i + k < sz; k++)
			if (entries[i + k].joltage - entries[i].joltage <= 3)
				entries[i].count += entries[i + k].count;
	for (i = 0, c = 0; i < sz && i < 3; i++)
		if (entries[i].joltage <= 3)
			c += entries[i].count;
	printf("C = %llu\n", c);
  }
