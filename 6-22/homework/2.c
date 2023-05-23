 ///
 /// @file    2.c
 /// @author  gsw(1499186594@qq.com)
 ///
   

/* 新建一个文件，里边内容为hello，通过mmap映射该文件后，修改hello为world，然后解除映射 */

#include "func.h"

int main(int argc, char **argv)
{
	args_check(argc, 2);
	int fd = open(argv[1], O_RDWR | O_CREAT, 0666);
	if(-1 == fd) {
		perror("open");
		return -1;
	}

	int ret = write(fd, "hello", 5);
	if(-1 == ret) {
		perror("write");
		return -1;
	}

	char* p = (char*)mmap(NULL, 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if((char*)-1 == p) {
		perror("mmap");
		return -1;
	}
	memset(p, 0, 5);
	strcpy(p, "world");

	ret = munmap(p, 5);

	close(fd);

    return 0;
}
