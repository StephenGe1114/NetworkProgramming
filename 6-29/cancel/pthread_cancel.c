 ///
 /// @file    pthread_cancel.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void *thread_func(void *p)
{
	printf("I am child thread\n");
	printf("I am child thread,I wake up\n");
	return (void *)0;
}

int main()
{
	pthread_t pthread_id;
	pthread_create(&pthread_id, NULL, thread_func, NULL);
	int ret = pthread_cancel(pthread_id);
	check_thread_error(ret, "pthread_cancel");
	long retval;
	pthread_join(pthread_id, (void **)&retval);
	printf("retval=%ld\n", retval);
	return 0;
}

