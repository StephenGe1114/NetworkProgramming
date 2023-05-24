 ///
 /// @file    orphan.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	if (!fork())
	{
		while (1)
			;
	}
	else
	{
		return 0;
	}
}

