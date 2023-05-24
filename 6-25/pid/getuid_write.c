#include "func.h"

int main()
{
	printf("uid=%d,gid=%d,euid=%d,egid=%d\n", getuid(), getgid(), geteuid(), getegid());
	int fd;
	fd = open("file", O_RDWR);
	if (-1 == fd)
	{
		perror("open");
		return -1;
	}
	write(fd, "haha", 4);
	close(fd);
	return 0;
}
