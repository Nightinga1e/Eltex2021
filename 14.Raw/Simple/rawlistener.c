#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFSIZE 1024
#define PORT 7628

int main()
{
	int sock_fd;
	int concheck, sendcheck, recvcheck;
	int size;
	socklen_t len;
	char sendbuf[BUFSIZE] = "Hello from client!";
	char recvbuf[BUFSIZE] = "";
	struct sockaddr_in someaddr;
	sock_fd = socket (AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(-1 == sock_fd)//при провале
	{
		perror("\nError : \n");
		printf("\nSocket creation error!\n");
		return -1;
	}
	char tmp[BUFSIZE];
	len = sizeof(someaddr);
	while(1)
	{
		recvcheck = recvfrom(sock_fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&someaddr, &len);
		if(-1 == recvcheck)
		{
			printf("\nRecvfrom error!\n");
			return -4;
		}

		if(inet_ntop(someaddr.sin_family, (void*)&(((struct sockaddr_in *)&someaddr)->sin_addr), tmp, sizeof(tmp)) == NULL)
		{
			perror("\nError: ");
		}
		printf("(from %s): %s\n", tmp, recvbuf + 28);
	}
	close(sock_fd);
	return 0;
}