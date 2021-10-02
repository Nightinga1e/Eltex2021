#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <arpa/inet.h>

#define BUFSIZE 1024
#define SOURCEPORT 7627
#define DESTPORT 2776
#define IDENT 4321
//#define SOURCEPORT 24
//#define DESTPORT 24

const char *ifname = "enp0s3";

int main()
{
	unsigned char dest_mac[6] = {0x08,0x00,0x27,0xee,0x73,0x6f}; 
	unsigned char dest_ip[4] = {10,0,2,4};
	unsigned char src_mac[6] = {0x08,0x00,0x27,0x1e,0x29,0xfe};
	unsigned char src_ip[4] = {10,0,2,6};
	char buf[128]; //for checksum
	int csum = 0; //cs
	int cstmp = 0; //cs
	short *ptr; //cs
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
	struct sockaddr_ll sockll;
	struct ether_header *eth_hdr = (struct ether_header *) packet;
	struct iphdr *ip_hdr = (struct iphdr *) (packet + sizeof(struct ether_header));
	struct udphdr *udp_hdr = (struct udphdr *) (packet + sizeof(struct ether_header) + sizeof(struct iphdr));

	sock_fd = socket (AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	if(-1 == sock_fd)//при провале
	{
		perror("\nError : \n");
		printf("\nSocket creation error!\n");
		return -1;
	}
	setsockopt(sock_fd, IPPROTO_IP, IP_HDRINCL, &val, sizeof(&val));

	sockll.sll_family = AF_PACKET;
	sockll.sll_halen = 6;
	sockll.sll_ifindex = if_nametoindex(ifname);

	if(0 == sockll.sll_ifindex)
	{
		perror("\nError: \n");
		printf("\nIndex error!\n");
		return -2;
	}

	memcpy(eth_hdr->ether_dhost, dest_mac, 6);
	memcpy(eth_hdr->ether_shost, src_mac, 6);	
	
	udp_hdr->source = htons(SOURCEPORT);
	udp_hdr->dest = htons(DESTPORT);
	udp_hdr->check = htons(0);


	ptr = (short *) packet;
	for(int i = 0; i < 10; i++)
	{
		csum = csum + *ptr;
		ptr++;
	}
	cstmp = csum >> 16;
	csum = csum + cstmp;
	csum = ~csum;

	ip_hdr->version = 4;
	ip_hdr->ihl = 5;
	ip_hdr->tos = 0;
	ip_hdr->tot_len = 0;	
	ip_hdr->id = 0;
	ip_hdr->check = csum;
	//ip_hdr->saddr = 0;
	ip_hdr->id = htonl(IDENT);
	ip_hdr->frag_off = 0;
	ip_hdr->ttl = 255;
	ip_hdr->protocol = 17; //UDP
	//ip_hdr->daddr = sockll.sll_addr.s_addr; 
	memcpy(&ip_hdr->saddr, src_ip, 4);
	memcpy(&ip_hdr->daddr, dest_ip, 4);
	
	mypacket = (char *) (packet + sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr));
	strcpy(mypacket, sendbuf);
	udp_hdr->len = htons(sizeof(struct udphdr) + strlen(mypacket));

	sendcheck = sendto(sock_fd, packet, sizeof(packet), 0, (struct sockaddr *)&sockll, sizeof(sockll));
	if(-1 == sendcheck)
	{
		printf("\nSendto error!\n");
		return -3;
	}

/*
	recvcheck = recvfrom(sock_fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&serv, &len);
	if(-1 == recvcheck)
	{
		printf("\nRecvfrom error!\n");
		return -4;
	}
*/

	char tmp[BUFSIZE];
	len = sizeof(sockll);
	while(fl)
	{
		recvcheck = recvfrom(sock_fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&sockll, &len);
		if(-1 == recvcheck)
		{
			printf("\nRecvfrom error!\n");
			return -5;
		}

		if(inet_ntop(sockll.sll_family, (void*)&(((struct sockaddr_ll *)&sockll)->sll_addr), tmp, sizeof(tmp)) == NULL)
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