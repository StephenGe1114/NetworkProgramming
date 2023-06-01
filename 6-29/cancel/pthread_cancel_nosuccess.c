 ///
 /// @file    pthread_cancel_nosuccess.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void *thread_func(void *p)
{
	while (1)
		;
	return NULL;
}

int main()
{
	pthread_t pthread_id;
	pthread_create(&pthread_id, NULL, thread_func, NULL);
	int ret = pthread_cancel(pthread_id);
	check_thread_error(ret, "pthread_cancel");
	pthread_join(pthread_id, NULL);
	return 0;
}

