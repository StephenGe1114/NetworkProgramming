 ///
 /// @file    pipe.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	int fds[2];
	pipe(fds);
	if (!fork())
	{
		close(fds[1]);
		char buf[128] = {0};
		read(fds[0], buf, sizeof(buf));
		printf("I am child,buf=%s\n", buf);
		close(fds[0]);
	}
	else
	{
		close(fds[0]);
		write(fds[1], "I am meimei", 11);
		wait(NULL);
		close(fds[1]);
	}
}

