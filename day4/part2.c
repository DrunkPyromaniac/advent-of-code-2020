#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

struct passport
	{
	unsigned short byr, iyr, eyr;
	char *hgt, *hcl, *ecl, *pid, *cid;
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
			p.byr = strtoul(val + 4, NULL, 10);
		else if (!strncmp(val, "iyr", 3))
			p.iyr = strtoul(val + 4, NULL, 10);
		else if (!strncmp(val, "eyr", 3))
			p.eyr = strtoul(val + 4, NULL, 10);
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
			printf("PP: %hu %hu %hu %s %s %s %s %s\n", p.byr, p.iyr, p.eyr, p.hgt, p.hcl, p.ecl, p.pid, p.cid);
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
		printf("PP: %hu %hu %hu %s %s %s %s %s\n", p.byr, p.iyr, p.eyr, p.hgt, p.hcl, p.ecl, p.pid, p.cid);
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

#define ISHEX(c) (((c) - '0' >= 0 && (c) - '0' <= 9) || ((c) - 'a' >= 0 && (c) - 'a' <= 5))

int main(int argc, char *argv[])
	{
	unsigned int sz, i, c = 0, h;
	char *unit;
	struct passport *pp = read_entries(&sz);
	for (i = 0; i < sz; i++)
		{
		if (pp[i].hgt)
			h = strtoul(pp[i].hgt, &unit, 10);
		c += (pp[i].byr >= 1920 && pp[i].byr <= 2002
			&& pp[i].iyr >= 2010 && pp[i].iyr <= 2020
			&& pp[i].eyr >= 2020 && pp[i].eyr <= 2030
			&& pp[i].hgt && ((!strcmp(unit, "cm") && h >= 150 && h <= 193) || (!strcmp(unit, "in") && h >= 59 && h <= 76))
			&& pp[i].hcl && strlen(pp[i].hcl) == 7 && pp[i].hcl[0] == '#' && ISHEX(pp[i].hcl[1]) && ISHEX(pp[i].hcl[2]) && ISHEX(pp[i].hcl[3]) && ISHEX(pp[i].hcl[4]) && ISHEX(pp[i].hcl[5]) && ISHEX(pp[i].hcl[6])
			&& pp[i].ecl &&
				(!strcmp(pp[i].ecl, "amb") || !strcmp(pp[i].ecl, "blu") || !strcmp(pp[i].ecl, "brn") || !strcmp(pp[i].ecl, "gry") || !strcmp(pp[i].ecl, "grn") || !strcmp(pp[i].ecl, "hzl") || !strcmp(pp[i].ecl, "oth"))
			&& pp[i].pid && strlen(pp[i].pid) == 9);
		}
	printf("V = %d\n", c);
	}
