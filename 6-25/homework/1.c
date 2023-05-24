 ///
 /// @file    1.c
 /// @author  gsw(1499186594@qq.com)
 ///

/*本机用户(你的就是你本身的那个用户)编写程序，修改文件file内容为hello，将可执行程序增加s权限,从而实现test用户能够通过该二进制修改file文件内容*/

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
	write(fd, "hello", 5);
	close(fd);
	return 0;
}

