 ///
 /// @file    popen_r.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	FILE *fp;
	fp = popen("./print", "r");
	if (NULL == fp)
	{
		perror("popen");
		return -1;
	}
	int fd;
	fd = fileno(fp);
	printf("fd=%d\n", fd);
	char buf[128] = {0};
	read(fd, buf, sizeof(buf));
	printf("buf=%s\n", buf);
	return 0;
}

