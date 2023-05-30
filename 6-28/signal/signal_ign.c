 ///
 /// @file    signal_ign.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		// 默认是业务代码
	}
}

