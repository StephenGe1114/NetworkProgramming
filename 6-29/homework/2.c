 ///
 /// @file    2.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*主线程，子线程各自加1千万，通过mutex锁实现最终结果为2千万*/

#include "func.h"
#define N 10000000

typedef struct {
    int num;
    pthread_mutex_t mutex;
} data;

void* thread_func(void* p)
{
    data* p1 = (data*)p;
    for(int i = 0; i < N; ++i) {
        pthread_mutex_lock(&p1->mutex);
        ++p1->num;
        pthread_mutex_unlock(&p1->mutex);
    }
    return NULL;
}

int main()
{
    data d;
    d.num = 0;
    int ret = pthread_mutex_init(&d.mutex, NULL);
    check_thread_error(ret, "pthread_mutex_init");
    pthread_t pthid;
    ret = pthread_create(&pthid, NULL, thread_func, (void*)&d);
    check_thread_error(ret, "pthread_create");
    for(int i = 0; i < N; ++i) {
        pthread_mutex_lock(&d.mutex);
        ++d.num;
        pthread_mutex_unlock(&d.mutex);
    }
    ret = pthread_join(pthid, NULL);
    check_thread_error(ret, "pthread_join");
    printf("mainthread %d\n", d.num);
    return 0;
}
