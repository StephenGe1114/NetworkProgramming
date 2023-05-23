 ///
 /// @file    1.c
 /// @author  gsw(1499186594@qq.com)
 ///
   

/* 定义一个学生结构体类型struct student，里边含有学号，姓名，分数，定义结构体数组struct student s[3], 给数组赋初值后，写入文件，然后通过lseek偏移到开头，然后再读取进行打印输出 */

#include "func.h"

typedef struct student
{
    int num;
    char name[24];
    float score;
} stu;

int main(int argc, char **argv)
{
    args_check(argc, 2);
    stu s[3] = {{1, "zhangsan", 78.5}, {2, "lisi", 65.5}, {3, "wangwu", 95.5}};
    int fd = open(argv[1], O_RDWR);
    if (-1 == fd)
    {
        perror("open");
        return -1;
    }

    char buf[3][128] = {0};
    for (int i = 0; i < 3; i++)
    {
        sprintf(buf[i], "%d %s %5.2f\n", s[i].num, s[i].name, s[i].score);
    }

    int ret;
    for (int i = 0; i < 3; i++)
    {
        ret = write(fd, buf[i], strlen(buf[i]));
        if (-1 == ret)
        {
            perror("write");
            return -1;
        }
    }

    ret = lseek(fd, 0, 0);
    printf("ret = %d\n", ret);
    if(-1 == ret) {
        perror("lseek");
        return -1;
    }

	char buf1[128] = {0};
	ret = read(fd, buf1, sizeof(buf1));
	if(-1 == ret) {
		perror("read");
		return -1;
	}
	printf("%s", buf1);

    close(fd);

    return 0;
}
