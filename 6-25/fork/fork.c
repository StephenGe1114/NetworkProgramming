 ///
 /// @file    fork.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	pid_t pid;
	pid = fork();
	if (0 == pid)
	{
		printf("I am child mypid=%d,myppid=%d\n", getpid(), getppid());
		while (1)
			;
	}
	else
	{
		printf("I am parent,mypid=%d,mychildpid=%d\n", getpid(), pid);
		sleep(1);
		while (1)
			;
		return 0;
	}
}

