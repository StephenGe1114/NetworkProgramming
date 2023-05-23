 ///
 /// @file    chat_a.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main(int argc, char **argv)
{
	args_check(argc, 3);
	int fdr, fdw;
	fdr = open(argv[1], O_RDONLY);
	if (-1 == fdr)
	{
		perror("open1");
		return -1;
	}
	fdw = open(argv[2], O_WRONLY);
	printf("fdr=%d,fdw=%d\n", fdr, fdw);
	char buf[128] = {0};
	int ret;
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		ret = read(fdr, buf, sizeof(buf)); // 缓冲区为空的时候，读端会卡主
		printf("%s\n", buf);
		memset(buf, 0, sizeof(buf));
		read(0, buf, sizeof(buf));
		write(fdw, buf, strlen(buf) - 1);
	}
	return 0;
}

