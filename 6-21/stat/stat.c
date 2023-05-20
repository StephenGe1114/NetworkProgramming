 ///
 /// @file    stat.c
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
	struct stat buf;
	int ret;
	char path[512] = {0};
	while ((p = readdir(dir)) != NULL)
	{
		sprintf(path, "%s%s%s", argv[1], "/", p->d_name);
		ret = stat(path, &buf);
		if (-1 == ret)
		{
			perror("stat");
			return -1;
		}
		printf("inode=%ld,mode=%x,nlink=%ld,uid=%s,gid=%s,size=%ld,mtime=%s %s\n", buf.st_ino, buf.st_mode, buf.st_nlink, getpwuid(buf.st_uid)->pw_name, getgrgid(buf.st_gid)->gr_name, buf.st_size, ctime(&buf.st_mtime), p->d_name);
	}
	closedir(dir);
	return 0;
}

