 ///
 /// @file    ctime.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include<stdio.h>
#include<time.h>
int main(void)
{
time_t t;
t=time(&t);
printf("Today'sdateandtime:%s\n",ctime(&t));
return 0;
}
