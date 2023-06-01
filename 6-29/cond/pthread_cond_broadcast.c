 ///
 /// @file    pthread_cond_broadcast.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"
// signal 一次只能唤醒一个线程
typedef struct
{
	pthread_cond_t cond;
	pthread_mutex_t mutex;
} data;

void *thread_func(void *p)
{
	data *pt = (data *)p;
	printf("before wait cond\n");
	pthread_mutex_lock(&pt->mutex);
	pthread_cond_wait(&pt->cond, &pt->mutex);
	pthread_mutex_unlock(&pt->mutex);
	printf("I am child,I will exit\n");
}

int main()
{
	data t;
	pthread_mutex_init(&t.mutex, NULL);
	pthread_cond_init(&t.cond, NULL);
	pthread_t thread_id, thread_id1;
	pthread_create(&thread_id, NULL, thread_func, &t);
	pthread_create(&thread_id1, NULL, thread_func, &t);
	sleep(1);
	pthread_cond_broadcast(&t.cond); // 让条件成立
	pthread_join(thread_id, NULL);
	pthread_join(thread_id1, NULL);
	pthread_mutex_destroy(&t.mutex);
	pthread_cond_destroy(&t.cond);
	printf("I am main thread\n");
	return 0;
}

