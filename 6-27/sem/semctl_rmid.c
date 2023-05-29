 ///
 /// @file    semctl_rmid.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"
// 删除信号量集合
int main()
{
	int sem_id;
	sem_id = semget(1001, 5, IPC_CREAT | 0600);
	check_error(-1, sem_id, "semget");
	int ret = semctl(sem_id, 0, IPC_RMID);
	check_error(-1, ret, "semctl");
	return 0;
}

