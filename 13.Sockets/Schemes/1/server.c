#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#define BUFSIZE 1024
#define PORT 7627
#define MAXTHR 2000

 
typedef struct Args{
    int fd;
} Args_t;

void* clmsgs(void* mynew_fd)
{
	Args_t *arg = (Args_t*) mynew_fd;
	int new_fd = arg->fd; 	
	char sendbuf[BUFSIZE] = "Hello from server!";
	char recvbuf[BUFSIZE] = "";
	recv(new_fd, recvbuf, BUFSIZE, 0);
	printf("Get message from client: %s\n", recvbuf);
	send(new_fd, sendbuf, BUFSIZE, 0);
	return 0;
}

void* clhandler(void* mysock_fd)
{
	Args_t *arg = (Args_t*) mysock_fd;
	int sock_fd = arg->fd; 	
	Args_t newargs[MAXTHR];
	int pstatus;
	pthread_t threads[MAXTHR];
	int thrnum = 0;
	int status_addr;
	int new_fd[MAXTHR];
	struct sockaddr_in client[MAXTHR];
	int len;
		
	while(thrnum < MAXTHR)
	{
		//len = sizeof(client[thrnum]);
		new_fd[thrnum] = accept(sock_fd, (struct sockaddr *)&client[thrnum], &len);
		if(-1 == new_fd[thrnum])
		{
			printf("\nAccept error!\n");
			return (void*)-7;
		}

		newargs[thrnum].fd = new_fd[thrnum];
		printf("\nNumber is: %d\n", thrnum);
		pstatus = pthread_create(&threads[thrnum], NULL, clmsgs, (void*)&newargs[thrnum]);
		if(-1 == pstatus)
		{
			printf("\nclhandler pthread_create error!\n");
			return (void*)-8;
		}
		thrnum = thrnum + 1;
	}	

	for(int i = 0; i<thrnum; i++)
	{
		pstatus = pthread_join(threads[i], (void**)&status_addr);
		if(-1 == pstatus)
		{
			printf("\nclhandler pthread_join error!\n");
			return (void*)-9;
		}
	}
	return 0;
}

int main()
{
	int sock_fd, new_fd;
	int len;
	int bindcheck;
	int listencheck;
	struct sockaddr_in serv;
	pthread_t threads[MAXTHR];
	pthread_t thread;
//	pthread_attr_t attr;
//	int attrres;
	int pstatus;
	int status_addr;
	Args_t args;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0); //создаем сокет
	if(-1 == sock_fd)//при провале
	{
		printf("\nSocket creation error!\n");
		return -1;
	}
/*
	int enable = 1;
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
	    perror("setsockopt(SO_REUSEADDR) failed");
	}	
	
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0)
	{
	    perror("setsockopt 2(SO_REUSEADDR) failed");
	}
*/
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(PORT); 
	args.fd = sock_fd;

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
/*
	attrres = pthread_attr_init(&attr);
	if(-1 == attrres)
	{
		printf("\npthread_attr_init error!\n");
		return -4;
	}
*/	
	pstatus = pthread_create(&thread, NULL, clhandler, (void*)&args);
	if(-1 == pstatus)
	{
		printf("\npthread_create error!\n");
		return -5;
	}

	pstatus = pthread_join(thread, (void**)&status_addr);
	if(-1 == pstatus)
	{
		printf("\npthread_join error!\n");
		return -6;
	}

	close(new_fd);
	close(sock_fd);	
	return 0;
}