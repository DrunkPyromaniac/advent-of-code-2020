#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

struct sub_bag
	{
	unsigned int count;
	char *adj, *color;
	};

struct bag
	{
	char *adj, *color;
	unsigned int sz_bags;
	struct sub_bag *bags;
	};

struct bag *read_entries(unsigned int *sz)
	{
	unsigned int i = 0, size = 0, c, count;
	char *adj, *color, ch;
	struct bag *ret = NULL;
	int v;

	while (scanf("%ms %ms bags contain ", &adj, &color) != EOF)
		{
		if (i == size)
			{
			size += 50;
			ret = realloc(ret, size * sizeof(*ret));
			}
		ret[i].adj = adj;
		ret[i].color = color;
		ret[i].sz_bags = 0;
		ret[i].bags = NULL;
		while ((v = scanf("%u %ms %ms bag", &count, &adj, &color)) == 3)
			{
			c = ret[i].sz_bags++;
			ret[i].bags = realloc(ret[i].bags, ret[i].sz_bags * sizeof(struct sub_bag));
			ret[i].bags[c].adj = adj;
			ret[i].bags[c].color = color;
			ret[i].bags[c].count = count;
			if (ret[i].bags[c].count > 1)
				scanf("s");
			scanf("%c ", &ch);
			if (ch == '.')
				break;
			else if (ch != ',')
				{
				printf("Gah! %c\n", ch);
				exit(0);
				}
			}
		if (!ret[i].sz_bags)
			scanf("no other bags. ");
		i++;
		}
	if (sz)
		*sz = i;
	return ret;
	}

unsigned int count_in(struct bag *bags, struct bag *b, unsigned int sz)
	{
	unsigned int ret = 0, i, j;

	for (i = 0; i < b->sz_bags; i++)
		{
		for (j = 0; j < sz; j++)
			if (!strcmp(b->bags[i].adj, bags[j].adj) && !strcmp(b->bags[i].color, bags[j].color))
				break;
		ret += b->bags[i].count * (count_in(bags, bags + j, sz) + 1);
		}
	return ret;
	}

int main(int argc, char *argv[])
	{
	unsigned int sz, i;
	struct bag *b = read_entries(&sz);
	for (i = 0; i < sz; i++)
		if (!strcmp(b[i].adj, "shiny") && !strcmp(b[i].color, "gold"))
			break;
	printf("C = %u\n", count_in(b, b + i, sz));
	}
