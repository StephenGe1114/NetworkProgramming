 ///
 /// @file    tcp_server.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"
#define N 5
int main(int argc, char **argv)
{
	args_check(argc, 3);
	int sfd;
	// 初始化socket
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	check_error(-1, sfd, "socket");
	struct sockaddr_in ser;
	bzero(&ser, sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[2]));	  // 端口号转换为网络字节序
	ser.sin_addr.s_addr = inet_addr(argv[1]); // 点分10进制的IP地址转为网络字节序
	int ret;
	ret = bind(sfd, (struct sockaddr *)&ser, sizeof(ser));
	check_error(-1, sfd, "bind");
	listen(sfd, 10);
	int new_fd[N];
	struct sockaddr_in cli;
	bzero(&cli, sizeof(cli));
	int len = sizeof(cli);
	char buf[128] = {0};
	fd_set readfds;
	fd_set tmpfds; // 始终记录要监控的描述符
	FD_ZERO(&tmpfds);
	FD_SET(sfd, &tmpfds);
	FD_SET(STDIN_FILENO, &tmpfds);
	memset(new_fd, -1, sizeof(new_fd));
	int i;
	// 多路复用
	while (1)
	{
		FD_ZERO(&readfds);
		memcpy(&readfds, &tmpfds, sizeof(fd_set));
		ret = select(13, &readfds, NULL, NULL, NULL);
		if (ret > 0)
		{
			if (FD_ISSET(sfd, &readfds))
			{
				// 找到位置为-1的元素
				for (i = 0; i < N; i++)
				{
					if (-1 == new_fd[i])
					{
						break;
					}
				}
				new_fd[i] = accept(sfd, (struct sockaddr *)&cli, &len);
				FD_SET(new_fd[i], &tmpfds);
				printf("ip=%s,port=%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
			}
			for (i = 0; i < N; i++)
			{
				if (new_fd[i] != -1 && FD_ISSET(new_fd[i], &readfds))
				{
					bzero(buf, sizeof(buf));
					ret = recv(new_fd[i], buf, sizeof(buf), 0);
					if (ret > 0)
					{
						printf("%s\n", buf);
					}
					else
					{
						close(new_fd[i]);
						FD_CLR(new_fd[i], &tmpfds); // 断开后不再监控
						new_fd[i] = -1;
						printf("byebye\n");
					}
				}
			}
			if (FD_ISSET(STDIN_FILENO, &readfds))
			{
				bzero(buf, sizeof(buf));
				read(STDIN_FILENO, buf, sizeof(buf));
				for (i = 0; i < N; i++)
				{
					new_fd[i] != -1 && send(new_fd[i], buf, strlen(buf) - 1, 0);
				}
			}
		}
	}
	close(sfd);
}

