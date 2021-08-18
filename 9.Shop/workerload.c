#include "workerload.h"

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

