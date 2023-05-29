 ///
 /// @file    shmctl_rmid.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"
// 删除共享内存
int main()
{
	int shmid;
	shmid = shmget(1000, 4096, 0600 | IPC_CREAT);
	check_error(-1, shmid, "shmget");
	int ret;
	ret = shmctl(shmid, IPC_RMID, NULL);
	check_error(-1, ret, "shmctl");
	return 0;
}

