 ///
 /// @file    4.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*子线程，主线程，同时对一个全局变量加2千万，通过加锁，实现最终效果是4千万,通过gettimeofday统计各加2千万的时间消耗*/

#include "func.h"
#define N 20000000

typedef struct
{
    int sum;
    pthread_mutex_t mutex;
} Data;

void *thread_func(void *p)
{
    Data *pd = (Data *)p;
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_lock(&pd->mutex);
        ++pd->sum;
        pthread_mutex_unlock(&pd->mutex);
    }
    return NULL;
}

int main()
{
    Data d;
    d.sum = 0;
    pthread_mutex_init(&d.mutex, NULL);
    pthread_t pthid;
    struct timeval start, end;
    memset(&start, 0, sizeof(start));
    memset(&end, 0, sizeof(end));
    gettimeofday(&start, NULL);
    pthread_create(&pthid, NULL, thread_func, &d);
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_lock(&d.mutex);
        ++d.sum;
        pthread_mutex_unlock(&d.mutex);
    }
    pthread_join(pthid, NULL);
    gettimeofday(&end, NULL);
    pthread_mutex_destroy(&d.mutex);
    printf("mainthread time us = %ld, sum = %d\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec, d.sum);
    return 0;
}
