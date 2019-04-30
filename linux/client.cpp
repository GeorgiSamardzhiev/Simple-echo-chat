#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

#define PORT 4444
#define MAX 128

int main(int argc, char *argv[]) {
	int fd, r;
	char buff[MAX] = { 0 };
	struct sockaddr_in sock;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd==-1) {
		perror("socket init");
		return 1;
	}

	char ip[MAX] = { 0 };
	std::cin>>ip;
	std::cin.ignore();

	sock.sin_family = AF_INET;
	sock.sin_addr.s_addr = inet_addr(ip);
	sock.sin_port = htons(PORT);

	if (connect(fd, (struct sockaddr *)&sock, sizeof sock) == -1) {
		close(fd);
		perror("connect fail");
		return 1;
	}

	while (strcmp(buff, "exit") != 0) {
		std::cin.getline(buff, MAX-1);

		if (send(fd, buff, strlen(buff), 0) == -1) {
			perror("send");
			return 1;
		}

		if ((r = recv(fd, buff, MAX-1, 0)) == -1) {
			perror("recv");
			return 1;
		}

		buff[r] = 0;
		printf("client: received '%s'\n", buff);
	}
	close(fd);

	return 0;
}
