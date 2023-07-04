 ///
 /// @file    read_stdin.c
 /// @author  gsw(1499186594@qq.com)
 ///

#include "func.h"

void change_fd_status(int fd)
{
	int status = fcntl(fd, F_GETFL);
	status = status | O_NONBLOCK; // 将描述符设置为非阻塞
	fcntl(fd, F_SETFL, status);
}

void change_fd_status2(int fd)
{
	int status = fcntl(fd, F_GETFL);
	status = status & ~O_NONBLOCK; // 将描述符设置为阻塞
	fcntl(fd, F_SETFL, status);
}

int main()
{
	char buf[128] = {0};
	change_fd_status(0);
	sleep(5);
	int ret = read(0, buf, sizeof(buf));
	printf("ret=%d,buf=%s,errno=%d\n", ret, buf, errno);
	change_fd_status2(0);
	ret = read(0, buf, sizeof(buf));
	printf("ret=%d,buf=%s,errno=%d\n", ret, buf, errno);
	return 0;
}

