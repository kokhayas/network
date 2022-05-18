#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define MAXLINE 4096
#define SA struct sockaddr_in6

int main(int argc, char *argv[])
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in6 servaddr;

	if ((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error");
	}

	memset(&servaddr, 0, sizeof(servaddr)); //bzero
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port = htons(13);
	if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
	{
		printf("inet_pton error: %s\n", argv[1]);
		exit(1);
	}
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect error");
	}
	while ((n = read(sockfd, recvline, MAXLINE)) > 0)
	{
		recvline[n] = '\0';
		if (fputs(recvline, stdout) == EOF)
		{
			perror("fputs error");
		}
	}
	if (n < 0)
	{
		perror("read error");
	}
	close(sockfd);
	exit(0);
}