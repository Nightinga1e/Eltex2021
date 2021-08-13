#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define NUMOFSHOPS 5

int main()
{
	int shops[NUMOFSHOPS];
	
	for (int i = 0; i < NUMOFSHOPS; i++)
	{
		shops[i] = 900 + rand() % 200;
		printf("\nShop #%d have %d items\n", i+1, shops[i]); 
	}
	return 0;
}