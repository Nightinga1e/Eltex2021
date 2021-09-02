#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

#define Q_NAME1 "/new_queue1"
#define Q_NAME2 "/new_queue2"
#define SIZE 100

int main()
{
	pid_t mypid;
	mqd_t qds1, qds2;
	
	int clresult = 0;	
	int wresult;
	int result = 0;
	int priority;
	int sendpriority = 7;
	int lenght = 0;
	char gettext[SIZE];	
	char message [21] = "Hello from Hello2.c!";
	struct mq_attr st_queue1;
	st_queue1.mq_maxmsg = 10;
	st_queue1.mq_msgsize = SIZE;
	qds1 = mq_open(Q_NAME1, O_RDWR, 0666, &st_queue1); // создаем дескриптор очереди
	if((mqd_t)-1 == qds1) // при провале
	{
		printf("\nmq_open error!\n");
		return -1;
	}
	qds2 = mq_open(Q_NAME2, O_RDWR, 0666, &st_queue1); // создаем дескриптор очереди
	if((mqd_t)-1 == qds2) // при провале
	{
		printf("\nmq_open qds1 error!\n");
		return -2;
	}	

	mypid = fork();
	if(mypid == 0)
	{//потомок
		result = mq_receive(qds1, gettext, SIZE, &priority);//пытаемся забрать сообщение из очереди
		if(-1 == result)//при неудаче
		{
			printf("\nmq_receive error!\n");
			return -3;
		}
		printf("\n%s\n", gettext);
	}else
	{//предок	
		lenght = strlen(message);
		result = mq_send(qds2, message, lenght, sendpriority);//добавляем сообщение в очередь
		if(-1 == result)// при неудаче
		{
			printf("\nmq_send error!\n");
			return -4;
		} 

		wait(&wresult);
		clresult = mq_close(qds1);
		if (-1 == clresult)
		{
			printf ("\nmq_close qds1 error!\n");	
			return -5;
		}

		clresult = mq_close(qds2);
		if (-1 == clresult)
		{
			printf ("\nmq_close qds2 error!\n");	
			return -6;
		}
	}
	return 0;
}