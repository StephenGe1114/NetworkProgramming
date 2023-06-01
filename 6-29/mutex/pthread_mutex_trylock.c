 ///
 /// @file    pthread_mutex_trylock.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

pthread_mutex_t mutex;

void *threadfunc(void *p)
{
	pthread_mutex_lock(&mutex);
	printf("I am child thread\n");
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, threadfunc, NULL);
	usleep(1000);
	printf("after child byebye\n");
	int ret = pthread_mutex_trylock(&mutex);
	check_thread_error(ret, "pthread_mutex_trylock");
	pthread_join(thread_id, NULL);
	printf("join success\n");
	return 0;
}

