 ///
 /// @file    shmdt.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

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
	sleep(10);
	int ret;
	ret = shmdt(p);
	if (-1 == ret)
	{
		perror("shmdt");
		return -1;
	}
	while (1)
		;
	return 0;
}

