 ///
 /// @file    6.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*卖票*/

#include "func.h"

typedef struct{
	pthread_cond_t cond;
	pthread_mutex_t mutex;
    int tickets;
    int window;
	int fds[2];
} data;

void* saleTickets(void *p)
{
    data* pData = (data*)p;
    int window = pData->window;
	write(pData->fds[1], "h", 1);
    int i = 0;
    while(1) {
        pthread_mutex_lock(&pData->mutex);
        printf("now window %d begin sale, left tickets = %d\n", window, pData->tickets);
        if(pData->tickets > 0) {
            --pData->tickets;
            ++i;
            if(!pData->tickets) {
                pthread_cond_signal(&pData->cond);
            }
            pthread_mutex_unlock(&pData->mutex);
            printf("window %d sales %d\n", window, i);
        } else {
            pthread_mutex_unlock(&pData->mutex);
            printf("sale out\n");
            break;
        }
		sleep(1);
    }
    return NULL;
}

void* setTickets(void* p)
{
    data* pData = (data*)p;
    pthread_mutex_lock(&pData->mutex);
    pthread_cond_wait(&pData->cond, &pData->mutex);
    pData->tickets = 20;
    printf("after setTickets, now tickets = %d\n", pData->tickets);
    pthread_mutex_unlock(&pData->mutex);
    return NULL;
}

int main()
{
    data d;
    pthread_cond_init(&d.cond, NULL);
    pthread_mutex_init(&d.mutex, NULL);
    d.tickets = 20;
	pipe(d.fds);
    pthread_t pthid[3];
    int i;
    for(i = 0; i < 2; i++) {
        d.window = i;
        pthread_create(pthid + i, NULL, saleTickets, &d);
		char c;
		read(d.fds[0], &c, 1);
    }
    pthread_create(pthid + 2, NULL, setTickets, &d);
    for(i = 0; i < 3; i++) {
        pthread_join(pthid[i], NULL);
    }
    pthread_cond_destroy(&d.cond);
    pthread_mutex_destroy(&d.mutex);
    printf("mainthread\n");

    return 0;
}
