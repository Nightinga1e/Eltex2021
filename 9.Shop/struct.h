#pragma once
#define NUMOFSHOPS 5

struct arg_st
{
	int number;
	int result;
	int shops[NUMOFSHOPS];
	pthread_mutex_t strmutex[NUMOFSHOPS+1];
};
