 ///
 /// @file    zombie.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	if (!fork())
	{
		printf("I am child,pid=%d\n", getpid());
	}
	else
	{
		while (1)
			;
	}
}

