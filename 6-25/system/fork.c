 ///
 /// @file    fork.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	if (!fork())
	{
		printf("I am child\n");
		int ret = execl("./sleep", "sleep", NULL);
		printf("ret=%d\n", ret);
		while (1)
			;
	}
	else
	{
		printf("I am parent\n");
		while (1)
			;
	}
}

