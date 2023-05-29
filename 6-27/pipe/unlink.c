 ///
 /// @file    unlink.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main(int argc, char **argv)
{
	args_check(argc, 2);
	unlink(argv[1]);
	return 0;
}

