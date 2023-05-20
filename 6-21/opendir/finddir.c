 ///
 /// @file    finddir.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void printdir(char *path, int width)
{
	DIR *dir;
	dir = opendir(path);
	if (!dir)
	{
		perror("opendir");
		return;
	}
	struct dirent *p;
	char buf[512] = {0};
	while ((p = readdir(dir)) != NULL)
	{
		if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
		{
		}
		else
		{
			printf("%*s%s\n", width, "", p->d_name);
			if (p->d_type == 4)
			{
				sprintf(buf, "%s%s%s", path, "/", p->d_name); // 路径拼接
				printdir(buf, width + 4);
			}
		}
	}
	closedir(dir);
}

int main(int argc, char *argv[])
{
	args_check(argc, 2);
	puts(argv[1]);
	printdir(argv[1], 4);
	return 0;
}

