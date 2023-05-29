 ///
 /// @file    shmat_fork.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"
#define N 10000000
int main(int argc, char **argv)
{
	args_check(argc, 2);
	key_t key;
	key = ftok(argv[1], 1);
	printf("key=%d\n", key);
	int shmid;
	shmid = shmget(key, 4096, 0600 | IPC_CREAT);
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
	if (!fork())
	{
		for (i = 0; i < N; i++)
		{
			p[0] = p[0] + 1;
		}
	}
	else
	{
		for (i = 0; i < N; i++)
		{
			p[0] = p[0] + 1;
		}
		wait(NULL);
		printf("I am parent p[0]=%d\n", p[0]);
	}
	return 0;
}

