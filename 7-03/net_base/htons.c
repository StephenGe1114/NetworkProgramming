 ///
 /// @file    htons.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	unsigned short port = 0x1234;
	printf("%d\n", port);
	unsigned short nport;
	nport = htons(port);
}



