 ///
 /// @file    signal_dfl.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void sigfunc(int signum)
{
	printf("before sleep %d is coming\n", signum);
	signal(SIGINT, SIG_DFL);
}

int main()
{
	signal(SIGINT, sigfunc);
	while (1)
	{
		// 默认是业务代码
	}
}

