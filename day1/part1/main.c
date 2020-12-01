#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

unsigned int *read_entries(unsigned int *sz)
  {
  unsigned int entry, i = 0, size = 0;
  unsigned int *ret = NULL;
  while (scanf("%d", &entry) != EOF)
    {
    if (i == size)
      {
      i += 50;
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
  unsigned int sz, i, j, *entries = read_entries(&sz);
  for (i = 0; i < sz; i++)
    for (j = i + 1; j < sz; j++)
      if (entries[i] + entries[j] == 2020)
        printf("P: %d\n", entries[i] * entries[j]);
  }
