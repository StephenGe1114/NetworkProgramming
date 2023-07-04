 ///
 /// @file    rename.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include <stdio.h>

int main(int argc, char *argv[])
{
	int ret;
	ret = rename(argv[1], argv[2]);
	if (-1 == ret)
	{
		perror("rename");
		return -1;
	}
	return 0;
}

