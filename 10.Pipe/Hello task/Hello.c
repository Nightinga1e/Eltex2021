#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define MESG_LEN 7

int main()
{
	int pipefd[2];
	pid_t pid;
	char message[MESG_LEN] = "Hello!";
	char rmessage[MESG_LEN];
	int result = 0;
	
	result = pipe(pipefd);
	if(-1 == result)
	{
		printf("\nPipe error!\n");
		return -1;
	}
	pid = fork();
	if(-1 == pid)
	{
		printf("\nFork error!\n");
		return -2;
	}	
	if(0 == pid)
	{
		close(pipefd[0]);
		write(pipefd[1], message, MESG_LEN);
		printf("\nSend message to parent: %s\n", message);
		close(pipefd[1]);
	}else
	{
		close(pipefd[1]);
		read(pipefd[0], rmessage, MESG_LEN);
		printf("\nReceive message from child: %s\n", rmessage);
		close(pipefd[0]);
		wait(NULL);	
	}
	return 0;
}