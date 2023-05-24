 ///
 /// @file    fork_global.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int i = 10;
int main()
{
	pid_t pid;
	pid = fork();
	if (0 == pid)
	{
		printf("I am child %d %p\n", i, &i);
	}
	else
	{
		printf("I am parent %d %p\n", i, &i);
		i = 5;
		printf("I am parent %d %p\n", i, &i);
		sleep(1);
		return 0;
	}
}

