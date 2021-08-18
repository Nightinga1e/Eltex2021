#include "custbuy.h"

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

