#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
	pid_t pid_2;
	int status;
	printf("\n1 My pid: %d, my parent: %d\n", getpid(), getppid());
	pid_2 = fork();
	if (pid_2 == 0)
	{
		pid_t pidch_2_1;
		pidch_2_1 = fork();
		if(pidch_2_1 == 0)
		{
			printf("\n2_1 My pid: %d, my parent: %d\n",getpid(), getppid());
		}else{
			printf("\n2 My pid: %d, my parent: %d\n",getpid(), getppid());
			wait(&status);
		}
	}else{
		pid_t pidch_3;
		pidch_3 = fork();
		if(pidch_3 == 0)
		{
			printf("\n3 My pid: %d, my parent: %d\n",getpid(), getppid());
			pid_t pidch3_1;
			pidch3_1 = fork();
			if (pidch3_1 == 0)
			{
				printf("\n3_1 My pid: %d, my parent: %d\n", getpid(), getppid());
			}else{
				pid_t pidch3_2;
				pidch3_2 = fork();
				if(pidch3_2 == 0)
				{
					printf("\n3_2 My pid: %d, my parent: %d\n", getpid(), getppid());
				}else{
					wait(&status);
				}
				wait(&status);
			}
		}
	}
	wait(&status);
	return 0;
}

