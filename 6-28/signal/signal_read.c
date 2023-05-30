 ///
 /// @file    signal_read.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void sigfunc(int signum)
{
	printf("before sleep %d is coming\n", signum);
	sleep(3);
	printf("after sleep %d is coming\n", signum);
}

int main()
{
	signal(SIGINT, sigfunc);
	signal(SIGQUIT, sigfunc);
	char buf[128] = {0};
	read(0, buf, sizeof(buf));
	return 0;
}

