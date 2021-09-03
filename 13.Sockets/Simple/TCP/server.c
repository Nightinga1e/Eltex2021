#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFSIZE 1024

int main()
{
	int sock_fd, new_fd;
	int len;
	int bindcheck;
	int listencheck;
	struct sockaddr_un serv, client;
	char sendbuf[BUFSIZE] = "Hello from server!";
	char recvbuf[BUFSIZE] = "";
	serv.sun_family = AF_LOCAL;
	strncpy(serv.sun_path, "Locsock", sizeof("Locksock"));

	sock_fd = socket(AF_LOCAL, SOCK_STREAM, 0); //создаем сокет
	if(-1 == sock_fd)//при провале
	{
		printf("\nSocket creation error!\n");
		return -1;
	}

	bindcheck = bind(sock_fd, (struct sockaddr *)&serv, sizeof(serv));
	if(-1 == bindcheck)
	{
		printf("\nBind error!\n");
		return -2;
	}

	listencheck = listen(sock_fd, 5);
	if(-1 == listencheck)
	{
		printf("\nListen error!\n");
		return -3;
	}

	len = sizeof(client);
	new_fd = accept(sock_fd, (struct sockaddr *)&client, &len);
	if(-1 == new_fd)
	{
		printf("\nAccept error!\n");
		return -4;
	}

	recv(new_fd, recvbuf, BUFSIZE, 0);
	printf("Get message from client: %s\n", recvbuf);
	send(new_fd, sendbuf, BUFSIZE, 0);

	close(new_fd);
	close(sock_fd);	
	return 0;
}