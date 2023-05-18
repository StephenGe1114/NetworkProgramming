 ///
 /// @file    chdir.c
 /// @author  gsw(1499186594@qq.com)
 /// @date    2023-05-18 17:51:26
 ///
#include <unistd.h>
#include <stdio.h>

int main(int argc,char **argv)
{
	if(argc != 2)
	{
		printf("error args\n");
		return -1;
	}
	int ret;
	ret = chdir(argv[1]);
	if(-1 == ret)
	{
		perror("chdir");
		return -1;
	}
	char *path;
	path = getcwd(NULL,0);
	printf("path=%s\n", path);
	return 0;
}

