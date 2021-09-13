#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define PORT 7627
#define MAXTHR 2000

int main()
{
	int counter = 0;
	int fresult;
	int sock_fd;
	int connectcheck;
	struct sockaddr_in serv;
	char sendbuf[BUFSIZE] = "Hello from client!";
	char recvbuf[BUFSIZE] = "";
	int tids[MAXTHR];
	for(int i=0; i<MAXTHR; i++)
	{
		tids[i] = fork();
		if(tids[i] == 0)
		{
			sock_fd = socket(AF_INET, SOCK_STREAM, 0);
			if(-1 == sock_fd)//при провале
			{
				printf("\nSocket creation error!\n");
				return -1;
			}

			serv.sin_family = AF_INET;
			serv.sin_addr.s_addr = htonl(INADDR_ANY);
			serv.sin_port = htons(PORT); 

			connectcheck = connect(sock_fd, (struct sockaddr*)&serv, sizeof(serv));
			if(-1 == connectcheck)
			{
				perror("\n Error: \n");
				//printf("\nConnect error!\n");
				close(sock_fd);
				printf("\nCounter = %d\n", counter);
				return -1;
			}else{
				counter++;
				printf("\nCounter = %d\n", counter);
				send(sock_fd, sendbuf, BUFSIZE, 0);
				recv(sock_fd, recvbuf, BUFSIZE, 0);
				printf("Get message from server: %s\n", recvbuf);
				
			}
		}else{
			for(int i=0; i<counter; i++)
			{
				wait(&fresult);
			}
		}
	}

	close(sock_fd);
	return 0;
}