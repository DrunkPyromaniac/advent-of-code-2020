#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define ACC 1
#define NOP 2
#define JMP 3

struct ins
	{
  unsigned char instr;
  unsigned int arg;
	};

struct ins *read_entries(unsigned int *sz)
	{
	unsigned int i = 0, size = 0, arg;
	char instr;
 	struct ins *ret = NULL;
	while (scanf("%c%d ", &instr, &arg) != EOF)
		{
		if (i == size)
			{
			size += 50;
			ret = realloc(ret, size * sizeof(*ret));
			}
    ret[i].instr = instr;
    ret[i].arg = arg;
		i++;
		}
	if (sz)
		*sz = i;
	return ret;
	}

int main(int argc, char *argv[])
	{
	unsigned int sz, i;
	signed int x = 0, y = 0, wx = 10, wy = 1, t;
	struct ins *code = read_entries(&sz);
	for (i = 0; i < sz; i++)
		{
    switch (code[i].instr)
      {
      case 'F':
        y += wy * code[i].arg;
        x += wx * code[i].arg;
        break;
      case 'N':
        wy += code[i].arg;
        break;
      case 'S':
        wy -= code[i].arg;
        break;
      case 'E':
        wx += code[i].arg;
        break;
      case 'W':
        wx -= code[i].arg;
        break;
      case 'L':
        code[i].arg = 360 - code[i].arg;
      case 'R':
        while (code[i].arg)
          {
          t = -wx;
          wx = wy;
          wy = t;
          code[i].arg -= 90;
          }
        break;
      default:
        printf("Gah!\n");
        exit(0);
      }
    }
	printf("D = %d\n", abs(x) + abs(y));
	}
