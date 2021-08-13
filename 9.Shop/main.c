#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define NUMOFSHOPS 5
#define NUMOFCUSTOMERS 3

void *custbuy(void *args)
{
	printf("\n I am customer\n");
}

void *workerload(void *args)
{
	printf("\nI am worker\n");
}

int main()
{
	int shops[NUMOFSHOPS];
	pthread_t customers[NUMOFCUSTOMERS];
	pthread_t worker;

	for (int i = 0; i < NUMOFSHOPS; i++)
	{
		shops[i] = 900 + rand() % 200;
		printf("\nShop #%d have %d items\n", i+1, shops[i]); 
	}

	for (int i =0; i< NUMOFCUSTOMERS; i++)
	{
		pthread_create(&customers[i], NULL, custbuy, NULL);
	}
	pthread_create(&worker, NULL, workerload, NULL);
	
	for (int i =0; i< NUMOFCUSTOMERS; i++)
	{
		pthread_join(customers[i], NULL);
	}
	pthread_join(worker, NULL);

	return 0;
}