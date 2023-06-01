 ///
 /// @file    pthread_create_arg2.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

// 线程函数
void *thread_func(void *p)
{
	printf("I am child thread,p=%ld\n", (long)p);
}

int main()
{
	pthread_t thread_id, thread_id1;
	int ret;
	ret = pthread_create(&thread_id, NULL, thread_func, (void *)1);
	check_thread_error(ret, "pthread_create");
	ret = pthread_create(&thread_id1, NULL, thread_func, (void *)2);
	check_thread_error(ret, "pthread_create");
	printf("I am main thread\n");
	ret = pthread_join(thread_id, NULL);
	check_thread_error(ret, "pthread_join");
	ret = pthread_join(thread_id1, NULL);
	return 0;
}

