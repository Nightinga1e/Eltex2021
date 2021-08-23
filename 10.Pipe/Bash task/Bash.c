#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define RETRES 1000

int main()
{
	int result;
	int pipefd[2];
	char command[3] = "   ";
	char lspath[13] = "/usr/bin/ls";
	char pspath[13] = "/usr/bin/ps";
	char wcpath[13] = "/usr/bin/wc";
	char binpath[12] = "       ";
	pid_t pid;
	result = pipe(pipefd);
	if(-1 == result)
	{
		printf("\npipe error!\n");
		return -1;
	}
	pid = fork();
	if(pid == 0)
	{
		close(pipefd[0]);
		int ret = 0; 		
		result = dup2(pipefd[1], 1);
		if (-1 == result)
		{
			printf("\ndup2 child error!\n");
			return -2;
		}
		ret = execl(lspath, "ls", NULL);
		if(-1 == ret)
		{
			printf("\npwd error!\n");
			return -3;
		} 	
		close(pipefd[1]);
	}else{
		close(pipefd[1]);
		int ret = 0;
		result = dup2(pipefd[0], 0);
		if (-1 == result)
		{
			printf("\ndup2 parent error!\n");
			return -4;
		}
		ret = execl(wcpath, "wc", NULL);
		if(-1 == ret)
		{
			printf("\nls error!\n");
			return -5;
		}
		close(pipefd[0]);
	}

	wait(&result);
	return 0;
}

