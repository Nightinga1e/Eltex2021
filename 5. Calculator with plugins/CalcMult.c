#include <stdio.h>

#define NAMELEN 30

struct Names
{
	char *name[NAMELEN];	
};

struct Names funcnames()
{
	static char funcs[NAMELEN] = "Mult";
	return (struct Names){.name = funcs};
} 

int Mult(int *a, int *b)
{
	int mult = 0;
	mult = *a * *b;
	return mult;
}