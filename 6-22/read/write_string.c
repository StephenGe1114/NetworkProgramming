 ///
 /// @file    write_string.c
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
	char buf[128] = "world";
	int ret;
	ret = write(fd, buf, strlen(buf));
	if (-1 == ret)
	{
		perror("write");
		return -1;
	}
	printf("ret=%d\n", ret);
	return 0;
}

