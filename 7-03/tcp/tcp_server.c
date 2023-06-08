 ///
 /// @file    tcp_server.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

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
	int new_fd;
	struct sockaddr_in cli;
	bzero(&cli, sizeof(cli));
	int len = sizeof(cli);
	printf("before accept\n");
	new_fd = accept(sfd, (struct sockaddr *)&cli, &len);
	printf("after accept ip=%s,port=%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
	char buf[128] = {0};
	fd_set readfds;
	// 多路复用
	while (1)
	{
		FD_ZERO(&readfds);
		FD_SET(new_fd, &readfds);
		FD_SET(STDIN_FILENO, &readfds);
		ret = select(new_fd + 1, &readfds, NULL, NULL, NULL);
		if (ret > 0)
		{
			if (FD_ISSET(new_fd, &readfds))
			{
				bzero(buf, sizeof(buf));
				ret = recv(new_fd, buf, sizeof(buf), 0);
				if (ret > 0)
				{
					printf("%s\n", buf);
				}
				else
				{
					printf("byebye\n");
					break;
				}
			}
			if (FD_ISSET(STDIN_FILENO, &readfds))
			{
				bzero(buf, sizeof(buf));
				read(STDIN_FILENO, buf, sizeof(buf));
				send(new_fd, buf, strlen(buf) - 1, 0);
			}
		}
	}
	close(new_fd);
	close(sfd);
}

