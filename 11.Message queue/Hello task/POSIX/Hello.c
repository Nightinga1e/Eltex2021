#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

#define Q_NAME "/new_queue"
int main()
{
	pid_t mypid;
	mqd_t qds;
	struct mq_attr st_queue;
	st_queue.mq_maxmsg = 10;
	st_queue.mq_msgsize = 11;
	int clresult = 0;	
	qds = mq_open(Q_NAME, O_CREAT | O_RDWR, 0666, &st_queue); // создаем дескриптор очереди
	if((mqd_t)-1 == qds) // при провале
	{
		printf("\nmq_open error!\n");
		return -1;
	}
	mypid = fork();
	if(0 == mypid)
	{//потомок
		int priority = 5;
		int result = 0;
		int lenght = 0;
		char message [10] = "Hello!";
		lenght = strlen(message);
		result = mq_send(qds, message, lenght, priority);//добавляем сообщение в очередь
		if(-1 == result)// при неудаче
		{
			printf("\nmq_send error!\n");
			return -2;
		} 
	}else
	{//родитель
		int wresult;
		int result = 0;
		int priority;
		char gettext[100];
		result = mq_receive(qds, gettext, 11, &priority);//пытаемся забрать сообщение из очереди
		if(-1 == result)//при неудаче
		{
			printf("\nmq_receive error!\n");
			return -4;
		}
		printf("\n%s\n", gettext);
		wait(&result);	clresult = mq_close(qds);
		if (-1 == clresult)
		{
			printf ("\nmq_close error!\n");
			return -5;
		}	
		clresult = mq_unlink(Q_NAME);
		if(-1 == clresult)
		{
			printf("\nmq_unlink error!\n");
			return -6;
		}
	}
	return 0;
}