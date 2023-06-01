 ///
 /// @file    5.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*子线程等待在一个条件变量上，主线程发送signal，使条件成立，然后子线程唤醒得到执行，正常结束，然后主线程回收子线程*/

#include "func.h"

typedef struct{
	pthread_cond_t cond;
	pthread_mutex_t mutex;
} data;

void *thread_func(void *p)
{
    data* pd = (data*)p;
    pthread_mutex_lock(&pd->mutex);
    printf("subthread 1\n");
    pthread_cond_wait(&pd->cond, &pd->mutex);
    printf("subthread 2\n");
    pthread_mutex_unlock(&pd->mutex);
    return NULL;
}

int main()
{
    data d;
    pthread_cond_init(&d.cond, NULL);
    pthread_mutex_init(&d.mutex, NULL);
    pthread_t pthid;
    pthread_create(&pthid, NULL, thread_func, &d);
	sleep(1);
    pthread_cond_signal(&d.cond);
    pthread_join(pthid, NULL);
    pthread_cond_destroy(&d.cond);
    pthread_mutex_destroy(&d.mutex);

    return 0;
}
