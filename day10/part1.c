#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

unsigned int *read_entries(unsigned int *sz)
  {
  unsigned int entry, i = 0, size = 0;
  unsigned int *ret = NULL;
  while (scanf("%u", &entry) != EOF)
    {
    if (i == size)
      {
      size += 50;
      ret = realloc(ret, size * sizeof(unsigned int));
      }
    ret[i] = entry;
    i++;
    }
  if (sz)
    *sz = i;
  return ret;
  }

void sort_entries(unsigned int *l, unsigned int sz)
	{
	unsigned char c;
	unsigned int i, t;
	do
		{
		c = 0;
		for (i = 0; i < sz - 1; i++)
			if (l[i] > l[i + 1])
				{
				t = l[i];
				l[i] = l[i + 1];
				l[i + 1] = t;
				c = 1;
				}
		} while (c);
	}

int main(int argc, char *argv[])
  {
  unsigned int sz, *entries = read_entries(&sz), num1 = 0, num3 = 0, prev = 0, i;
	sort_entries(entries, sz);
  for (i = 0; i < sz; i++)
		{
		if (entries[i] - prev == 1)
			num1++;
		else if (entries[i] - prev == 3)
			num3++;
		prev = entries[i];
		}
	num3++;
	printf("S: %u\n", num1 * num3);
  }
