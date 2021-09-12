#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFSIZE 1024
#define PORT 7627

int main()
{
	int sock_fd;
	int connectcheck;
	struct sockaddr_in serv;
	char sendbuf[BUFSIZE] = "Hello from client!";
	char recvbuf[BUFSIZE] = "";

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(PORT); 

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sock_fd)//при провале
	{
		printf("\nSocket creation error!\n");
		return -1;
	}

	connectcheck = connect(sock_fd, (struct sockaddr*)&serv, sizeof(serv));
	if(-1 == connectcheck)
	{
		printf("\nConnect error!\n");
		return -1;
	}

	send(sock_fd, sendbuf, BUFSIZE, 0);
	recv(sock_fd, recvbuf, BUFSIZE, 0);
	printf("Get message from server: %s\n", recvbuf);
	close(sock_fd);
	return 0;
}