 ///
 /// @file    pthread_top.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void *threadfunc(void *p)
{
	while (1)
		;
}
int main()
{
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, threadfunc, NULL);
	while (1)
		;
}

