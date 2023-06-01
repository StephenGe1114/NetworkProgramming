 ///
 /// @file    pthread_create.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

// 线程函数
void *thread_func(void *p)
{
	printf("I am child thread\n");
	p = calloc(1, 20);
	strcpy((char *)p, "hello");
		;
	pthread_exit(p);
}

int main()
{
	pthread_t thread_id;
	int ret;
	ret = pthread_create(&thread_id, NULL, thread_func, NULL);
	check_thread_error(ret, "pthread_create");
	printf("I am main thread\n");
	void *thread_ret;
	ret = pthread_join(thread_id, &thread_ret);
	check_thread_error(ret, "pthread_join");
	printf("main thread %s\n", (char *)thread_ret);
	return 0;
}

