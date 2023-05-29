 ///
 /// @file    shmget_private.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"
// 私有方式创建共享内存，只能在有亲缘性关系的进程间使用
int main()
{
	int shmid;
	shmid = shmget(IPC_PRIVATE, 4096, 0600 | IPC_CREAT);
	check_error(-1, shmid, "shmget");
	return 0;
}

