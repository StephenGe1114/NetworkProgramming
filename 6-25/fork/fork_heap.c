 ///
 /// @file    fork_heap.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	pid_t pid;
	char *p = (char *)malloc(20);
	strcpy(p, "hello");
	pid = fork();
	if (0 == pid)
	{
		printf("I am child %s %p\n", p, p);
	}
	else
	{
		printf("I am parent %s %p\n", p, p);
		strcpy(p, "world");
		printf("I am parent %s %p\n", p, p);
		sleep(1);
		return 0;
	}
}

