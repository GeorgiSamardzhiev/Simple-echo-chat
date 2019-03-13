#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

#define PORT 4444
#define MAX 255

int main(int argc, char *argv[]) {
	int fd, numbytes;
	char buff[MAX] = { 0 };
	struct sockaddr_in sock;


	fd = socket(PF_INET, SOCK_STREAM, 0);
	if (fd==-1) {
		perror("socket init");
		return 1;
	}

	char ip[MAX] = { 0 };
	std::cin>>ip;

	sock.sin_family = PF_INET;
	sock.sin_addr.s_addr = inet_addr(ip);
	sock.sin_port = htons(PORT);

	if (connect(fd, (struct sockaddr *)&sock, sizeof sock) == -1) {
		close(fd);
		perror("connect fail");
		return 1;
	}

	std::cin>>buff;

	if (send(fd, buff, strlen(buff), 0) == -1) {
		perror("send");
	}

	if ((numbytes = recv(fd, buff, MAX-1, 0)) == -1) {
		perror("recv");
		exit(1);
	}

	buff[numbytes] = 0;

	printf("client: received '%s'\n", buff);

	close(fd);

	return 0;
}
