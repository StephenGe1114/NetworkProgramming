 ///
 /// @file    write.c
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
	int val = 100;
	int ret;
	ret = write(fd, &val, sizeof(val));
	if (-1 == ret)
	{
		perror("write");
		return -1;
	}
	printf("ret=%d\n", ret);
	return 0;
}

