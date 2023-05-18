 ///
 /// @file    sscanf.c
 /// @author  gsw(1499186594@qq.com)
 /// @date    2023-05-18 17:24:50
 ///
#include <stdio.h>

typedef struct {
	int num;
	char name[20];
	float score;
} stu;

int main()
{
	stu s = {0};
	char buf[128] = "1001 xiongda 98.50";
	sscanf(buf,"%d%s%f",&s.num,s.name,&s.score);
	printf("%d %s %5.2f\n",s.num,s.name,s.score);
	return 0;
}
         
