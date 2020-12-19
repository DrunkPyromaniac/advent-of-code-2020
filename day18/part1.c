#include <stdio.h>
#include <string.h>

#define SYNTAX (-2)

#define END 0
#define PLUS 1
#define LPAR 3
#define RPAR 4
#define STAR 5
#define CONST 7

int factor(char *string, size_t *loc, long long *val);
int expr(char *string, size_t *loc, long long *val);

int nextToken(char *string, size_t *loc)
	{
	while (string[(*loc)])
		switch (string[(*loc)])
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				return CONST;
			case ')':
				(*loc)++;
				return RPAR;
			case '(':
				(*loc)++;
				return LPAR;
			case 0:
				return END;
			case '*':
				(*loc)++;
				return STAR;
			case '+':
				(*loc)++;
				return PLUS;
			case ' ':
			case '\t':
				(*loc)++;
				break;
			default:
				return SYNTAX;
			}
	return END;
	}

int main(void)
	{
	long long v;
	int read;
	char *line = NULL;
	size_t l, sz = 0;
	unsigned long long sum = 0;

	while ((read = getline(&line, &sz, stdin)) != -1)
		{
		l = 0;
		line[strlen(line) - 1] = 0;
		if (expr(line, &l, &v) != SYNTAX)
			sum += v;
		}
	printf("S = %llu\n", sum);
	return 0;
	}

int expr(char *string, size_t *loc, long long *val)
	{
	long long v, v2;
	int t, r, r2;

	t = nextToken(string, loc);
	switch (t)
		{
		case LPAR:
			(*loc)--;
			/* no break */
		case CONST:
			r = factor(string, loc, &v);
			if (r)
				return r;
			while (1)
				{
				t = nextToken(string, loc);
				switch (t)
					{
					case PLUS:
						r2 = factor(string, loc, &v2);
						if (r2)
							return r2;
						v += v2;
						break;
					case STAR:
						r2 = factor(string, loc, &v2);
						if (r2)
							return r2;
						v *= v2;
						break;
					case RPAR:
						(*loc)--;
						/* no break */
					case END:
						*val = v;
						return 0;
					default:
						return SYNTAX;
					}
				}
			break;
		default:
			return SYNTAX;
		}
	}

int factor(char *string, size_t *loc, long long *val)
	{
	long long v;
	int t, r;
	char ch;

	t = nextToken(string, loc);
	switch (t)
		{
		case CONST:
			v = 0;
			while (1)
				{
				ch = string[*loc];
				if (ch >= 0x30 && ch <= 0x39)
					{
					v *= 10;
					v += ch - 0x30;
					(*loc)++;
					}
				else
					break;
				}
			*val = v;
			return 0;
			break;
		case LPAR:
			r = expr(string, loc, &v);
			t = nextToken(string, loc);
			if (t != RPAR)
				return SYNTAX;
			if (!r)
				*val = v;
			return r;
			break;
		default:
			return SYNTAX;
		}
	}
