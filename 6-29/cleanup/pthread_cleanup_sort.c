 ///
 /// @file    pthread_cleanup_sort.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"
// free只写在清理函数
void cleanup(void *p)
{
	printf("I am cleanup func %ld\n", (long)p);
}
void *thread_func(void *p)
{
	printf("I am child thread\n");
	pthread_cleanup_push(cleanup, (void *)1);
	pthread_cleanup_push(cleanup, (void *)2);
	printf("I am child thread,I wake up\n");
	sleep(2);
	pthread_exit(NULL);
	pthread_cleanup_pop(1); // pop(0),弹出清理函数不执行，pop(1),弹出清理函数执行
	pthread_cleanup_pop(1); // pop(0),弹出清理函数不执行，pop(1),弹出清理函数执行
}

int main()
{
	pthread_t pthread_id;
	pthread_create(&pthread_id, NULL, thread_func, NULL);
	sleep(1);
	int ret = pthread_cancel(pthread_id);
	check_thread_error(ret, "pthread_cancel");
	long retval;
	pthread_join(pthread_id, (void **)&retval);
	printf("retval=%ld\n", retval);
	return 0;
}

