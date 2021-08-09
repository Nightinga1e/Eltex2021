#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int status = 0;
	pid = fork();
	if(pid == 0)
	{
		printf("\nI am a child, my pid is : %d, my ppid is: %d\n", getpid(), getppid());
	}else{
		printf("\nI am a parent, my pid is : %d, my ppid is: %d\n", getpid(), getppid());
	}
	wait(&status);
	return 0;
}
