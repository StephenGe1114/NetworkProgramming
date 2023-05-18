 ///
 /// @file    chmod.c
 /// @author  gsw(1499186594@qq.com)
 /// @date    2023-05-18 17:45:10
 ///
#include <sys/stat.h>
#include <stdio.h>
         
int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("error args\n");
		return -1;
	}
	int ret;
	ret = chmod(argv[1], 0222);
	if(-1 == ret)
	{
		perror("chmod");
		return -1;
	}
    return 0;
}
