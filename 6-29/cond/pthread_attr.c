 ///
 /// @file    pthread_attr.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"
// 设置线程属性
void *threadfunc(void *p)
{
	printf("I am child thread\n");
	pthread_exit(NULL);
}
int main()
{
	pthread_t thread_id;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread_id, &attr, threadfunc, NULL);
	long retval = 10;
	pthread_join(thread_id, (void **)&retval);
	printf("retval=%ld\n", retval);
	sleep(1);
}

