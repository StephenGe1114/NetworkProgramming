 ///
 /// @file    writev.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	char buf[10] = "hello";
	char buf1[10] = "world";
	struct iovec iov[2];
	iov[0].iov_base = buf;
	iov[0].iov_len = 5;
	iov[1].iov_base = buf1;
	iov[1].iov_len = 5;
	int fd = open("file1", O_RDWR);
	writev(fd, iov, 2);
}

