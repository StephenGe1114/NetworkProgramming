 ///
 /// @file    sprintf.c
 /// @author  gsw(1499186594@qq.com)
 /// @date    2023-05-18 17:19:59
 ///
#include <stdio.h>

typedef struct {
	int num;
	char name[20];
	float score;
} stu;
         
int main(int argc, char **argv)
{
	stu s = {1001, "xiongda", 98.5};
	char buf[128] = {0};
	sprintf(buf, "%d %s %5.2f", s.num, s.name, s.score);
	puts(buf);
    return 0;
}
