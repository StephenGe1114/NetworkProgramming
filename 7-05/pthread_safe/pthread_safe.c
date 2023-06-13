 ///
 /// @file    pthread_safe.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void *thread_func(void *p)
{
	sleep(2);
	time_t t = time(NULL);
	char *p1;
	p1 = ctime(&t);
	printf("I am child,p1=%p,p1=%s\n", p1, p1);
}

int main()
{
	pthread_t pthid;
	pthread_create(&pthid, NULL, thread_func, NULL);
	char *p;
	time_t t = time(NULL); // 获取当前的秒数
	p = ctime(&t);
	printf("I am main,p=%p,p=%s\n", p, p);
	pthread_join(pthid, NULL);
	sleep(5);
	printf("I am main,p=%p,p=%s\n", p, p);
	return 0;
}

