 ///
 /// @file    opendir.c
 /// @author  gsw(1499186594@qq.com)
 ///
     
#include "func.h"

int main(int argc, char *argv[])
{
	args_check(argc, 2);
	DIR *dir;
	dir = opendir(argv[1]);
	if (!dir)
	{
		perror("opendir");
		return -1;
	}
	struct dirent *p;
	off_t pos;
	while ((p = readdir(dir)) != NULL)
	{
		printf("ino=%ld d_reclen=%d d_type=%d d_name=%s\n", p->d_ino, p->d_reclen, p->d_type, p->d_name);
		if (!strcmp(p->d_name, "a.out"))
		{
			pos = telldir(dir);
		}
	}
	seekdir(dir, pos);
	p = readdir(dir); // 每次读取，指针自动偏移一位
	printf("pos = %ld\n", pos);
	pos = telldir(dir);
	printf("pos = %ld\n", pos);


	printf("%s\n", p->d_name);
	printf("-----------------------\n");
	rewinddir(dir);
	p = readdir(dir);
	printf("%s\n", p->d_name);
	closedir(dir);
	return 0;
}

