 ///
 /// @file    wait.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	pid_t pid;
	pid = fork();
	if (!pid)
	{
		printf("I am child,pid=%d\n", getpid());
		return 1;
	}
	else
	{
		printf("I am parent\n");
		wait(NULL); // 等待子进程退出
		return 0;
	}
}

