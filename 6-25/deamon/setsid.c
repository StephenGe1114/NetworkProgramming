 ///
 /// @file    setsid.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	if (!fork())
	{
		printf("I am child,mypid=%d,ppid=%d,sid=%d\n", getpid(), getppid(), getsid(0));
		setsid();
		printf("I am child,mypid=%d,ppid=%d,sid=%d\n", getpid(), getppid(), getsid(0));
		while (1)
			;
	}
	else
	{
		printf("I am parent pid=%d,sid=%d\n", getpid(), getsid(0));
		wait(NULL);
	}
}

