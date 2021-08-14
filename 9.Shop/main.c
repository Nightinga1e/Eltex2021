#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define NUMOFSHOPS 5
#define NUMOFCUSTOMERS 3

struct arg_st
{
	int number;
	int result;
	int shops[NUMOFSHOPS];
	pthread_mutex_t strmutex[NUMOFSHOPS+1];
};

void *custbuy(void *arg)
{
	int mynum = 0;
	int myresult = 0;
	int req = 3000;
	int randshop = 0;
	int bufreq = 0;
	int bufshop = 0;
	pthread_mutex_t mutex[NUMOFSHOPS+1];
	struct arg_st *arguments = (struct arg_st *)arg;
	mutex[NUMOFSHOPS] = arguments->strmutex[NUMOFSHOPS];

	pthread_mutex_lock(&mutex[NUMOFSHOPS]);
	mynum = arguments->number;
	arguments->number += 1;
	pthread_mutex_unlock(&mutex[NUMOFSHOPS]);

	//printf("\n My number is: %d\n", mynum);
	while (req != 0)
	{	
		randshop = rand() % 5;
		if(pthread_mutex_trylock(&mutex[randshop]) == 0)
		{
			bufreq = req;
			bufshop = arguments->shops[randshop];
			if(arguments->shops[randshop] > 0)
			{
				req = req - arguments->shops[randshop];
				arguments->shops[randshop] = 0;
				if(req < 0)
				{
					printf("\n I am customer #%d, took %d items from %d shop, requierment - %d \n", mynum, bufreq, randshop + 1, 0); 
					arguments->shops[randshop] = arguments->shops[randshop] + ((-1)*req);
					req = 0;
				}else
				{
					printf("\n I am customer #%d, took %d items from %d shop, requierment - %d \n", mynum, bufshop, randshop + 1, req); 	
				}
			}			
			pthread_mutex_unlock(&mutex[randshop]);
		}
		sleep(2);	
	}
	arguments->result+=1;
	pthread_exit(NULL);
	return 0;
}

void *workerload(void *arg)
{
	int randshop = 0;
	pthread_mutex_t mutex[NUMOFSHOPS+1];
	struct arg_st *arguments = (struct arg_st *)arg;
	mutex[NUMOFSHOPS] = arguments->strmutex[NUMOFSHOPS];

	while(3 != arguments->result)
	{
		randshop = rand() % 5;
		if (pthread_mutex_trylock(&mutex[randshop]) == 0)
		{
			arguments->shops[randshop] += 200;
			printf("\n I am worker, add 200 items to %d shop \n", randshop + 1);
			pthread_mutex_unlock(&mutex[randshop]);
		}
		sleep(1);		
	}	
	
	pthread_exit(NULL);
	return 0;
}

int main()
{
	int randitems = 0;
	struct arg_st args;
	args.number = 1;
	args.result = 0;
	pthread_t customers[NUMOFCUSTOMERS];
	pthread_t worker;
	srand(time(NULL));
	
	for(int i = 0; i<NUMOFSHOPS+1; i++)
	{
		pthread_mutex_init(&args.strmutex[i], NULL);
	}

	for (int i = 0; i < NUMOFSHOPS; i++)
	{
		args.shops[i] = 900 + rand() % 200;
		printf("\nShop #%d have %d items\n", i+1, args.shops[i]); 
	}

	for (int i =0; i< NUMOFCUSTOMERS; i++)
	{
		pthread_create(&customers[i], NULL, custbuy, (void *)&args);
	}
	pthread_create(&worker, NULL, workerload, (void *)&args);
	
	for (int i =0; i< NUMOFCUSTOMERS; i++)
	{
		pthread_join(customers[i], NULL);
	}
	pthread_join(worker, NULL);

	for (int i =0; i< NUMOFCUSTOMERS+1; i++)
	{	
		pthread_mutex_destroy(&args.strmutex[i]);
	}	
	return 0;
}