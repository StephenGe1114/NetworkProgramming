 ///
 /// @file    dup2.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main(int argc, char **argv)
{
	args_check(argc, 2);
	int fd;
	fd = open(argv[1], O_RDWR);
	if (-1 == fd)
	{
		perror("open");
		return -1;
	}
	printf("fd=%d\n", fd);
	int fd2;
	fflush(stdout);
	fd2 = dup2(fd, 1); // 描述符的复制
	printf("fd2=%d\n", fd2);
	printf("you can't see me\n");
	return 0;
}

