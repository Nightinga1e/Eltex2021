#include <stdio.h>

#define NAMELEN 30

struct Names
{
	char *name[NAMELEN];	
};

struct Names funcnames()
{
	static char funcs[NAMELEN] = "Sub";
	return (struct Names){.name = funcs};
} 

int Sub(int *a, int *b)
{
	int sub = 0;
	sub = *a - *b;
	return sub;
}
