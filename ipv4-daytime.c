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
#define SA struct sockaddr

int main(int argc, char *argv[])
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr; //接続先のIP　addressやport情報を保持するため

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error");
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) // argv[1]=133.11.205.155
	{
		printf("inet_pton error: %s\n", argv[1]);
		exit(1);
	}
	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
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