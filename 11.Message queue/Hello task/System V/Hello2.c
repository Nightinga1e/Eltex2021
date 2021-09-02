//Message queue with System V

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct msgbuf{
	long mtype;
	char message[100];
};

int main()
{
	pid_t mypid;
	key_t msgkey;
	int mqid = 0;
	int result = 0;
	int type = 1;
	char *file = "Hello.c";
	int id = 'K';
	msgkey = ftok(file, id); // генерация ключа для msgget
	if (-1 == msgkey) //при провале генерации
	{
		printf("\nftok error! \n");
		return -1;
	}	
	mqid = msgget(msgkey, IPC_CREAT | 0666); //создание очереди сообщений, получение идентификатора
	if (-1 == result) // при провале создания 
	{
		printf("\nmsgget error!\n");
		return -2;
	}
	mypid = fork();
	if (0 == mypid)
	{//потомок
		struct msgbuf msg_st;
		int result = 0;
		int lenght = 0;
		char mymessage[10] = "Hello!";
		msg_st.mtype = type;
		strncpy(msg_st.message, mymessage, 10); 
		lenght = sizeof(struct msgbuf) - sizeof(long);
		result = msgsnd(mqid, &msg_st, lenght, 0); //ставим сообщение в очередь
		if(-1 == result) // в случае неудачи
		{
			printf("\nmsgsnd error!\n");
			return -3;
		}	
	}else
	{//родитель
		struct msgbuf msg_st;
		int wresult;
		int result = 0;
		int lenght = 0;
		lenght = sizeof(struct msgbuf) - sizeof(long);
		result = msgrcv(mqid, &msg_st, lenght, type, 0); //пытаемся забрать сообщение из очереди
		if(-1 == result) // при неудаче
		{
			printf("\nmsgget error!\n");
			return -4;
		}
		printf("\n%s\n", msg_st.message);
		wait(&wresult); //ждем потомка
		result = msgctl(mqid, IPC_RMID, 0); //удаляем очередь
		if(-1 == result)
		{
			printf("\nmsgctl error!\n");
			return -5;
		}
	}			
	return 0;
}