#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define BUFSIZE 1024
#define SOURCEPORT 7627
#define DESTPORT 2776
#define IDENT 4321

int main()
{
	int sock_fd;
	int concheck, sendcheck, recvcheck;
	int size;
	int fl = 1;
	int val = 1;
	socklen_t len;
	char sendbuf[BUFSIZE] = "Hello from client!";
	char packet[BUFSIZE];
	char *mypacket;
	char recvbuf[BUFSIZE] = "";
	struct sockaddr_in serv;
	struct iphdr *ip_hdr = (struct iphdr *) packet;
	struct udphdr *udp_hdr = (struct udphdr *) (packet + sizeof(struct iphdr));
	sock_fd = socket (AF_INET, SOCK_RAW, IPPROTO_UDP);

	if(-1 == sock_fd)//при провале
	{
		perror("\nError : \n");
		printf("\nSocket creation error!\n");
		return -1;
	}
	setsockopt(sock_fd, IPPROTO_IP, IP_HDRINCL, &val, sizeof(&val));

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(DESTPORT); 

	udp_hdr->source = htons(SOURCEPORT);
	udp_hdr->dest = htons(DESTPORT);
	udp_hdr->check = htons(0);

	ip_hdr->version = 4;
	ip_hdr->ihl = 5;
	ip_hdr->tos = 0;
	//ip_hdr->len = sizeof(struct iphdr) + sizeof(struct udphdr) + strlen(mypacket);
	ip_hdr->tot_len = 0;	
	ip_hdr->id = 0;
	ip_hdr->check = 0;
	ip_hdr->saddr = 0;
	ip_hdr->id = htonl(IDENT);
	ip_hdr->frag_off = 0;
	ip_hdr->ttl = 255;
	ip_hdr->protocol = 17; //UDP
	ip_hdr->daddr = serv.sin_addr.s_addr; 

	mypacket = (char *) (packet + sizeof(struct iphdr) + sizeof(struct udphdr));
	strcpy(mypacket, sendbuf);
	udp_hdr->len = htons(sizeof(struct udphdr) + strlen(mypacket));

	sendcheck = sendto(sock_fd, packet, sizeof(packet), 0, (struct sockaddr *)&serv, sizeof(serv));
	if(-1 == sendcheck)
	{
		printf("\nSendto error!\n");
		return -3;
	}

	recvcheck = recvfrom(sock_fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&serv, &len);
	if(-1 == recvcheck)
	{
		printf("\nRecvfrom error!\n");
		return -4;
	}
 
	char tmp[BUFSIZE];
	len = sizeof(serv);
	while(fl)
	{
		recvcheck = recvfrom(sock_fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&serv, &len);
		if(-1 == recvcheck)
		{
			printf("\nRecvfrom error!\n");
			return -5;
		}

		if(inet_ntop(serv.sin_family, (void*)&(((struct sockaddr_in *)&serv)->sin_addr), tmp, sizeof(tmp)) == NULL)
		{
			perror("\nError: ");
			return -6;
		}
		
		if(strncmp(tmp, "127.0.0.1", strlen(tmp)) == 0)
		{
			printf("(from %s): %s\n", tmp, recvbuf + 28);
			fl = 0;
		}
	}
	close(sock_fd);
	return 0;
}