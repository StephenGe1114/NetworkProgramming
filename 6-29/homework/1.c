 ///
 /// @file    1.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*创建一个子线程，传入数值1，在子线程中能够获取并打印，子线程退出，返回数值2，主线程通过pthread_join获取等待子线程结束并获取子线程的退出值并打印*/

#include "func.h"

void* thread_func(void* p)
{
    printf("subthread %ld\n", (long)p);
    pthread_exit((void*)2);
}

int main()
{
    pthread_t pthid;
    int ret = pthread_create(&pthid, NULL, thread_func, (void*)1);
    check_thread_error(ret, "pthread_create");
    long l;
    pthread_join(pthid, (void**)&l);
    printf("mainthread %ld\n", l);
    return 0;
}
