 ///
 /// @file    pthread_create_arg.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

// 线程函数
void *thread_func(void *p)
{
	printf("I am child thread,p=%s\n", (char *)p);
}

int main()
{
	pthread_t thread_id;
	int ret;
	char *p = (char *)calloc(1, 20);
	strcpy(p, "hello");
	ret = pthread_create(&thread_id, NULL, thread_func, p);
	check_thread_error(ret, "pthread_create");
	printf("I am main thread\n");
	ret = pthread_join(thread_id, NULL);
	check_thread_error(ret, "pthread_join");
	return 0;
}

