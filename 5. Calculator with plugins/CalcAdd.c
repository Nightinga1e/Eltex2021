#include <stdio.h>

#define NAMELEN 30

struct Names
{
	char *name[NAMELEN];	
};

struct Names funcnames()
{
	static char funcs[NAMELEN] = "Add";
	return (struct Names){.name = funcs};
} 

int Add(int *a, int *b)
{
	int sum = 0;
	sum = *a + *b;
	return sum;
}
