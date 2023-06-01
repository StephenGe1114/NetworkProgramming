 ///
 /// @file    pthread_create_exit_int.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

// 线程函数
void *thread_func(void *p)
{
	printf("I am child thread\n");
	pthread_exit((void *)0); // 返回值
}

int main()
{
	pthread_t thread_id;
	int ret;
	ret = pthread_create(&thread_id, NULL, thread_func, NULL);
	check_thread_error(ret, "pthread_create");
	printf("I am main thread\n");
	long l;
	ret = pthread_join(thread_id, (void **)&l);
	check_thread_error(ret, "pthread_join");
	printf("main thread %ld\n", l);
	return 0;
}

