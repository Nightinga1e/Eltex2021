#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int result;
	char command[3] = "   ";
	char lspath[7] = "/bin/ls";
	char pspath[7] = "/bin/ps";
	char binpath[7] = "       ";
	pid_t pid;
/*	fgets(command, 2, stdin);
 	if(strcmp(command, "ls") == 0)
	{
		strncpy(binpath, lspath, 7);
	}
	if(strcmp(command, "ps") == 0)
	{
		srncpy(binpath, pspath, 7);
	}
*/
	pid = fork();
	if(pid == 0)
	{
		int ret = 0; 
		ret = execl(lspath, "ls", NULL);
		if(-1 == ret)
		{
			printf("\nError with ls\n");
			return -1;
		} 	
	}else{
		int ret = 0;
		ret = execl(pspath, "ps", NULL);
		if(-1 == ret)
		{
			printf("\nError with ps\n");
			return -2;
		}
	}

	wait(&result);
	return 0;
}
