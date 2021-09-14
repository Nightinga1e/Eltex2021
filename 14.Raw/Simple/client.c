#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFSIZE 1024
#define PORT 7628

int main()
{
	int sock_fd;
	int concheck, sendcheck, recvcheck;
	int size;
	int len;
	char sendbuf[BUFSIZE] = "Hello from client!";
	char recvbuf[BUFSIZE] = "";
	struct sockaddr_in serv;
	sock_fd = socket (AF_INET, SOCK_DGRAM, 0);
	if(-1 == sock_fd)//при провале
	{
		printf("\nSocket creation error!\n");
		return -1;
	}

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(PORT); 
	
	concheck = connect(sock_fd, (struct sockaddr *)&serv, sizeof(serv));
	if(-1 == concheck)
	{
		printf("\nConnect error!\n");
		return -2;
	}

	sendcheck = sendto(sock_fd, sendbuf, sizeof(sendbuf), 0, (struct sockaddr *)&serv, sizeof(serv));
	if(-1 == sendcheck)
	{
		printf("\nSendto error!\n");
		return -3;
	}	

	len = sizeof(serv);
	recvcheck = recvfrom(sock_fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&serv, &len);
	if(-1 == recvcheck)
	{
		printf("\nRecvfrom error!\n");
		return -4;
	}
	printf("\nGet message from client: %s\n", recvbuf);
	close(sock_fd);
	return 0;
}