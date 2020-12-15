#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SZ_NUM (sizeof(numbers) / sizeof(numbers[0]))

int main(void)
  {
  unsigned int numbers[] = {0, 13, 16, 17, 1, 10, 6};
  unsigned int sz_table = 500, i, prev, cur;
  unsigned int *table = malloc(sz_table * sizeof(unsigned int));
  memset(table, 0xFF, sz_table * sizeof(unsigned int));
  for (i = 0; i < 30000000; i++)
    {
    if (i < SZ_NUM)
      cur = numbers[i];
    else if (sz_table <= prev || table[prev] == (unsigned int)-1)
      cur = 0;
    else
      cur = i - table[prev] - 1;
    if (i)
      {
      if (sz_table <= prev)
        {
        table = realloc(table, (prev + 500) * sizeof(unsigned int));
        memset(table + sz_table, 0xFF, (prev + 500 - sz_table) * sizeof(unsigned int));
        sz_table = prev + 500;
        }
      table[prev] = i - 1;
      }
    prev = cur;
    }
  printf("Said %u\n", cur);
  }
