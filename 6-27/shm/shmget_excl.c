 ///
 /// @file    shmget_excl.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	int shmid;
	shmid = shmget(1000, 4096, 0600 | IPC_CREAT | IPC_EXCL);
	check_error(-1, shmid, "shmget");
	return 0;
}

