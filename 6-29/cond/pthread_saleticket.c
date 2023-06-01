 ///
 /// @file    pthread_saleticket.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

typedef struct
{
	int ticketnum;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int windows;
	int fds[2];
} data;

void *salewindows(void *p)
{
	data *pt = (data *)p;
	int windows = pt->windows;
	write(pt->fds[1], &windows, 1);
	int i = 0;
	while (1)
	{
		pthread_mutex_lock(&pt->mutex);
		if (pt->ticketnum > 0)
		{
			printf("windows %d is staring sales tickets %d\n", windows, pt->ticketnum);
			pt->ticketnum--;
			if (!pt->ticketnum)
			{
				pthread_cond_signal(&pt->cond);
			}
			i++;
			printf("windows %d is sales finish %d\n", windows, pt->ticketnum);
		}
		else
		{
			pthread_mutex_unlock(&pt->mutex);
			printf("windows %d i=%d\n", windows, i);
			break;
		}
		pthread_mutex_unlock(&pt->mutex);
		sleep(1);
	}
}
// 放票线程
void *setticket(void *p)
{
	data *pt = (data *)p;
	pthread_mutex_lock(&pt->mutex);
	if (pt->ticketnum > 0)
	{
		pthread_cond_wait(&pt->cond, &pt->mutex);
	}
	pt->ticketnum = 20;
	pthread_mutex_unlock(&pt->mutex);
}

int main()
{
	pthread_t pth[3];
	data t;
	pipe(t.fds);
	t.ticketnum = 20;
	pthread_mutex_init(&t.mutex, NULL);
	pthread_cond_init(&t.cond, NULL);
	int i;
	char flag;
	for (i = 0; i < 2; i++)
	{
		t.windows = i;
		pthread_create(pth + i, NULL, salewindows, &t);
		read(t.fds[0], &flag, sizeof(flag));
	}
	pthread_create(pth + 2, NULL, setticket, &t);
	for (i = 0; i < 3; i++)
	{
		pthread_join(pth[i], NULL);
	}
	return 0;
}

