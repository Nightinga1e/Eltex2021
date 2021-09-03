#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFSIZE 1024

int main()
{
	int sock_fd;
	int connectcheck;
	struct sockaddr_un serv;
	char sendbuf[BUFSIZE] = "Hello from client!";
	char recvbuf[BUFSIZE] = "";

	sock_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	serv.sun_family = AF_LOCAL;
	strncpy(serv.sun_path, "Locsock", sizeof("Locksock"));

	connectcheck = connect(sock_fd, (struct sockaddr*)&serv, sizeof(serv));
	if(-1 == connectcheck)
	{
		printf("\nConnect error!\n");
		return -1;
	}

	send(sock_fd, sendbuf, BUFSIZE, 0);
	recv(sock_fd, recvbuf, BUFSIZE, 0);
	printf("Get message from client: %s\n", recvbuf);
	close(sock_fd);
	return 0;
}