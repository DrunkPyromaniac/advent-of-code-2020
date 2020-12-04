#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

struct passport
	{
	char *byr, *iyr, *eyr, *hgt, *hcl, *ecl, *pid, *cid;
	};

struct passport *read_entries(unsigned int *sz)
	{
	unsigned int i = 0, size = 0;
	char val[1024], spaces[1024];
	struct passport *ret = NULL, p;
	memset(&p, 0, sizeof(p));
	while (scanf("%s%[ \n]", val, spaces) != EOF)
		{
		if (!strncmp(val, "byr", 3))
			p.byr = strdup(val + 4);
		else if (!strncmp(val, "iyr", 3))
			p.iyr = strdup(val + 4);
		else if (!strncmp(val, "eyr", 3))
			p.eyr = strdup(val + 4);
		else if (!strncmp(val, "hgt", 3))
			p.hgt = strdup(val + 4);
		else if (!strncmp(val, "hcl", 3))
			p.hcl = strdup(val + 4);
		else if (!strncmp(val, "ecl", 3))
			p.ecl = strdup(val + 4);
		else if (!strncmp(val, "pid", 3))
			p.pid = strdup(val + 4);
		else if (!strncmp(val, "cid", 3))
			p.cid = strdup(val + 4);
		if (strstr(spaces, "\n\n"))
			{
			printf("PP: %s %s %s %s %s %s %s %s\n", p.byr, p.iyr, p.eyr, p.hgt, p.hcl, p.ecl, p.pid, p.cid);
			if (i == size)
				{
				size += 50;
				ret = realloc(ret, size * sizeof(p));
				}
			memmove(ret + i, &p, sizeof(p));
			memset(&p, 0, sizeof(p));
			i++;
			}
		}
	if (p.byr || p.iyr || p.eyr || p.hgt || p.hcl || p.ecl || p.pid || p.cid)
		{
		printf("PP: %s %s %s %s %s %s %s %s\n", p.byr, p.iyr, p.eyr, p.hgt, p.hcl, p.ecl, p.pid, p.cid);
		if (i == size)
			{
			size += 50;
			ret = realloc(ret, size * sizeof(p));
			}
		memmove(ret + i, &p, sizeof(p));
		i++;
		}
	if (sz)
		*sz = i;
	return ret;
	}

int main(int argc, char *argv[])
	{
	unsigned int sz, i, c = 0;
	struct passport *pp = read_entries(&sz);
	for (i = 0; i < sz; i++)
		c += (pp[i].byr && pp[i].iyr && pp[i].eyr && pp[i].hgt && pp[i].hcl && pp[i].ecl && pp[i].pid);
	printf("V = %d\n", c);
	}
