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

int main(int argc, char *argv[])
  {
  unsigned int sz, i, j, k, *entries = read_entries(&sz), sum, min, max;
	unsigned char good;
  for (i = 25; i < sz; i++, good = 0)
		{
    for (j = i - 25; j < i && !good; j++)
			for (k = j + 1; k < i && !good; k++)
				if (entries[j] + entries[k] == entries[i])
					good = 1;
		if (!good)
			{
			for (j = 0; j < i; j++, sum = 0, min = (unsigned int)-1, max = 0)
				for (k = j; k < i; k++)
					{
					sum += entries[k];
					if (min > entries[k])
						min = entries[k];
					if (max < entries[k])
						max = entries[k];
					if (sum == entries[i])
						printf("W: %u\n", min + max);
					}
			break;
			}
		}
	printf("B: %u (%u)\n", entries[i], i);
  }
