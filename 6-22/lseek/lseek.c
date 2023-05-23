 ///
 /// @file    lseek.c
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
	off_t ret;
	ret = lseek(fd, 1024, 2);
	printf("ret=%ld\n", ret);
	char c = 'w';
	write(fd, &c, sizeof(char));
	close(fd);
	return 0;
}

