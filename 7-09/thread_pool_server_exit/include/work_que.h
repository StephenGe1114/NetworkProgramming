#ifndef __WORK_QUE_H__
#define __WORK_QUE_H__
#include "head.h"

// 任务节点
typedef struct tag_node
{
	int new_fd; // accept客户端请求生成的描述符，即需要完成的任务
	struct tag_node *pNext;
} node_t, *pnode_t;

// 任务队列
typedef struct
{
	pnode_t que_head, que_tail;
	int que_capacity; // 队列最大容量
	int size; // 队列当前大小
	pthread_mutex_t que_mutex; // 任务队列是多线程共享，入队出队都要加解锁
} que_t, *pque_t;

void que_insert(pque_t, pnode_t);

void que_get(pque_t, pnode_t *);

#endif
