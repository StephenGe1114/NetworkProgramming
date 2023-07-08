#include "factory.h"

int exit_fds[2];

void *download_file(void *p)
{
	pfac pf = (pfac)p;
	pque_t pq = &pf->que;
	pnode_t pcur;
	while (1)
	{
		pthread_mutex_lock(&pq->que_mutex);
		if (0 == pq->size)
		{
			pthread_cond_wait(&pf->cond, &pq->que_mutex);
		}
		que_get(pq, &pcur);
		pthread_mutex_unlock(&pq->que_mutex);
		if (pcur != NULL)
		{
			tran_file(pcur->new_fd);
			free(pcur);
		}
	}
}

// 异步拉起同步，收到信号执行信号处理函数
void sig_exit_func(int signum)
{
	char flag = 1;
	write(exit_fds[1], &flag, 1);
}

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		printf("./server IP PORT THREAD_NUM CAPACITY");
		return -1;
	}
	factory f; // 主要数据结构
	int thread_num = atoi(argv[3]);
	int capacity = atoi(argv[4]);
	factory_init(&f, download_file, thread_num, capacity);
	factory_start(&f);
	int sfd;
	tcp_start_listen(&sfd, argv[1], argv[2], capacity);
	int new_fd;
	pque_t pq = &f.que;
	pnode_t pnew;
	pipe(exit_fds);
	int ret;
	int epfd = epoll_create(1);
	struct epoll_event event, evs[2];
	event.events = EPOLLIN;
	event.data.fd = sfd;
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &event);
	check_error(-1, ret, "epoll_ctl");
	// 监控exit_fds[0]管道
	event.data.fd = exit_fds[0];
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, exit_fds[0], &event);
	check_error(-1, ret, "epoll_ctl");
	int i;
	signal(SIGUSR1, sig_exit_func);
	while (1)
	{
		ret = epoll_wait(epfd, evs, 2, -1);
		for (i = 0; i < ret; i++)
		{
			if (sfd == evs[i].data.fd)
			{
				new_fd = accept(sfd, NULL, NULL);
				pnew = (pnode_t)calloc(1, sizeof(node_t));
				pnew->new_fd = new_fd;
				pthread_mutex_lock(&pq->que_mutex);
				que_insert(pq, pnew);
				pthread_mutex_unlock(&pq->que_mutex);
				pthread_cond_signal(&f.cond); // 发送信号给子线程
			}
			// 收到SIGUSR1信号，开始退出
			if (exit_fds[0] == evs[i].data.fd)
			{
				close(sfd); // 不再接受新的网络请求
				pnew = (pnode_t)calloc(1, sizeof(node_t));
				pnew->new_fd = -1;
				pthread_mutex_lock(&pq->que_mutex);
				que_insert_exit(pq, pnew);
				pthread_mutex_unlock(&pq->que_mutex);
				pthread_cond_broadcast(&f.cond);
				for (i = 0; i < f.pthread_num; i++)
				{
					pthread_join(f.pth_id[i], NULL);
				}
				exit(0);
			}
		}
	}
}
