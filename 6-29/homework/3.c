 ///
 /// @file    3.c
 /// @author  gsw(1499186594@qq.com)
 ///

/*创建一个子线程，子线程申请内存，通过清理函数进行free，子线程停留在read标准输入，主线程cancel子线程，子线程能够通过清理函数free对应的malloc的内存*/

#include "func.h"

void clean(void* p)
{
	printf("buf = %s\n", (char*)p);
    free(p);
    printf("I am clean\n");
}

void* thread_func(void* p)
{
    p = calloc(1, 5);
    strcpy(p, "hello");
    char buf[128] = {0};
    pthread_cleanup_push(clean, p);
    read(0, buf, sizeof(buf));
    pthread_cleanup_pop(0);
	return NULL;
}

int main()
{
    pthread_t pthid;
    pthread_create(&pthid, NULL, thread_func, NULL);
    pthread_cancel(pthid);
    long l;
    pthread_join(pthid, (void**)&l);
    printf("mainthread l = %ld\n", l);
    return 0;
}
