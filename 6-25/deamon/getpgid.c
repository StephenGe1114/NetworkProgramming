 ///
 /// @file    getpgid.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	if (!fork())
	{
		printf("I am child,mypid=%d,ppid=%d,pgid=%d\n", getpid(), getppid(), getpgid(0));
		setpgid(0, 0);
		printf("I am child,mypid=%d,ppid=%d,pgid=%d\n", getpid(), getppid(), getpgid(0));
		while (1)
			;
	}
	else
	{
		printf("I am parent pid=%d,pgid=%d\n", getpid(), getpgid(0));
		wait(NULL);
	}
}

