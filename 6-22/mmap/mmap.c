 ///
 /// @file    mmap.c
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
	char *p;
	p = (char *)mmap(NULL, 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if ((char *)-1 == p)
	{
		perror("mmap");
		return -1;
	}
	printf("p[0]=%c\n", p[0]);
	p[0] = 'g';
	int ret = munmap(p, 5);
	if (-1 == ret)
	{
		perror("munmap");
		return -1;
	}
	return 0;
}

