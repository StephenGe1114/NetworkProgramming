 ///
 /// @file    pthread_cond_timedwait.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

typedef struct
{
	pthread_cond_t cond;
	pthread_mutex_t mutex;
} data;

void *thread_func(void *p)
{
	data *pt = (data *)p;
	printf("before wait cond\n");
	struct timespec t;
	t.tv_sec = time(NULL) + 3;
	int ret;
	pthread_mutex_lock(&pt->mutex);
	ret = pthread_cond_timedwait(&pt->cond, &pt->mutex, &t);
	pthread_mutex_unlock(&pt->mutex);
	printf("pthread_cond_timedwait ret=%d\n", ret);
	printf("I am child,I will exit\n");
}

int main()
{
	data t;
	pthread_mutex_init(&t.mutex, NULL);
	pthread_cond_init(&t.cond, NULL);
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, thread_func, &t);
	sleep(1);
//	pthread_cond_signal(&t.cond);
	pthread_join(thread_id, NULL);
	pthread_mutex_destroy(&t.mutex);
	pthread_cond_destroy(&t.cond);
	printf("I am main thread\n");
	return 0;
}

