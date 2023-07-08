#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"

typedef void *(*thread_func_t)(void *p);

// 管理线程池的数据结构
typedef struct
{
	pthread_t *pth_id;		  // 线程id的起始地址
	int pthread_num;		  // 创建的线程数目
	que_t que;				  // 任务队列
	thread_func_t threadfunc; // 线程函数
	pthread_cond_t cond; // 当任务队列不为空时，条件成立
	short start_flag; // 线程是否启动标志
} factory, *pfac;

int factory_init(pfac, thread_func_t, int, int);

int factory_start(pfac);

int tcp_start_listen(int *, char *, char *, int);

int tran_file(int);

int send_n(int, char *, int);

#define FILENAME "file"

typedef struct
{
	int len;
	char buf[1000];
} train;

#endif
