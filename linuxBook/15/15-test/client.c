#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch = 'A';
	char ipAddr[20];

	if(argc == 2)
	{
		strcpy(ipAddr, argv[1]);
	}
	else
	{
		strcpy(ipAddr, "127.0.0.1");
	}
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipAddr);
	address.sin_port = htons(9734);

	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1)
	{
		perror("oops:client1");
		printf("exit(1)");
		exit(1);
	}

	write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf("char from server: %c\n",ch);
	close(sockfd);
	exit(0);
}
