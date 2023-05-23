 ///
 /// @file    chat_b.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main(int argc, char **argv)
{
	args_check(argc, 3);
	int fdw, fdr;
	fdw = open(argv[1], O_WRONLY); // 只有一端会阻塞
	if (-1 == fdw)
	{
		perror("open");
		return -1;
	}
	fdr = open(argv[2], O_RDONLY);
	printf("fdw=%d,fdr=%d\n", fdw, fdr);
	char buf[128];
	while (1)
	{
		bzero(buf, sizeof(buf));
		read(0, buf, sizeof(buf));
		write(fdw, buf, strlen(buf) - 1);
		bzero(buf, sizeof(buf));
		read(fdr, buf, sizeof(buf));
		printf("%s\n", buf);
	}
	return 0;
}

