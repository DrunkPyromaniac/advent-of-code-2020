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
	unsigned char instr, exec;
	signed int arg;
	};

struct ins *read_entries(unsigned int *sz)
	{
	unsigned int i = 0, size = 0, arg;
	char instr[4];
 	struct ins *ret = NULL;
	while (scanf("%3s %d", instr, &arg) != EOF)
		{
		if (i == size)
			{
			size += 50;
			ret = realloc(ret, size * sizeof(*ret));
			}
		if (!strcmp(instr, "jmp"))
			ret[i].instr = JMP;
		else if (!strcmp(instr, "nop"))
			ret[i].instr = NOP;
		else if (!strcmp(instr, "acc"))
			ret[i].instr = ACC;
		else
			ret[i].instr = 0;
		ret[i].arg = arg;
		ret[i].exec = 0;
		i++;
		}
	if (sz)
		*sz = i;
	return ret;
	}

char execute(struct ins *code, unsigned int sz)
	{
	signed int acc = 0;
	unsigned int ptr = 0;
	while (!code[ptr].exec && ptr < sz)
		{
		code[ptr].exec = 1;
		switch (code[ptr].instr)
			{
			case NOP:
				ptr++;
				break;
			case ACC:
				acc += code[ptr].arg;
				ptr++;
				break;
			case JMP:
				ptr += code[ptr].arg;
				break;
			default:
				printf("Gah!\n");
				exit(0);
			}
		}
	printf("A = %d\n", acc);
	return ptr >= sz;
	}

int main(int argc, char *argv[])
	{
	unsigned int sz, i, j;
	struct ins *code = read_entries(&sz);
	for (i = 0; i < sz; i++)
		{
		if (code[i].instr == NOP)
			{
			code[i].instr = JMP;
			if (execute(code, sz))
				exit(0);
			code[i].instr = NOP;
			}
		else if (code[i].instr == JMP)
			{
			code[i].instr = NOP;
			if (execute(code, sz))
				exit(0);
			code[i].instr = JMP;
			}
		else
			continue;
		for (j = 0;j < sz; j++)
			code[j].exec = 0;
		}
	}
