 ///
 /// @file    getcwd.c
 /// @author  gsw(1499186594@qq.com)
 /// @date    2023-05-18 23:06:41
 ///
#include <unistd.h>
#include <stdio.h>

int main()
{
	char *path;
	path = getcwd(NULL, 0);
	printf("path=%s\n", path);
	return 0;
}

