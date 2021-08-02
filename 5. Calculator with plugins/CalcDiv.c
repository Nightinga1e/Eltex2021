#include <stdio.h>

#define NAMELEN 30

struct Names
{
	char *name[NAMELEN];	
};

struct Names funcnames()
{
	static char funcs[NAMELEN] = "Div";
	return (struct Names){.name = funcs};
}
 
int Div(int *a, int *b)
{
	int div = 0;
	div = *a / *b;
	return div;
}