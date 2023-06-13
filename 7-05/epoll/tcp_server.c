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
	char buf[128] = {0};
	int epfd = epoll_create(1);
	struct epoll_event event, evs[3];
	event.events = EPOLLIN; // 是否可读
	event.data.fd = STDIN_FILENO;
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
	check_error(-1, ret, "epoll_ctl");
	event.data.fd = sfd;
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &event);
	check_error(-1, ret, "epoll_ctl1");
	int i;
	// 多路复用
	while (1)
	{
		ret = epoll_wait(epfd, evs, 3, -1);
		for (i = 0; i < ret; i++)
		{
			if (evs[i].data.fd == sfd) // sfd可读
			{
				new_fd = accept(sfd, (struct sockaddr *)&cli, &len);
				event.data.fd = new_fd;
				epoll_ctl(epfd, EPOLL_CTL_ADD, new_fd, &event);
				printf("ip=%s,port=%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
			}
			if (evs[i].data.fd == new_fd)
			{
				bzero(buf, sizeof(buf));
				ret = recv(new_fd, buf, sizeof(buf), 0);
				if (ret > 0)
				{
					printf("%s\n", buf);
				}
				else
				{
					event.data.fd = new_fd;
					epoll_ctl(epfd, EPOLL_CTL_DEL, new_fd, &event); // 解注册
					close(new_fd);
					printf("byebye\n");
				}
			}
			if (EPOLLIN == evs[i].events && evs[i].data.fd == STDIN_FILENO)
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

