 ///
 /// @file    ftruncate.c
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
	int ret;
	ret = ftruncate(fd, 1 << 10);
	if (-1 == ret)
	{
		perror("ftruncate");
		return -1;
	}
	return 0;
}

