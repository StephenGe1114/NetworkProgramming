 ///
 /// @file    read.c
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
	char buf[128] = {0};
	int ret;
	ret = read(fd, buf, sizeof(buf));
	if (-1 == ret)
	{
		perror("read");
		return -1;
	}
	printf("ret=%d,buf=%s\n", ret, buf);
	return 0;
}

