 ///
 /// @file    popen_w.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	FILE *fp;
	fp = popen("./scanf", "w");
	if (NULL == fp)
	{
		perror("popen");
		return -1;
	}
	int fd;
	fd = fileno(fp);
	printf("fd=%d\n", fd);
	char buf[128] = "3 4";
	write(fd, buf, strlen(buf));
	pclose(fp);
	return 0;
}

