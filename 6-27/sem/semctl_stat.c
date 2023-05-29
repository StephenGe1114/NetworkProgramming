 ///
 /// @file    semctl_stat.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"
// 删除信号量集合
int main()
{
	int sem_id;
	sem_id = semget(1000, 2, IPC_CREAT | 0600);
	check_error(-1, sem_id, "semget");
	struct semid_ds buf;
	int ret = semctl(sem_id, 0, IPC_STAT, &buf);
	check_error(-1, ret, "semctl");
	printf("uid=%d,mode=%o,nsems=%ld\n", buf.sem_perm.uid, buf.sem_perm.mode, buf.sem_nsems);
	return 0;
}

