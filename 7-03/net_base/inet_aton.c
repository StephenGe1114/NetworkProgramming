 ///
 /// @file    inet_aton.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main(int argc, char *argv[])
{
	args_check(argc, 2);
	int ret;
	struct in_addr addr;
	ret = inet_aton(argv[1], &addr);
	check_error(0, ret, "inet_aton");
	printf("addr.s_addr=%x\n", addr.s_addr);
	printf("addr.s_addr=%x\n", inet_addr(argv[1]));
	printf("ip=%s\n", inet_ntoa(addr));
	return 0;
}

