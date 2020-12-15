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
  unsigned short dir = 90;
	signed int x = 0, y = 0;
  char c;
	struct ins *code = read_entries(&sz);
	for (i = 0; i < sz; i++)
		{
    c = code[i].instr;
    if (c == 'F')
      {
      if (!dir)
        c = 'N';
      else if (dir == 90)
        c = 'E';
      else if (dir == 180)
        c = 'S';
      else if (dir == 270)
        c = 'W';
      }
    switch (c)
      {
      case 'N':
        y += code[i].arg;
        break;
      case 'S':
        y -= code[i].arg;
        break;
      case 'E':
        x += code[i].arg;
        break;
      case 'W':
        x -= code[i].arg;
        break;
      case 'R':
        dir += code[i].arg;
        dir %= 360;
        break;
      case 'L':
        dir += 360;
        dir -= code[i].arg;
        dir %= 360;
        break;
      default:
        printf("Gah! %c\n", c);
        exit(0);
      }
    }
	printf("D = %d\n", abs(x) + abs(y));
	}
