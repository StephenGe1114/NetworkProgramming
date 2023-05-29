 ///
 /// @file    mkfifo.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main(int argc, char **argv)
{
	args_check(argc, 2);
	int ret;
	ret = mkfifo(argv[1], 0666);
	if (-1 == ret)
	{
		perror("mkfifo");
		return -1;
	}
	return 0;
}

