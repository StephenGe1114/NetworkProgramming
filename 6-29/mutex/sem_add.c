 ///
 /// @file    sem_add.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"
#define N 10000000
int main(int argc, char **argv)
{
	int sem_id;
	sem_id = semget(1000, 1, IPC_CREAT | 0600);
	check_error(-1, sem_id, "semget");
	int ret;
	ret = semctl(sem_id, 0, SETVAL, 1);
	check_error(-1, ret, "semctl");
	int shmid;
	shmid = shmget(1000, 4096, 0600 | IPC_CREAT);
	if (-1 == shmid)
	{
		perror("shmget");
		return -1;
	}
	printf("shmid=%d\n", shmid);
	int *p;
	p = (int *)shmat(shmid, NULL, 0);
	if ((int *)-1 == p)
	{
		perror("shmat");
		return -1;
	}
	p[0] = 0;
	int i;
	struct sembuf sopp, sopv;
	sopp.sem_num = 0;
	sopp.sem_op = -1; // 加锁
	sopp.sem_flg = SEM_UNDO;
	sopv.sem_num = 0;
	sopv.sem_op = 1; // 解锁
	sopv.sem_flg = SEM_UNDO;
	struct timeval start, end;
	gettimeofday(&start, NULL);
	if (!fork())
	{
		for (i = 0; i < N; i++)
		{
			// 关灯，加锁
			semop(sem_id, &sopp, 1);
			p[0] = p[0] + 1;
			semop(sem_id, &sopv, 1);
			// 开灯，解锁
		}
	}
	else
	{
		for (i = 0; i < N; i++)
		{
			// 关灯，加锁
			semop(sem_id, &sopp, 1);
			p[0] = p[0] + 1;
			semop(sem_id, &sopv, 1);
			// 开灯，解锁
		}
		wait(NULL);
		gettimeofday(&end, NULL);
		printf("I am parent p[0]=%d\n", p[0]);
		printf("use time=%ld\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
	}
	return 0;
}

