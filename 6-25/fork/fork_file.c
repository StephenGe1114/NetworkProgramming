 ///
 /// @file    fork_file.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	pid_t pid;
	int fd = open("file", O_RDWR);
	pid = fork();
	if (0 == pid)
	{
		printf("I am child\n");
		char buf[128] = {0};
		read(fd, buf, 5);
		printf("I am child,buf=%s\n", buf);
	}
	else
	{
		char buf[128] = {0};
		read(fd, buf, 5);
		printf("I am parent %s\n", buf);
		sleep(1);
		return 0;
	}
}

