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
	key_t msgkey1, msgkey2;
	int mqid1 = 0;
	int mqid2 = 0;
	int result = 0;
	int type = 1;
	char *file1 = "Hello1.c";
	char *file2 = "Hello2.c";
	int id1 = 'O';
	int id2 = 'K';

	msgkey1 = ftok(file1, id1); // генерация ключа для msgget
	if (-1 == msgkey1) //при провале генерации
	{
		printf("\nftok error! \n");
		return -1;
	}	
	
	mqid1 = msgget(msgkey1, IPC_CREAT | 0666); //создание очереди сообщений, получение идентификатора
	if (-1 == mqid1) // при провале создания 
	{
		printf("\nmsgget error!\n");
		return -2;
	}

	msgkey2 = ftok(file2, id2); // генерация ключа для msgget
	if (-1 == msgkey2) //при провале генерации
	{
		printf("\nftok error! \n");
		return -1;
	}	

	mqid2 = msgget(msgkey2, IPC_CREAT | 0666); //создание очереди сообщений, получение идентификатора
	if (-1 == mqid2) // при провале создания 
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
		char mymessage[22] = "Hello from Hello1.c!";
		msg_st.mtype = type;
		strncpy(msg_st.message, mymessage, 22); 
		lenght = sizeof(struct msgbuf) - sizeof(long);
		result = msgsnd(mqid1, &msg_st, lenght, 0); //ставим сообщение в очередь
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
		result = msgrcv(mqid2, &msg_st, lenght, type, 0); //пытаемся забрать сообщение из очереди
		if(-1 == result) // при неудаче
		{
			printf("\nmsgget error!\n");
			return -4;
		}
		printf("\n%s\n", msg_st.message);
		
		wait(&wresult); //ждем потомка

		result = msgctl(mqid1, IPC_RMID, 0); //удаляем очередь
		if(-1 == result)
		{
			printf("\nmsgctl error!\n");
			return -5;
		}

		result = msgctl(mqid2, IPC_RMID, 0); //удаляем очередь
		if(-1 == result)
		{
			printf("\nmsgctl error!\n");
			return -5;
		}
	}			
	return 0;
}