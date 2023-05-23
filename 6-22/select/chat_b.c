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
	fd_set rdset;
	int ret;
	while (1)
	{
		FD_ZERO(&rdset);
		FD_SET(0, &rdset);
		FD_SET(fdr, &rdset);
		ret = select(fdr + 1, &rdset, NULL, NULL, NULL);
		if (ret > 0)
		{
			if (FD_ISSET(fdr, &rdset))
			{
				memset(buf, 0, sizeof(buf));
				ret = read(fdr, buf, sizeof(buf)); // 缓冲区为空的时候，读端会卡主
				if (0 == ret)
				{
					printf("byebye\n");
					break;
				}
				printf("%s\n", buf);
			}
			if (FD_ISSET(0, &rdset))
			{
				memset(buf, 0, sizeof(buf));
				read(0, buf, sizeof(buf));
				write(fdw, buf, strlen(buf) - 1);
			}
		}
	}
	return 0;
}

