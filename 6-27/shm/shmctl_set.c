 ///
 /// @file    shmctl_set.c
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
	struct shmid_ds buf;
	ret = shmctl(shmid, IPC_STAT, &buf);
	check_error(-1, ret, "shmctl");
	printf("cuid=%d,mode=%o,size=%ld,nattach=%ld\n", buf.shm_perm.cuid, buf.shm_perm.mode, buf.shm_segsz, buf.shm_nattch);
	buf.shm_perm.mode = 0666;
	ret = shmctl(shmid, IPC_SET, &buf);
	check_error(-1, ret, "shmctl");
	return 0;
}

